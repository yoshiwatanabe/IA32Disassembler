// ****************************************************************************
// File:		PEOptionalHeader.h
// Purpose: 	To contain the declaration of a class PEOptionalHeader. 
//				
//				PEOptionalHeader represents "optional header" part of a PE file.
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

#ifndef PE_OPTIONAL_HEADER_H
#define PE_OPTIONAL_HEADER_H

class PEOptionalHeader  
{
	static char *					ImageDirectoryNames[]; 
	const unsigned int				NUMBER_IMAGE_DIRECTORY_ENTRYS;
	const PIMAGE_OPTIONAL_HEADER	m_optionalHeader;

public:
	PEOptionalHeader(PIMAGE_NT_HEADERS ntheader);
	~PEOptionalHeader();
	void DoConsoleOutput() const;
};

#endif //PE_OPTIONAL_HEADER_H
