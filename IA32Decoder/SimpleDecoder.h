// ****************************************************************************
// File:		SimpleDecoder.h
// Purpose: 	To contain the declaration of a class SimpleDecoder. 
//				
//				SimpleDecoder is able to 'decode' a stream of bytes (which
//				is supposed to be chunk of Intel x86 instructions) into
//				human-readable assebly instructions.
//
//				This decoder, being called "Simple", really doesn't do
//				any decoding at all. It can only dump hex representation of
//				raw bytes in ASCII characters in the console (via DoCosoleOutput).
//				
//				This is a starting point for more sophisticated decoders 
//				such as "disassembler" that shows out put like "MOV EAX, 4",
//				instead of "05 2F 04" or something like this.
//
// Implementation note:
//				This class is a client of a DLL called "IA32Parser.DLL". It makes
//				a call to LoadLibrary and GetProcAddress at run time, so 
//				there is no need to link against "IA32Parser.Lib" file. However,
//				if you wish, you can modify the project so that it will statically
//				link to the DLL. At any rate, IA32Parser.DLL must appear in the PATH
//				in order for this class object to work.
//
// Author:		Yoshi Watanabe
//
// Log:			1/17/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef SIMPLE_DECODER_H
#define SIMPLE_DECODER_H

#include "IA32InstructionParser.h"

class SimpleDecoder  
{
	static const char	PARSER_SERVER_FILENAME[];
	static const char	PARSER_CREATION_ROUTINE[];

	const BYTE*			m_begin;
	const UINT			m_size;
	HINSTANCE			m_parser_handle;
	InstructionParser*	m_instruction_parser;
	const static char*	m_strErrorMessages[];
	static std::string	m_error;

	void initializeParser();

public:
	enum Exception
	{
		PARSER_SERVER_LOAD_FAILURE,
		PARSER_FACTORY_LOCATE_FAILURE,
		PARSER_INSTANCE_CREATION_FAILURE
	};
	static void GetLastError(std::string& buf);

	SimpleDecoder(DWORD begin, UINT size);
	~SimpleDecoder();  

	void DoCosoleOutput();
};

#endif //SIMPLE_DECODER_H
