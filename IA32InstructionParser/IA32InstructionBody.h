// ****************************************************************************
// File:		IA32InstructionBody.h
// Purpose: 	To contain the declaration of a class IA32InstructionBody. 
//				
//				IA32InstructionBody represents an instruction of Intel ix86
//				architecture (IA32) instruction set.
// Author:		Yoshi Watanabe
//
// Log:			1/15/99 - created.
//
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef IA32INSTRUCTION_BODY_H
#define IA32INSTRUCTION_BODY_H

#include "IA32PrefixPart.h"
#include "IA32OpcodePart.h"
#include "IA32ModrmPart.h"
#include "IA32DisplacementPart.h"
#include "IA32ImmediatePart.h"

class IA32InstructionBody  
{
	uint	m_size;
	byte*	m_raw_instruction;
	bool	m_member_initialized;

	IA32PrefixPart			m_prefix;
	IA32OpcodePart			m_opcode;
	IA32ModrmPart			m_modrm;
	IA32DisplacementPart	m_displacement;
	IA32ImmediatePart		m_immediate;
	

	void saveRowInstructionData(byte* new_position, byte* current_position);
											
	// ===========================================================
	// I give these guys "friend" status because I use them
	// to parse a single instruction (which is made up with 
	// components like opcode, ModR/M, etc.), and they sometimes 
	// need to exchange information among themselves.
	// ===========================================================
	friend class IA32OpcodePart;
	friend class IA32ModrmPart;
	friend class IA32DisplacementPart;
	friend class IA32ImmediatePart;

	// ===========================================================
	// Private member access functions provided for my friends.
	// ===========================================================
	IA32PrefixPart&			Prefix()		{ return m_prefix; };
	IA32OpcodePart&			Opcode()		{ return m_opcode; };
	IA32ModrmPart&			Modrm()			{ return m_modrm; };
	IA32DisplacementPart&	Displacement()	{ return m_displacement; };
	IA32ImmediatePart&		Immediate()		{ return m_immediate; };

public:
	IA32InstructionBody();
	~IA32InstructionBody();
	void Initialize();
	byte* Parse(const byte* bytestream);
	uint GetRawInstructionData(byte* buffer); 
};

#endif //IA32INSTRUCTION_BODY_H
