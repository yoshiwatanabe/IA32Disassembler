// ****************************************************************************
// File:		IA32ModrmPart.h
// Purpose: 	To contain the declaration of a class IA32ModrmPart. 
//				
//				IA32ModrmPart represents "MorR/M" as well as optional
//				SIB byte of an instruction. 
// Author:		Yoshi Watanabe
//
// Log:			1/15/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef IA32MODRM_PART_H
#define IA32MODRM_PART_H

class IA32InstructionBody;

class IA32ModrmPart  
{
	// ===========================================================
	// Data members.
	// ===========================================================
	IA32InstructionBody *	m_instruction;		 

	bool m_required;
	bool m_sib_accompanies;
	byte m_modrm_data;
	byte m_sib_data;

	// ===========================================================
	// Internal helper functions.
	// ===========================================================
	uint findDisplacementDataSize();
	uint findImmediateDataSize();

public:
	IA32ModrmPart();
	~IA32ModrmPart();

	void Initialize(IA32InstructionBody* instruction);
	byte* Parse(const byte* bytestream);
	void Reset();
	void SetRequired() { m_required = true; };
};

#endif //IA32MODRM_PART_H
