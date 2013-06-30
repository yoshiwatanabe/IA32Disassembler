// ****************************************************************************
// File:		InstructionParserImpl.h
// Purpose: 	To contain the declaration of a class InstructionParserImpl. 
//				
//				InstructionParserImpl is an implementation class for an abstract
//				base class InstructionParser.
//
//				What this meeans from client's point of view is that when clients
//				call methods of InstructionParser, the call end up in the method
//				implemented by this class.
//
//				From server's point of view, when a pointer to InstructionParser
//				is requested by clients, we give a pointer to an instance of
//				this class, InstructionParserImpl.
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

#ifndef INSTRUCTION_PARSER_IMPL_H
#define INSTRUCTION_PARSER_IMPL_H

#include "IA32InstructionParser.h"
#include "IA32InstructionBody.h"

class InstructionParserImpl : public InstructionParser
{
	IA32InstructionBody	m_instruction_body;

	byte*	m_stream_begin;
	uint	m_stream_size;
	byte*	m_current_position;
	byte*	m_new_position;

public:
	InstructionParserImpl();
	~InstructionParserImpl();

	void Initialize(byte* bytestream, uint stream_size);

	// ===========================================================
	// Implimentation of abstract base class - InstructionParser.
	// ===========================================================
	virtual int GetFirstRawInstructionData(byte* buffer);
	virtual int GetNextRawInstructionData(byte* buffer) ;
};

#endif //INSTRUCTION_PARSER_IMPL_H