// IA32InstructionParser.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "IA32InstructionParser.h"
#include "InstructionParserImpl.h"

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
			break;
    }
    return TRUE;
}

// ===========================================================
// Exactly one "parser object" exist in this DLL server.
// ===========================================================
static InstructionParserImpl	parser;

// ===========================================================
// Object creation routine (a.k.a. factory function?).
// Client has access to 'parser' object only through this 
// routine.
// ===========================================================
extern "C" IA32PARSER_API
InstructionParser* CreateInstructionParser(byte* bytestream, uint stream_size)
{
	parser.Initialize(bytestream, stream_size);
	return &parser;
}

