
// ****************************************************************************
// File:		PEUtility.h
// Purpose: 	Public declaration/definition for PEUtility.DLL.
//				
//				The file contains:
//				
//				1. Declaration of an abstract base class (e.g. interface) 
//				   - IPEFileWrap.
//				3. Declaration of two exported functions which provide a pointer
//				   to an implementation of IPEFileWrap class, and an error
//				   message if case the first function fails.
//
//				Include this to your project in order to use PEUtilty.DLL
//
//
// Service provided by PEUtility.DLL and its IPEFileWrap object;
// 
//		General description:
//				IPEFileWrap is basically a wrapper of a Portable Executabl (PE) format
//				file used in most Microsoft Windows platforms (exception: VxD on Win9x)
//
//			    At this moment, the object provides a set of functions to give section 
//				information.
//
//		Limitation:
//				* Single-threaded use only.
//				* No COM-style referencing counting available. (yes, I should make this
//				  COM object).
//
//		Initialization of IPEFileWrap Object:
//				Client should call CreatePEFileWrap() routine exported from
//				PEUtility.DLL, passing a pointer to the name of PE file and
//				the OUT parameter to receive the pointer to IPEFileWrap object.
//				Client should check the return value against PEUTILITY_SUCCESS
//				enum value. If it is not success, then you can call	
//				GetLastCreationFailureReason() to find out what went wrong.
// 
//		Service routines provided by Instruction Object:
//
//				The names of functions should tell you what they do.
//
//				GetBase()
//
//				GetCodeSectionOffset()
//				GetCodeSectionSize()
//				GetInitializedDataSectionOffset()
//				GetInitializedDataSectionSize()
//				GetUninitializedDataSectionOffset()
//				GetUninitializedDataSectionSize()
//				GetImportDataSectionOffset()
//				GetImportDataSectionSize()
//				GetExportDataSectionOffset()
//				GetExportDataSectionSize()
//				GetResourceSectionOffset()			
//				GetResourceSectionSize()
//
//				Typically, you use GetBase to get a base address, then
//				call a set of GetXXXOffSet & GetXXXSize.
//				base address + offset makes a "start address" of the
//				section. The size is returned from GetXXXSize.
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

#ifndef PEUTILITY_H
#define PEUTILITY_H

#ifdef PEUTILITY_EXPORTS
#define PEUTILITY_API __declspec(dllexport)
#else
#define PEUTILITY_API __declspec(dllimport)
#endif


class IPEFileWrap 
{
public:
	virtual DWORD	GetBase() = 0;
	virtual DWORD	GetCodeSectionOffset() = 0;				
	virtual UINT	GetCodeSectionSize() = 0;					
	virtual DWORD	GetInitializedDataSectionOffset() = 0;		
	virtual UINT	GetInitializedDataSectionSize() = 0;		
	virtual DWORD	GetUninitializedDataSectionOffset() = 0;
	virtual UINT	GetUninitializedDataSectionSize() = 0;		
	virtual DWORD	GetImportDataSectionOffset() = 0;			
	virtual UINT	GetImportDataSectionSize() = 0;			
	virtual DWORD	GetExportDataSectionOffset() = 0;			
	virtual UINT	GetExportDataSectionSize() = 0;			
	virtual DWORD	GetResourceSectionOffset() = 0;			
	virtual UINT	GetResourceSectionSize() = 0;				
};

enum PEUTILITY_ERROR_CODE
{
	PEUTILITY_SUCCESS		=  1,
	PEUTILITY_FAILURE		=  0,
	OBJECT_ALREADY_CREATED	= -1
};

typedef int (*PPEFILE_FACTORY_FUNC)(char*, IPEFileWrap*);

extern "C" PEUTILITY_API 
int CreatePEFileWrap(char* filename, IPEFileWrap** ppx);

extern "C" PEUTILITY_API
int GetLastCreationFailureReason(char* out_buffer);

#endif //PEUTILITY_H