// PESectionTable.cpp: implementation of the PESectionTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PESectionTable.h"

PESectionTable::DWORD_FLAG_DESCRIPTIONS PESectionTable::SectionCharacteristics[] = 
{
	{ IMAGE_SCN_CNT_CODE, "CODE" },
	{ IMAGE_SCN_CNT_INITIALIZED_DATA, "INITIALIZED_DATA" },
	{ IMAGE_SCN_CNT_UNINITIALIZED_DATA, "UNINITIALIZED_DATA" },
	{ IMAGE_SCN_LNK_INFO, "LNK_INFO" },
	// { IMAGE_SCN_LNK_OVERLAY, "LNK_OVERLAY" },
	{ IMAGE_SCN_LNK_REMOVE, "LNK_REMOVE" },
	{ IMAGE_SCN_LNK_COMDAT, "LNK_COMDAT" },
	{ IMAGE_SCN_MEM_DISCARDABLE, "MEM_DISCARDABLE" },
	{ IMAGE_SCN_MEM_NOT_CACHED, "MEM_NOT_CACHED" },
	{ IMAGE_SCN_MEM_NOT_PAGED, "MEM_NOT_PAGED" },
	{ IMAGE_SCN_MEM_SHARED, "MEM_SHARED" },
	{ IMAGE_SCN_MEM_EXECUTE, "MEM_EXECUTE" },
	{ IMAGE_SCN_MEM_READ, "MEM_READ" },
	{ IMAGE_SCN_MEM_WRITE, "MEM_WRITE" },
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#include <winnt.h>

PESectionTable::PESectionTable(PIMAGE_NT_HEADERS ntheader, unsigned int nSections)
	: NUMBER_SECTION_CHARACTERISTICS(13)
	, m_section(IMAGE_FIRST_SECTION(ntheader))
	, m_cSections(nSections)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(ntheader), sizeof(void*)) );
	assert( nSections != 0 );
}

PESectionTable::~PESectionTable()
{

}

void PESectionTable::DoConsoleOutput()	const
{
	using namespace std;

	char buffer[80];
	BOOL IsEXE = TRUE;
	PIMAGE_SECTION_HEADER section = m_section;

	int i = 1;
	wsprintf(buffer, "%02X %-8.8s", i, section->Name); 	

  	//section++;

    for ( i = 1; i <= m_cSections; i++, section++ )
    {
	  	wsprintf(buffer, "%02X %-8.8s", i, section->Name); 	
		cout << buffer << '\n';

		wsprintf(buffer, "%s: %08X  Virtal address:  %08X", IsEXE ? "Virtual size":"Physical address",
			section->Misc.VirtualSize, section->VirtualAddress);
		cout << buffer << '\n';
  
		wsprintf(buffer, "Raw data offset: %08X  size (%08X)",
			section->PointerToRawData, section->SizeOfRawData);
		cout << buffer << '\n';

		wsprintf(buffer, "Relocation offset: %08X  number (%08X)",
			section->PointerToRelocations, section->NumberOfRelocations);
		cout << buffer << '\n';

		wsprintf(buffer, "Line number offset: %08X  number (%08X)",
			section->PointerToLinenumbers, section->NumberOfLinenumbers);
		cout << buffer << '\n';
		
		wsprintf(buffer, "characteristics: %08X",
			section->Characteristics);
		cout << buffer << '\n';
		//
        for ( int j=0; j < NUMBER_SECTION_CHARACTERISTICS; j++ )
        {
            if ( section->Characteristics & SectionCharacteristics[j].flag )
			{
                wsprintf(buffer, "%s", SectionCharacteristics[j].name );
				cout << buffer << '\n';
			}
        }
    }
}

// ===========================================================
// PURPOSE: Finds the PIMAGE_SECTION_HEADER element of the
// specified section (e.g. ".text") in the section table, then
// returns its 'offset'.
//
// RETURN: Returns 0 if couldn't find it. Otherwise offset. 
// ===========================================================
DWORD PESectionTable::getSectionOffset(const char* sectionname) const
{
	PIMAGE_SECTION_HEADER section = m_section;
	unsigned int i = 1;

	while ( i <= m_cSections )
	{
		if ( 0 == strncmp(
						reinterpret_cast<const char*>(section->Name),
						sectionname, 
						strlen(sectionname)) 
			)
		{
			// Found it!
			return section->PointerToRawData; 
		}

		i++;
		section++;
	}

	return 0;
};

// ===========================================================
// PURPOSE: Finds the PIMAGE_SECTION_HEADER element of the
// specified section (e.g. ".text") in the section table, then
// returns its 'size'.
//
// RETURN: Returns -1 if couldn't find it. Otherwise offset. 
// ===========================================================
UINT PESectionTable::getSectionSize(char* sectionname) const
{
	PIMAGE_SECTION_HEADER section = m_section;
	unsigned int i = 1;

	while ( i <= m_cSections )
	{
		if ( 0 == strncmp(
						reinterpret_cast<const char*>(section->Name),
						sectionname, 
						strlen(sectionname)) 
			)
		{
			// Found it!
			return section->SizeOfRawData; 
		}

		i++;
		section++;
	}

	return -1;
};
