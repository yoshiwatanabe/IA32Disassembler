// IA32ImmediatePart.cpp: implementation of the IA32ImmediatePart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32ImmediatePart.h"
#include "IA32InstructionBody.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32ImmediatePart::IA32ImmediatePart()
	: m_instruction(NULL)
{

}

IA32ImmediatePart::~IA32ImmediatePart()
{

}

void IA32ImmediatePart::Initialize(IA32InstructionBody* instruction)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(instruction), sizeof(void*)) );

	m_instruction = instruction;
}

byte* IA32ImmediatePart::Parse(const byte* bytestream)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(m_instruction), sizeof(void*)) );
	assert( !IsBadReadPtr(const_cast<byte*>(bytestream), sizeof(byte*)) );

	byte* current_position		= const_cast<byte*>(bytestream);

	// ===========================================================
	// Bail out quick if this instruction has not immediate.
	// Take a note about this fact.
	// ===========================================================
	if ( m_size == 0 )
	{
		return current_position;
	}

	// ===========================================================
	// Read immediate data from the stream. Cast the pointer to
	// one of byte(1), word(2), dword(4) if necessary. 
	// ===========================================================
	switch ( m_size )
	{
		ushort* ptr_word;
		uint*   ptr_doubleword;

		case 1: // 8-bit Immediate
			m_1byte_immediate_data = *current_position;
			break;

		case 2:	// 16-bit Immediate
			{
				ptr_word = reinterpret_cast<ushort*>(current_position);
				m_2byte_immediate_data = *ptr_word;
			}		
			break;

		case 3: // ENTER Iw, Ib 
			{
				m_word_byte_pair = true;
				ptr_word = reinterpret_cast<ushort*>(current_position);   
				m_2byte_immediate_data = *ptr_word++;

				m_1byte_immediate_data = *(reinterpret_cast<byte*>(ptr_word));
			}
			break;

		case 4: // 32-bit displacement - we have two possibilities.
			{
				ptr_doubleword = reinterpret_cast<uint*>(current_position);
				m_4byte_immediate_data = *ptr_doubleword;
			}
			break;

		default: // size of anything else is an error.
		assert(0);
	}
 
	// ===========================================================
	// Advance the pointer to the location just *passed" the
	// displacement data we parsed in this method.
	// ===========================================================
	current_position += m_size;

	return current_position;
}

void IA32ImmediatePart::Reset()
{
	m_word_byte_pair = false;
	m_size = 0x0;
};

void IA32ImmediatePart::SetSize(int n) 
{ 
	assert( !(n > 4) ); 
	assert( m_size == 0x0 );
	m_size = n; 
};
