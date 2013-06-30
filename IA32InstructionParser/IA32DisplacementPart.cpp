// IA32DisplacementPart.cpp: implementation of the IA32DisplacementPart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32DisplacementPart.h"
#include "IA32InstructionBody.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32DisplacementPart::IA32DisplacementPart()
	: m_instruction(NULL)
{

}

IA32DisplacementPart::~IA32DisplacementPart()
{

}

void IA32DisplacementPart::Initialize(IA32InstructionBody* instruction)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(instruction), sizeof(void*)) );

	m_instruction = instruction;
}

// ===========================================================
// Reset the "per-instruction" state to the default. Client
// must call this method for each instruction to flush
// previous instruction's state data.
// ===========================================================
void IA32DisplacementPart::Reset()
{
	m_full_displacement = false;
	m_size = 0xCCCCCCCC;
};


// ===========================================================
// Parses displacement data from the stream.
// ===========================================================
byte* IA32DisplacementPart::Parse(const byte* bytestream)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(m_instruction), sizeof(void*)) );
	assert( !IsBadReadPtr(const_cast<byte*>(bytestream), sizeof(byte*)) );

	byte* current_position		= const_cast<byte*>(bytestream);
	//m_no_displacement						= false;

	// ===========================================================
	// Bail out quick if this instruction has not displacement.
	// Take a note about this fact.
	// ===========================================================
	if ( m_size == 0 )
	{
		//m_no_displacement = true;
		return current_position;
	}

	// ===========================================================
	// Read displacement data from the stream. Cast the pointer to
	// one of byte(1), word(2), dword(4) if necessary. When we
	// are reading SEGMENT:OFFSET pair of offset, take a note about
	// it by setting an internal flag.
	// ===========================================================
	switch ( m_size )
	{
		ushort* ptr_word;
		unsigned int*   ptr_doubleword;

		case 1: // 8-bit Displacement
			m_1byte_displacement_data = *current_position;
			break;

		case 2:	// 16-bit Displacement
			{
				ptr_word = reinterpret_cast<ushort*>(current_position);
				m_2byte_displacement_data = *ptr_word;
			}		
			break;

		case 4: // 32-bit displacement - we have two possibilities.
			{
				if ( m_full_displacement == true )
				{
					//
					// segment(16):offset(16) pattern.
					//

					ptr_word = reinterpret_cast<ushort*>(current_position);   
					m_segment_displacement_data	= *ptr_word++;
					m_2byte_displacement_data = *ptr_word;
				}
				else
				{
					//
					// offset(32) pattern.
					//

					ptr_doubleword = reinterpret_cast<unsigned int*>(current_position);
					m_4byte_displacement_data = *ptr_doubleword;
				}
			}
			break;

		case 6: // segment(16):offset(32) pattern
			{
				ptr_word = reinterpret_cast<ushort*>(current_position);   
				m_segment_displacement_data = *ptr_word++;

				ptr_doubleword = reinterpret_cast<unsigned int*>(ptr_word);
				m_4byte_displacement_data = *ptr_doubleword;
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