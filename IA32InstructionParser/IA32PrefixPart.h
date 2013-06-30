// ****************************************************************************
// File:		IA32ModrmPart.h
// Purpose: 	To contain the declaration of a class IA32ModrmPart. 
//				
//				IA32ModrmPart represents "MorR/M" as well as optional
//				SIB byte of an instruction. 
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

#ifndef IA32PREFIX_PART_H
#define IA32PREFIX_PART_H

class IA32PrefixPart  
{
	static const byte	PREFIX_BYTE_ARRAY[];

	const uint  m_default_segment_size;
	const uint  m_default_stack_size;

	byte* m_prefix_data;
	bool  m_operand_size_overriden;
	bool  m_address_size_overriden;

public:	 
	IA32PrefixPart(uint default_size = 32);
	~IA32PrefixPart();
	BYTE* Parse(const byte* data);
	void Reset();
	uint EffectiveOperandSize();
	uint EffectiveAddressSize();
};

#endif //IA32PREFIX_PART_H
