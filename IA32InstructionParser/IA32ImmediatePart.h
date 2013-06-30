// ****************************************************************************
// File:		IA32ImmediatePart.h
// Purpose: 	To contain the declaration of a class IA32ImmediatePart. 
//				
//				IA32ImmediatePart represents "immediate" data part of 
//				instructions which take immediate data as an operand.
// Author:		Yoshi Watanabe
//
// Log:			1/15/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef IA32IMMEDIATE_PART_H
#define IA32IMMEDIATE_PART_H

class IA32InstructionBody;

class IA32ImmediatePart  
{
	IA32InstructionBody *	m_instruction;

	ushort	m_size;
	byte	m_1byte_immediate_data;
	ushort	m_2byte_immediate_data;
	uint	m_4byte_immediate_data;
	bool	m_word_byte_pair; // for ENTRY opcode

public:
	IA32ImmediatePart();
	~IA32ImmediatePart();
	void Initialize(IA32InstructionBody* instruction);
	byte* Parse(const byte* bytestream);
	void Reset();
	ushort Size() { return m_size; };
	void SetSize(int n); 
};

#endif //IA32IMMEDIATE_PART_H
