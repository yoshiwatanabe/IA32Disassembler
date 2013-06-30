// ****************************************************************************
// File:		IA32OpcodePart.h
// Purpose: 	To contain the declaration of a class IA32OpcodePart. 
//				
//				IA32OpcodePart represents "opcode" part of an instruction of Intel
//				ix86 architecture (IA32) instruction set.
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

#ifndef IA32OPCODE_PART_H
#define IA32OPCODE_PART_H

class IA32InstructionBody;

class IA32OpcodePart  
{
	// ===========================================================
	// These bit maps describe "ModR/M byte requirement" for 
	// a given opcode.
	// ===========================================================
	static const ushort ONE_BYTE_OPCODE_MODREF_REQUIREMENT[];
	static const ushort TWO_BYTE_OPCODE_MODREF_REQUIREMENT[];

	// ===========================================================
	// These bit maps describes "Displacement data requirement" 
	// as well as "Displacement data size", if required, for
	// a given opcode.
	// ===========================================================
	static const ushort ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE[];
	static const ushort ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE[];
	static const ushort TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE[];
	static const ushort TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE[];

	// ===========================================================
	// These bit maps describe "Immediate data requirement"
	// as well as "Immediate data size", if required, for
	// a given opcode.
	// ===========================================================
	static const ushort ONE_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE[];
	static const ushort ONE_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE[];
	static const ushort TWO_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE[];
	static const ushort TWO_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE[];

	// ===========================================================
	// Data members.
	// ===========================================================
	IA32InstructionBody *	m_instruction;

	bool m_two_bytes;
	uint m_extension_group_id;
	byte m_opcode_data;

	// ===========================================================
	// Internal Helper Functions.
	// ===========================================================
	void markExtendedOpcode();
	bool isModrefRequired();
	uint findDisplacementDataSize();
	uint findImmediateDataSize();
	bool isBitSetInTable(byte opcode, const ushort* table);

public:
	IA32OpcodePart();
	~IA32OpcodePart();
	void Initialize(IA32InstructionBody* instruction);
	byte* Parse(const byte* bytestream);
	void Reset();
	uint OpcodeExtensionGroup() { return m_extension_group_id; };
	byte OpcodeByte()			{ return m_opcode_data; };
};

#endif //IA32OPCODE_PART_H

