// ****************************************************************************
// File:		PEFileHeader.h
// Purpose: 	To contain the declaration of a class PEFileHeader. 
//				
//				PEFileHeader represents "primary header" part of a PE file.
//				It provides a primitive "dump" capability via DoConsoleOutput
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

#ifndef PD_FILE_HEADER_H
#define PD_FILE_HEADER_H

class PEFileHeader  
{
	typedef struct 
	{ 
		WORD    flag;
		PSTR    name;

	} WORD_FLAG_DESCRIPTIONS;

	typedef struct
	{
		DWORD   flag;
		PSTR    name;

	} DWORD_FLAG_DESCRIPTIONS;

	// Bitfield values and names for the IMAGE_FILE_HEADER flags
	static WORD_FLAG_DESCRIPTIONS	ImageFileHeaderCharacteristics[];
	const UINT						NUMBER_IMAGE_HEADER_FLAGS;
	const PIMAGE_FILE_HEADER		m_pImageFileHeader;

public:
	PEFileHeader(PIMAGE_NT_HEADERS ntheader);
	~PEFileHeader();
	UINT NumberOfSections() { return m_pImageFileHeader->NumberOfSections; };
	void DoConsoleOutput() const;
};

#endif //PD_FILE_HEADER_H
