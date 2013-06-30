// PEOptionalHeader.cpp: implementation of the PEOptionalHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEOptionalHeader.h"
							   

char* PEOptionalHeader::ImageDirectoryNames[] = 
{
    "EXPORT", "IMPORT", "RESOURCE", "EXCEPTION", "SECURITY", "BASERELOC",
    "DEBUG", "COPYRIGHT", "GLOBALPTR", "TLS", "LOAD_CONFIG",
    "BOUND_IMPORT", "IAT" // These last two entries added for NT 3.51
};    

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PEOptionalHeader::PEOptionalHeader(PIMAGE_NT_HEADERS ntheader)
	: NUMBER_IMAGE_DIRECTORY_ENTRYS( 13 )
	, m_optionalHeader(reinterpret_cast<PIMAGE_OPTIONAL_HEADER>( &(ntheader->OptionalHeader) ) )
{
	assert( !IsBadReadPtr((void*)ntheader, sizeof(void*)) );
};

PEOptionalHeader::~PEOptionalHeader()
{
};

void PEOptionalHeader::DoConsoleOutput() const
{
	using namespace std;

	UINT width = 30;
	char *s, buffer[80];
	UINT i;

	wsprintf(buffer, "Magic\t%04X", m_optionalHeader->Magic);    
	cout << buffer << '\n';

	wsprintf(buffer, "Linker version\t%u.%02u", m_optionalHeader->MajorLinkerVersion,
												m_optionalHeader->MinorLinkerVersion);    
	cout << buffer << '\n';

	wsprintf(buffer, "size of code\t%X", m_optionalHeader->SizeOfCode);    
	cout << buffer << '\n';

	wsprintf(buffer, "size of initialized data\t%X", m_optionalHeader->SizeOfInitializedData);    
	cout << buffer << '\n';

	wsprintf(buffer, "size of uninitialized data\t%X", m_optionalHeader->SizeOfUninitializedData);    
	cout << buffer << '\n';

	wsprintf(buffer, "entrypoint RVA\t%X", m_optionalHeader->AddressOfEntryPoint);    
	cout << buffer << '\n';

	wsprintf(buffer, "base of code\t%X", m_optionalHeader->BaseOfCode);    
	cout << buffer << '\n';

	wsprintf(buffer, "base of data\t%X", m_optionalHeader->BaseOfData);    
	cout << buffer << '\n';

	wsprintf(buffer, "image base\t%X", m_optionalHeader->ImageBase);    
	cout << buffer << '\n';

	wsprintf(buffer, "section align\t%X", m_optionalHeader->SectionAlignment);    
	cout << buffer << '\n';

	wsprintf(buffer, "file align\t%X", m_optionalHeader->FileAlignment);    
	cout << buffer << '\n';

	wsprintf(buffer, "required OS version\t%u.%02u",
		m_optionalHeader->MajorOperatingSystemVersion,
		m_optionalHeader->MinorOperatingSystemVersion);    
	cout << buffer << '\n';

	wsprintf(buffer, "image version\t%u.%02u",
		m_optionalHeader->MajorImageVersion,
		m_optionalHeader->MinorImageVersion);    
	cout << buffer << '\n';

	wsprintf(buffer, "subsystem version\t%u.%02u",
		m_optionalHeader->MajorSubsystemVersion,
		m_optionalHeader->MinorSubsystemVersion);    
	cout << buffer << '\n';

	wsprintf(buffer, "size of image\t%X", m_optionalHeader->SizeOfImage);    
	cout << buffer << '\n';

	wsprintf(buffer, "size of headers\t%X", m_optionalHeader->SizeOfHeaders);    
	cout << buffer << '\n';

	wsprintf(buffer, "checksum\t%X", m_optionalHeader->CheckSum);    
	cout << buffer << '\n';

	switch( m_optionalHeader->Subsystem )
	{
		case IMAGE_SUBSYSTEM_NATIVE: s = "Native"; break;
		case IMAGE_SUBSYSTEM_WINDOWS_GUI: s = "Windows GUI"; break;
		case IMAGE_SUBSYSTEM_WINDOWS_CUI: s = "Windows character"; break;
		case IMAGE_SUBSYSTEM_OS2_CUI: s = "OS/2 character"; break;
		case IMAGE_SUBSYSTEM_POSIX_CUI: s = "Posix character"; break;
		default: s = "unknown";
	}
	wsprintf(buffer, "Subsystem\t%04X (%s)", m_optionalHeader->Subsystem, s);
	cout << buffer << '\n';    

	wsprintf(buffer, "stack reserve size\t%X", m_optionalHeader->SizeOfStackReserve);
	cout << buffer << '\n';    

	wsprintf(buffer, "stack commit size\t%X", m_optionalHeader->SizeOfStackCommit);
	cout << buffer << '\n';    

	wsprintf(buffer, "heap reserve size\t%X", m_optionalHeader->SizeOfHeapReserve);
	cout << buffer << '\n';    

	wsprintf(buffer, "heap commit size\t%X", m_optionalHeader->SizeOfHeapCommit);
	cout << buffer << '\n';    



	wsprintf(buffer, "RVAs & sizes\t%X", m_optionalHeader->NumberOfRvaAndSizes);
	cout << buffer << '\n';    

	cout << "\n- Data Directory -";

	
	for ( i=0; i < m_optionalHeader->NumberOfRvaAndSizes; i++)
	{
		wsprintf(buffer, "%-12s \trva: %08X size: %08X\n",
			(i >= NUMBER_IMAGE_DIRECTORY_ENTRYS)
				? "unused" : ImageDirectoryNames[i], 
			m_optionalHeader->DataDirectory[i].VirtualAddress,
			m_optionalHeader->DataDirectory[i].Size);
		
		cout << buffer << '\n';
	}
}
