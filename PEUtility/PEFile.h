// ****************************************************************************
// File:		PEFile.h
// Purpose: 	To contain the declaration of a class PEFile. 
//				
//				PEFile represents a PE file.
//				It provides a set of access methods to get to certain parts
//				within a PE file (for example, "header" and "optional header".
//				PEFile object itself is a container class which simply
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

#ifndef PE_FILE_H
#define PE_FILE_H

#include "PEUtility.h"

#include "PEFileHeader.h"
#include "PEOptionalHeader.h"  
#include "PESectionTable.h"	   


class PEFile : public IPEFileWrap 
{	   
	HANDLE				m_hFile;
	HANDLE				m_hFileMapping;
	LPVOID				m_lpFileBase;
	DWORD				m_base;
	PIMAGE_NT_HEADERS	m_pNTHeader;

	PEFileHeader*		m_header;
	PEOptionalHeader*	m_optionalheader;
	PESectionTable*		m_sectiontable;

	const static char*	m_strErrorMessages[];
	static std::string	m_error;

public:

	// ===========================================================
	// Exceptions that this class may throw.
	// ===========================================================
	enum Exception
	{
		WIN32API_FAILURE_CREATEFILE,
		WIN32API_FAILURE_CREATEFILEMAPPING,
		WIN32API_FAILURE_MAPVIEWOFFILE,
		IMAGE_DOS_SIGNATURE_ABSENT,
		IMAGE_NT_SIGNATURE_ABSENT
	};
	static void GetLastError(std::string& buf);

	PEFile(char* pefile);
	~PEFile();				 

	// ===========================================================
	// Primitive "console" dump methods.
	// ===========================================================
	void DumpHeaderContents()			{ m_header->DoConsoleOutput(); };
	void DumpOptionalHeaderContents()	{ m_optionalheader->DoConsoleOutput(); };
	void DumpSectionTableContents()		{ m_sectiontable->DoConsoleOutput(); };

	// ===========================================================
	// Methods that provide per-section information to clients.
	// ===========================================================
	virtual DWORD	GetBase() 								{ return m_base; };
	virtual DWORD	GetCodeSectionOffset() 				{ return m_sectiontable->GetCodeSectionOffset(); };
	virtual UINT	GetCodeSectionSize() 					{ return m_sectiontable->GetCodeSectionSize(); };
	virtual DWORD	GetInitializedDataSectionOffset() 		{ return m_sectiontable->GetInitializedDataSectionOffset();	};
	virtual UINT	GetInitializedDataSectionSize() 		{ return m_sectiontable->GetInitializedDataSectionSize(); };
	virtual DWORD	GetUninitializedDataSectionOffset() 	{ return m_sectiontable->GetUninitializedDataSectionOffset(); };
	virtual UINT	GetUninitializedDataSectionSize() 		{ return m_sectiontable->GetUninitializedDataSectionSize(); };
	virtual DWORD	GetImportDataSectionOffset() 			{ return m_sectiontable->GetImportDataSectionOffset(); };
	virtual UINT	GetImportDataSectionSize() 			{ return m_sectiontable->GetImportDataSectionSize(); };
	virtual DWORD	GetExportDataSectionOffset() 			{ return m_sectiontable->GetExportDataSectionOffset(); };
	virtual UINT	GetExportDataSectionSize() 			{ return m_sectiontable->GetExportDataSectionSize(); };
	virtual DWORD	GetResourceSectionOffset() 			{ return m_sectiontable->GetResourceSectionOffset(); };
	virtual UINT	GetResourceSectionSize() 				{ return m_sectiontable->GetResourceSectionSize(); };
};

#endif //PE_FILE_H
