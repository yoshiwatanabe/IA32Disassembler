// PEFileHeader.cpp: implementation of the PEFileHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEFileHeader.h"

PEFileHeader::WORD_FLAG_DESCRIPTIONS PEFileHeader::ImageFileHeaderCharacteristics[] = 
{
	{ IMAGE_FILE_RELOCS_STRIPPED, "RELOCS_STRIPPED" },
	{ IMAGE_FILE_EXECUTABLE_IMAGE, "EXECUTABLE_IMAGE" },
	{ IMAGE_FILE_LINE_NUMS_STRIPPED, "LINE_NUMS_STRIPPED" },
	{ IMAGE_FILE_LOCAL_SYMS_STRIPPED, "LOCAL_SYMS_STRIPPED" },
	// { IMAGE_FILE_MINIMAL_OBJECT, "MINIMAL_OBJECT" }, // Removed in NT 3.5
	// { IMAGE_FILE_UPDATE_OBJECT, "UPDATE_OBJECT" },   // Removed in NT 3.5
	// { IMAGE_FILE_16BIT_MACHINE, "16BIT_MACHINE" },   // Removed in NT 3.5
	{ IMAGE_FILE_BYTES_REVERSED_LO, "BYTES_REVERSED_LO" },
	{ IMAGE_FILE_32BIT_MACHINE, "32BIT_MACHINE" },
	{ IMAGE_FILE_DEBUG_STRIPPED, "DEBUG_STRIPPED" },
	// { IMAGE_FILE_PATCH, "PATCH" },
	{ IMAGE_FILE_SYSTEM, "SYSTEM" },
	{ IMAGE_FILE_DLL, "DLL" },
	{ IMAGE_FILE_BYTES_REVERSED_HI, "BYTES_REVERSED_HI" }
};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 
PEFileHeader::PEFileHeader(PIMAGE_NT_HEADERS ntheader)
	: NUMBER_IMAGE_HEADER_FLAGS(10)	
	, m_pImageFileHeader(reinterpret_cast<PIMAGE_FILE_HEADER>( &(ntheader->FileHeader) ))
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(ntheader), sizeof(void*)) );
};				

PEFileHeader::~PEFileHeader()
{
};

void PEFileHeader::DoConsoleOutput() const
{
	using namespace std;

	UINT headerFieldWidth = 30;
	UINT i;
	char *szMachine;
	char buffer[60];

	switch( m_pImageFileHeader->Machine )
	{
		case IMAGE_FILE_MACHINE_I386:   szMachine = "i386"; break;
		// case IMAGE_FILE_MACHINE_I860:    szMachine = "i860"; break;
		case IMAGE_FILE_MACHINE_R3000:  szMachine = "R3000"; break;
		case IMAGE_FILE_MACHINE_R4000:  szMachine = "R4000"; break;
		case IMAGE_FILE_MACHINE_ALPHA:  szMachine = "alpha"; break;
		default:    szMachine = "unknown"; break;
	}

	wsprintf(buffer, "Machine:\t%04X (%s)", m_pImageFileHeader->Machine, szMachine);
	cout << buffer << '\n';

	wsprintf(buffer, "Number of Sections:\t%04X", m_pImageFileHeader->NumberOfSections);
	cout << buffer << '\n';

	wsprintf(buffer, "TimeDateStamp:\t%08X", m_pImageFileHeader->TimeDateStamp);
	cout << buffer << '\n';

	wsprintf(buffer, "PointerToSymbolTable:\t%08X", m_pImageFileHeader->PointerToSymbolTable);
	cout << buffer << '\n';

	wsprintf(buffer, "NumberOfSymbols:\t%08X", m_pImageFileHeader->NumberOfSymbols);
	cout << buffer << '\n';

	wsprintf(buffer, "SizeOfOptionalHeader:\t%04X", m_pImageFileHeader->SizeOfOptionalHeader);
	cout << buffer << '\n';

	wsprintf(buffer, "Characteristices:\t%04X", m_pImageFileHeader->Characteristics);
	cout << buffer << '\n';


	for ( i=0; i < NUMBER_IMAGE_HEADER_FLAGS; i++ )
	{
		if ( m_pImageFileHeader->Characteristics & 
			 ImageFileHeaderCharacteristics[i].flag )
		{
		wsprintf(buffer, "  %s", ImageFileHeaderCharacteristics[i].name);
		cout << buffer << '\n';
		}
	}
};

