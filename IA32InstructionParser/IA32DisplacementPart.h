// ****************************************************************************
// File:		IA32DisplacementPart.h
// Purpose: 	To contain the declaration of a class IA32DisplacementPart. 
//				
//				IA32DisplacementPart represents "displacement" data part of 
//				instructions which take displacement for calculating effective 
//				address.
// Author:		Yoshi Watanabe
//
// Log:			1/15/99 - created.
// ----------------------------------------------------------------------------
//	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
// ****************************************************************************

#ifndef IA32DISPLACEMENT_PART_H
#define IA32DISPLACEMENT_PART_H

class IA32InstructionBody;

class IA32DisplacementPart  
{
	IA32InstructionBody *	m_instruction;

	uint	m_size;
	byte	m_1byte_displacement_data;
	ushort	m_2byte_displacement_data;
	uint	m_4byte_displacement_data;
	ushort	m_segment_displacement_data;
	bool	m_full_displacement;

public:
	IA32DisplacementPart();
	~IA32DisplacementPart();
	void Initialize(IA32InstructionBody* instruction);
	byte* Parse(const byte* bytestream);
	void Reset();
	void SetFullDisplacement()	{ m_full_displacement = true; };
	uint Size()					{ return m_size; };
	void SetSize(int n)			{ assert( n != 3 ); assert( !(n > 6) ); m_size = n; };
};

#endif //IA32DISPLACEMENT_PART_H
