// ****************************************************************************
// File:		InstructionParser.h
// Purpose: 	Public declaration/definition for IA32Parser.DLL.
//				
//				The file contains:
//				
//				1. #define of a couple of constant values that client need to know.
//				2. Declaration of an abstract base class (e.g. interface) 
//				   - InstructionParser.
//				3. Declaration of an exported function which provide a pointer
//				   to an implementation of InstructionParser class.
//
//				Include this to your project in order to use IA32Parser.DLL
//				NOTE: currently, the only way to use service provide by
//				IA32Parser.DLL is to LoadLibrary() "IA32Parser.DLL" and then 
//				GetProcAddress() for "CreateInstructionParser".
//				When you use GetProcAddress, you must perform a nasty cast
//				of function pointer to another. For this PFACTORY_FUNCTION type
//				is provided. Use this to cast a generic function pointer
//				returne by GetProcAddress to the signiture of CreateInstructionParser.
//				
//
//
// Service provided by IA32Parser.DLL and its InstructionParser object;
// 
//		General description:
//				InstructionParser object provides "parsing" service for
//				a stream of Intel x86 architecture instruction (IA32) code.
//				
//				The instruction set includes both 16-bit and 32-bit instructions
//				upto Pentium Pro instruction set.
//
//		Limitation:
//				* Floating-point instructions are not yet supported (To be implemented)
//				* MMX is not yet supported (To be implemented).
//
//		Initialization of Instruction Object:
//				Client should call CreateInstructionParser() routine exported from
//				IA32Parser.DLL, passing a pointer to the stream of raw bytes and
//				its size. Typcially, clients obtain these data by reading a 
//				PE file (Portable Executable format file) - a standard executable
//				file format for Win32 platform (Win9x ring3 and all WinNT).
//
//		Service routines provided by Instruction Object:
//				It takes a stream of raw bytes which is supposed to be a series
//				of instructions. It parses, and gives back a part of 
//				raw bytes that comprises a single instruction. The size could
//				range between 1 to 15. (meaning that Intel x86 instruction can be
//				as little as 1 byte, and as big as 15 bytes.
//
//				InstructionParser provies two methods.
//					GetFirstRawInstructionData()
//					GetNextRawInstructionData().
//
//				Both methods takes a pointer to buffer which is allocated
//				by the calling client as OUT parameter. If successful,
//				those methods fills the buffer with raw byte data, for a
//				single current instruction, and returns the size.
//				
//				The valid return values are:
//					- from 1 to n where n is smaller than 15.
//					- exactly 0
//					- exactly -1 (defined as NO_MORE_INSTRUCTION for readability)
//	
//				Only case that require further explanation is when return value
//				was exactly 0. This indicates that the current byte was not
//				interpreted as anything that parser is aware of. This could mean
//				that the byte is one of the instruction that are not implemented
//				yet (e.g. MMX).  Client should just ignore, and keep calling
//				GetNextRawInstructionData until it encounters NO_MORE_INSTRUCTION.
//				Even if 0 is returned, these methods deposit a copy of byte in
//				the OUT parameter buffer so that client can show it to user.
//
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

#ifndef IA32INSTRUCTION_PARSER
#define IA32INSTRUCTION_PARSER

#ifdef	IA32INSTRUCTIONPARSER_EXPORTS
#define IA32PARSER_API __declspec(dllexport)
#else
#define IA32PARSER_API __declspec(dllimport)
#endif

typedef unsigned char byte;
#define MINIMUM_BUFFER_SIZE 32
#define NO_MORE_INSTRUCTION -1


class InstructionParser
{
public:
	virtual int GetFirstRawInstructionData(byte* buffer) = 0;
	virtual int GetNextRawInstructionData(byte* buffer) = 0;
};

typedef InstructionParser* (*PFACTORY_FUNCTION)(byte*, unsigned int);

extern "C" IA32PARSER_API 
InstructionParser* CreateInstructionParser(byte* bytestream, unsigned int stream_size);


#endif //IA32INSTRUCTION_PARSER