// SimpleDecoder.cpp: implementation of the SimpleDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>	  
#include <iostream>
#include <cassert>
#include <string>
#include <windows.h>


#include "SimpleDecoder.h"

const char SimpleDecoder::PARSER_SERVER_FILENAME[]	= { "IA32Parser.dll" };
const char SimpleDecoder::PARSER_CREATION_ROUTINE[] = { "CreateInstructionParser" };
const char*	SimpleDecoder::m_strErrorMessages[]		= {

	"SimpleDecoder object exception: Can't load code section parser server IA32Parser.dll. Make sure the server is in the PATH.",
	"SimpleDecoder object exception: Can't find parser creation routine CreateInstructionParser() in the server",
	"SimpleDecoder object exception: Can't instantiate InstructionParser object using CreateInstructionParser() routine in the server"
};

std::string SimpleDecoder::m_error;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SimpleDecoder::SimpleDecoder(DWORD begin, UINT size)
	: m_begin( reinterpret_cast<BYTE*>(begin) )
	, m_size(size)
{
	assert( begin != 0 );
	assert( begin >= 0 );
	assert( !IsBadReadPtr((void*)begin, sizeof(void*)) );

	// ===========================================================
	// implement exception throwing here.
	// ===========================================================
	initializeParser();
};

SimpleDecoder::~SimpleDecoder()
{
	if ( m_parser_handle ) FreeLibrary( m_parser_handle ), m_parser_handle = NULL; 
}

// 
// Initialize member pointer which will point to an instance of
// InstructionParser object hosted in a separate DLL server.
//
// EXCEPTION: PARSER_SERVER_LOAD_FAILURE - loading of DLL failed.  
// 			  PARSER_FACTORY_LOCATE_FAILURE - unable to get creation function.
//			  PARSER_INSTANCE_CREATION_FAILURE - creation of instance failed.
// 
void SimpleDecoder::initializeParser()
{
	// ===========================================================
	// [1] First, we try to "load" the server DLL using Win32 API
	//	   LoadLibrary().
	// [2] Next, use Win32 API GetProceAddress to obtain a pointer to 
	//	   the function which we will use to create an instance of
	//     InstructionParser.
	// [3a] Finally, we try to create and obtain a pointer to
	//     InstructionParser. However, before that, we must "cast" 
	//     the function pointer obtained from GetProceAddress. 
	//     GetProcAddress simply returns a pointer to function that 
	//     takes 'void' as a parameter and returns a 'void'.
	//     Definitely, this is NOT the signiture of the actual
	//     routine that the function pointer is pointing.
	//
	// [3b] Now we can use the function pointer, properly casted
	//	   and stored in the appropriate pointer variable.
	// ===========================================================	

	// [1]
	{
		m_parser_handle = LoadLibrary( SimpleDecoder::PARSER_SERVER_FILENAME );

		if ( m_parser_handle == NULL )
		{
			m_error = m_strErrorMessages[PARSER_SERVER_LOAD_FAILURE];
			throw PARSER_SERVER_LOAD_FAILURE;
		}
	}

	// [2]
	FARPROC function_pointer = 
		GetProcAddress( m_parser_handle, SimpleDecoder::PARSER_CREATION_ROUTINE );

	if ( function_pointer == NULL )
	{
		m_error = m_strErrorMessages[PARSER_FACTORY_LOCATE_FAILURE];
		throw PARSER_FACTORY_LOCATE_FAILURE;
	}

	// [3a]
	PFACTORY_FUNCTION pCreateInstructionParser = (PFACTORY_FUNCTION)function_pointer;

	// [3b]
	BYTE* code_section = const_cast<BYTE*>(m_begin);
	m_instruction_parser = (*pCreateInstructionParser)(code_section, m_size);

	if ( m_instruction_parser == NULL )
	{
		m_error = m_strErrorMessages[PARSER_INSTANCE_CREATION_FAILURE];
		throw PARSER_INSTANCE_CREATION_FAILURE;
	}
}
  
//
// Dumps the content of 'code section' in the PE file to console output
// - in effect, this method realizes a traditional "disassembler".
//
void SimpleDecoder::DoCosoleOutput()
{
	assert(NULL != m_parser_handle);
	assert(!IsBadReadPtr( (void*)m_instruction_parser, sizeof(void*)));

	BYTE* current_position = const_cast<BYTE*>(m_begin);
	BYTE* new_position = NULL;

	BYTE	raw_data_buffer[MINIMUM_BUFFER_SIZE];
	int		raw_data_size = 0;
	char	strbuffer[MINIMUM_BUFFER_SIZE * 2];


	// ===========================================================
	// Get the first instruction in raw byte format.
	// ===========================================================
	raw_data_size = 
		m_instruction_parser->GetFirstRawInstructionData( raw_data_buffer );

	// ===========================================================
	// Set up a loop that terminates when there is no more
	// instruction.
	// ===========================================================
	while ( raw_data_size != NO_MORE_INSTRUCTION )
	{
		char lineoutput[MAX_PATH] = { 0 };

		// ===========================================================
		// Size == 0 means that parser couldn't interpret the byte.
		// just show the byte to user, and go on. (this is not a 
		// fatal error).
		// Size == n means we go 'n' byte-long instruction raw data.
		// In either case, copy raw byte(s) in character foramt
		// to 'lineoutput' buffer, then show it to user.
		// ===========================================================
		if ( raw_data_size == 0 )
		{
			sprintf( lineoutput, 
				     "%02X (not processed - instruction not implemented?)", 
					 raw_data_buffer[0] );
		}
		else
		{
			for ( int i = 0; i < raw_data_size; ++i )
			{
				sprintf(strbuffer, "%02X ", raw_data_buffer[i]);
				strcat(lineoutput, strbuffer);
			}
		}

		printf("%s\n", lineoutput);

		// ===========================================================
		// Read next instruction in raw byte format.
		// ===========================================================
		raw_data_size = m_instruction_parser->GetNextRawInstructionData( raw_data_buffer );
	}
}

void SimpleDecoder::GetLastError(std::string& buf)
{
	buf = m_error;
}