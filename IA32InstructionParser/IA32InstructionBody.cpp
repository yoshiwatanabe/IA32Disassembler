// IA32InstructionBody.cpp: implementation of the IA32InstructionBody class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32InstructionBody.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32InstructionBody::IA32InstructionBody()
	: m_size(0)
	, m_raw_instruction(new byte[16])
	, m_member_initialized(false)
{
	assert( !IsBadWritePtr(reinterpret_cast<void*>(m_raw_instruction), sizeof(void*)) );
}

IA32InstructionBody::~IA32InstructionBody()
{

}

// ===========================================================
// Let member objects be aware of who is the boss. (they
// need to report to the boss about what they find out about
// part of instruction they are in charge of.)
// ===========================================================
void IA32InstructionBody::Initialize()
{
	m_opcode.Initialize(this);
	m_modrm.Initialize(this);	
	m_displacement.Initialize(this);
	m_immediate.Initialize(this);

	m_member_initialized = true;
}

// ===========================================================
// RESPONSIBILITY: Dumps the content of the current instruction.
// 
// RETURN: A pointer to byte in the input byte stream where
// next instruction (probably) will start. Returns the input
// pointer if couldn't interpret it.
// ===========================================================
byte* IA32InstructionBody::Parse(const byte* bytestream) 
{
	assert(m_member_initialized);

	m_size					= 0;

	m_prefix.Reset();
	m_opcode.Reset();
	m_modrm.Reset();
	m_displacement.Reset();
	m_immediate.Reset();


	byte* current_position = const_cast<byte*>(bytestream);
	byte* new_position = NULL;
	
	// ===========================================================
	// Parse "prefix".
	// ===========================================================
	new_position = m_prefix.Parse(current_position);

	if ( new_position > current_position )
	{
		saveRowInstructionData(new_position, current_position);
		current_position	= new_position;
	}

	// ===========================================================
	// Parse "opcode".
	// ===========================================================
	new_position = m_opcode.Parse(current_position);	 

	if ( new_position > current_position )
	{
		saveRowInstructionData(new_position, current_position);
		current_position = new_position;
	}

	// ===========================================================
	// Parse "ModR/M".
	// ===========================================================
	new_position = m_modrm.Parse(current_position);

	if ( new_position > current_position )
	{
		saveRowInstructionData(new_position, current_position);
		current_position = new_position;
	}

	// ===========================================================
	// Parse displacement.
	// ===========================================================
	new_position = m_displacement.Parse(current_position);

	if ( new_position > current_position )
	{
		saveRowInstructionData(new_position, current_position);
		current_position = new_position;
	}
	
	// ===========================================================
	// Parse Immediate.
	// ===========================================================
	new_position = m_immediate.Parse(current_position);

	if ( new_position > current_position )
	{
		saveRowInstructionData(new_position, current_position);
		current_position = new_position;
	}

	return current_position; 
};

void IA32InstructionBody::saveRowInstructionData(byte* new_position, byte* current_position)
{
	assert( !IsBadWritePtr((void*)m_raw_instruction, sizeof(void*)) );
	assert( !IsBadReadPtr((void*)new_position, sizeof(void*)) );
	assert( !IsBadReadPtr((void*)current_position, new_position - current_position) );

	memcpy( &m_raw_instruction[m_size],
			current_position,
			new_position - current_position
			);

	m_size += new_position - current_position;
}

uint IA32InstructionBody::GetRawInstructionData(byte* buffer)
{ 
	assert(!IsBadStringPtr( (LPCTSTR)buffer, m_size ) );
	memcpy( buffer, m_raw_instruction, m_size );
	return m_size; 
};
