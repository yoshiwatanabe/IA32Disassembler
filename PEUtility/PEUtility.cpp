// PEUtility.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "PEUtility.h"
#include "PEFile.h"

// ===========================================================
// Pointer to our only PEFile instance.
// ===========================================================
static PEFile* s_pPEFile;
static std::string s_error_message;


// ===========================================================
// Standard DllMain. We do nothing here.
// ===========================================================
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			delete s_pPEFile;
			break;
    }
    return TRUE;
}

// ===========================================================
// Object creation routine (factory function).
// Only way for client to obtain a IPEFileWrap object is
// to call this routine.
// ===========================================================
extern "C" PEUTILITY_API 
int CreatePEFileWrap(char* filename, IPEFileWrap** ppx)
{
	if ( s_pPEFile != NULL )
	{
		s_error_message  = "An instance of PEFileWrap object is already created.";
		return OBJECT_ALREADY_CREATED;
	}

	try
	{
		s_pPEFile = new PEFile( filename );
		if ( s_pPEFile ) *ppx = s_pPEFile;
		
	}
	catch ( PEFile::Exception )
	{
		PEFile::GetLastError(s_error_message);
		ppx = NULL;
		return PEUTILITY_FAILURE;
	}
	return PEUTILITY_SUCCESS;
}

	   
extern "C" PEUTILITY_API
int GetLastCreationFailureReason(char* out_buffer)
{
	if ( IsBadWritePtr((void*)out_buffer, MAX_PATH) )
		return -1;

	strcpy(out_buffer, s_error_message.c_str());
	return s_error_message.length();
}
