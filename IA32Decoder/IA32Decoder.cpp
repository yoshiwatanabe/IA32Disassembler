// ****************************************************************************
// File:		IA32Decoder.cpp
// Purpose: 	
//
// Author:		Yoshi Watanabe
//
// Log:			1/17/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#include <iostream>
#include <string>
#include <windows.h>

#include "PEUtility.h"
#include "SimpleDecoder.h"

void main(int argc, char* argv[])
{
	if ( argc == 1 )
	{
		std::cout << "Usage: SimpleDecoder.exe pefilename\n"
				  << "   where pefilename is a fully qualified path to a PE file.\n";
		return;
	}

	IPEFileWrap* pefile		= NULL;	
	char*		 filename	= argv[1];

	// ===========================================================
	// [1] Create an instance of IPEFileWrap class which will represent
	//     the PE file passed by the user.
	// [2] Extract information about "code section" within the PE file.
	// [3] Create a local object of SimpleDecoder, passing the 
	//     location and size of "code section" that we want it to
	//     decode.
	// [4] Issue a command to "decode" the "code section" we gave to it.
	// ===========================================================

	// [1]
	if ( PEUTILITY_SUCCESS == CreatePEFileWrap( filename, &pefile ) )
	{
		// [2]
		DWORD base_address			= pefile->GetBase();
		DWORD code_section_offset	= pefile->GetCodeSectionOffset();
		UINT  code_section_size		= pefile->GetCodeSectionSize();

		// Add 'base' and 'offset' to form the 'begining' of the section.
		DWORD code_section_begin	= base_address + code_section_offset;

		try
		{
			// [3]
			SimpleDecoder decoder(code_section_begin, code_section_size);

			// [4]
			decoder.DoCosoleOutput();
		}
		catch( SimpleDecoder::Exception )
		{
			// ===========================================================
			// If any exception is thrown by SimpleDecoder, ask SimpleDecoder
			// what was wrong, then show it to the user.
			// ===========================================================
			std::string output_buffer;
			SimpleDecoder::GetLastError(output_buffer);
			std::cout << output_buffer.c_str() << '\n';
		}
	}
	else
	{
		// ===========================================================
		// Show the user why input filename was not accepted.
		// ===========================================================
		char buffer[MAX_PATH];
		if ( GetLastCreationFailureReason(buffer) )
			MessageBox(NULL, buffer, "Decoder", MB_OK);
	}
}
