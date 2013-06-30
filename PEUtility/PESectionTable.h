// ****************************************************************************
// File:		PESectionTable.h
// Purpose: 	To contain the declaration of a class PESectionTable. 
//				
//				PESectionTable represents "Section table" part of a PE file.
//				It provides its clients with a set of methods to give
//				size and location of the requested 'section'.
//				It also provides a primitive "dump" capability via DoConsoleOutput
//				method.
//
// Note:		Code is adopted from Matt Pietrek's PEDUMP source file to fit to
//				C++ style responsibility-based decomposition.
//
// Author:		Yoshi Watanabe
//
// Log:			1/16/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef PE_SECTION_TABLE_H
#define PE_SECTION_TABLE_H

class PESectionTable  
{
	typedef struct
	{
		DWORD   flag;
		PSTR    name;

	} DWORD_FLAG_DESCRIPTIONS;

	static DWORD_FLAG_DESCRIPTIONS	SectionCharacteristics[];
	const unsigned char				NUMBER_SECTION_CHARACTERISTICS;
	const PIMAGE_SECTION_HEADER		m_section;
	const UINT						m_cSections;

	DWORD getSectionOffset(const char* sectionname) const ;
	UINT  getSectionSize(char* sectionname) const ;

public:
	PESectionTable(PIMAGE_NT_HEADERS ntheader, unsigned int nSections);
	~PESectionTable();
	void DoConsoleOutput() const;

	// ===========================================================
	// These member functions return 'offset' and 'size' of
	// commonly referred section such as ".text" (CODE) section.
	// NOTE: ".xxx" convention is what Microsoft tool generates so
	// these ruotine don't work with Borland or other tools.
	// ===========================================================
	DWORD	GetCodeSectionOffset() const				{ return getSectionOffset(".text"); };
	UINT	GetCodeSectionSize() const					{ return getSectionSize(".text"); };
	DWORD	GetInitializedDataSectionOffset() const		{ return getSectionOffset(".data"); };
	UINT	GetInitializedDataSectionSize() const		{ return getSectionSize(".data"); };
	DWORD	GetUninitializedDataSectionOffset() const	{ return getSectionOffset(".bss"); };
	UINT	GetUninitializedDataSectionSize() const		{ return getSectionSize(".bss"); };
	DWORD	GetImportDataSectionOffset() const			{ return getSectionOffset(".idata"); };
	UINT	GetImportDataSectionSize() const			{ return getSectionSize(".idata"); };
	DWORD	GetExportDataSectionOffset() const			{ return getSectionOffset(".edata"); };
	UINT	GetExportDataSectionSize() const			{ return getSectionSize(".edata"); };
	DWORD	GetResourceSectionOffset() const			{ return getSectionOffset(".rsrc"); };
	UINT	GetResourceSectionSize() const				{ return getSectionSize(".rsrc"); };
};

#endif //PE_SECTION_TABLE_H
