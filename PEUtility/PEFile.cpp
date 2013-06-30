// PEFile.cpp: implementation of the PEFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEFile.h"

const char* PEFile::m_strErrorMessages[] = 
{ 
	"PEFile object exception: Couldn't open specified PE file with CreateFile().",
	"PEFile object exception: Couldn't open file mapping with CreateFileMapping() API.",
	"PEFile object exception: Couldn't map view of file with MapViewOfFile() API",
	"PEFile object exception: Couldn't find DOS signature (NZ) in the specified file.",
	"PEFile object exception: Coundn't find NT signature (PE) in the specified file."
};

std::string PEFile::m_error;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

  
PEFile::PEFile(char* pefile)
{
	assert(!IsBadReadPtr((void*)pefile,sizeof(char*)));

	m_hFile			= INVALID_HANDLE_VALUE;
	m_hFileMapping	= 0;
	m_lpFileBase	= NULL;
	m_base			= 0;
	m_pNTHeader		= NULL;

	PIMAGE_DOS_HEADER dosHeader;

	try
	{
		// ===========================================================
		// [1] Try to open target file with CreateFile API
		// [2] Try to create a file mapping for the file just opened.
		// [3] Try to "map" view of the file.
		// [4] Veryfy DOS signature (NZ).
		// [5[ Veryfy NT signature (PE).
		// ===========================================================

		// [1]
		m_hFile = CreateFile(pefile, GENERIC_READ, FILE_SHARE_READ, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if ( m_hFile == INVALID_HANDLE_VALUE )
			throw WIN32API_FAILURE_CREATEFILE;

		// [2]
		m_hFileMapping = CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		if ( m_hFileMapping == 0 )
			throw WIN32API_FAILURE_CREATEFILEMAPPING;				

		// [3]
		m_lpFileBase = MapViewOfFile(m_hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if ( m_lpFileBase == 0 )
			throw WIN32API_FAILURE_MAPVIEWOFFILE;

		// [4]
		dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>( m_lpFileBase );
		if ( dosHeader->e_magic != IMAGE_DOS_SIGNATURE )
			throw IMAGE_DOS_SIGNATURE_ABSENT;		

		
		m_base = reinterpret_cast<DWORD>( dosHeader );
   		m_pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS> (
										reinterpret_cast<DWORD>(dosHeader)	
									+	static_cast<DWORD>(dosHeader->e_lfanew) );

		// [5]		
		if ( m_pNTHeader->Signature != IMAGE_NT_SIGNATURE )
			throw IMAGE_NT_SIGNATURE_ABSENT;
	}
	catch(Exception e)
	{
		// ===========================================================
		// This block catchs class-specific exception just thrown above.
		// This block acts like a kind of destructor which makes
		// sure that things closed, if open.
		// At the end of the block, it simply "re-thows" the exception
		// so that client will be able to catch the exception.
		// ===========================================================

		if (m_lpFileBase != 0)
			UnmapViewOfFile(m_lpFileBase), m_lpFileBase = 0;

		if (m_hFileMapping != 0) 
			CloseHandle(m_hFileMapping), m_hFileMapping = 0;

		if (m_hFile != INVALID_HANDLE_VALUE)
			CloseHandle(m_hFile), m_hFile = INVALID_HANDLE_VALUE;
		
		m_error = m_strErrorMessages[e];

		throw;	// re-throw the exception we just "caught".
	}

	m_header			= new PEFileHeader(m_pNTHeader);
	m_optionalheader	= new PEOptionalHeader(m_pNTHeader);
	m_sectiontable		= new PESectionTable(m_pNTHeader, m_header->NumberOfSections());
};

PEFile::~PEFile()
{
	delete m_sectiontable;
	delete m_optionalheader;
	delete m_header;

	if (m_lpFileBase != 0)		UnmapViewOfFile(m_lpFileBase);
	if (m_hFileMapping != 0)	CloseHandle(m_hFileMapping);
	if (m_hFile != INVALID_HANDLE_VALUE) CloseHandle(m_hFile);
};


void PEFile::GetLastError(std::string& buf)
{
	buf = m_error;
}