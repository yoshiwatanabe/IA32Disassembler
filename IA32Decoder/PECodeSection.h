// ****************************************************************************
// File:		PECodeSection.h
// Purpose: 	To contain the declaration of a class PECodeSection. 
//				
//				PECodeSection represents the "code section" part of a PE file.
//				It provides a set of access methods to get to certain parts
//				within a PE file (for example, "header" and "optional header".
//				PECodeSection object itself is a container class which simply
//				host subordinate objects. Each subordinate object is responsible
//				for a part (section) within a PE file.
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

#ifndef PE_CODE_SECTION_H
#define PE_CODE_SECTION_H

#include "IA32InstructionParser.h"

class PECodeSection  
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

	PECodeSection(DWORD begin, UINT size);
	~PECodeSection();  

	void DoCosoleOutput();
};

#endif //PE_CODE_SECTION_H
