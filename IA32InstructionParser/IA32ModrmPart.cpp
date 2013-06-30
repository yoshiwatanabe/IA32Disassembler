// IA32ModrmPart.cpp: implementation of the IA32ModrmPart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32ModrmPart.h"
#include "IA32InstructionBody.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32ModrmPart::IA32ModrmPart()
	: m_instruction(NULL)
{

}

IA32ModrmPart::~IA32ModrmPart()
{

}

void IA32ModrmPart::Initialize(IA32InstructionBody* instruction)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(instruction), sizeof(void*)) );

	m_instruction = instruction;
}

// ===========================================================
// Interpret the ModR/M byte to see if there will be any
// displacement data following. If so, then return how many
// bytes the displacement size is going to be.
// ===========================================================
uint IA32ModrmPart::findDisplacementDataSize()
{
	const byte RM_FIELD_MASK	= 0x07;
	const byte MOD_FIELD_MASK	= 0xC0;
	const byte MOD_FIELD_00		= 0x00;
	const byte MOD_FIELD_01		= 0x40;
	const byte MOD_FIELD_10		= 0x80;
	const byte MOD_FIELD_11		= 0xC0;

	uint displacement_size		= 0;
	bool address_size_is_32		= false;
	
	if ( m_instruction->Prefix().EffectiveAddressSize() == 32 ) 
		address_size_is_32 = true;

	switch ( m_modrm_data & MOD_FIELD_MASK )
	{
		case MOD_FIELD_00:
			if ( address_size_is_32 )
			{
				if ( ( m_modrm_data & RM_FIELD_MASK ) == 0x05 )
					displacement_size = 4;
			}
			else
			{
				if ( ( m_modrm_data & RM_FIELD_MASK ) == 0x06 )
					displacement_size = 2;
			}
		break;

		case MOD_FIELD_01:
			displacement_size = 1;
		break;

		case MOD_FIELD_10:
			displacement_size = address_size_is_32 ? 4 : 2;
		break;

		case MOD_FIELD_11:
			displacement_size = 0;
		break;

	default:
		;
	}

	return displacement_size;
}

// ===========================================================
// Interpret the ModR/M byte to see if there will be any
// immediate data following. If so, then return how many
// bytes the immeidate size is going to be.
// ===========================================================
uint IA32ModrmPart::findImmediateDataSize()
{
	const byte OPCODE_FIELD_MASK	= 0x38;
	uint immediate_size				= 0;
	bool operand_size_is_32			= false;

	byte opcode = m_instruction->Opcode().OpcodeByte();

	
	if ( m_instruction->Prefix().EffectiveOperandSize() == 32 ) 
		operand_size_is_32 = true;

	// ===========================================================
	// Certain opcode belong to something called "extension group"
	// where REG/OPCODE field (bit #3,4,5) of ModR/M works like
	// a "sub opcode".  There are 10 groups (1 to 0A) but only 1,
	// 2,3,8, and A(or 10 in decimal) MAY take immediate data.
	// ===========================================================
	switch ( m_instruction->Opcode().OpcodeExtensionGroup() )
	{
	case 1:
		{
			if ( opcode == 0x81 )
				immediate_size = operand_size_is_32 ? 4 : 2;
			else
				immediate_size = 1;
		}
		break;

	case 2:
		{
			// Only these two opcode of Group 2 take 1-byte immediate data.
			if ( ( opcode == 0xC0 ) || ( opcode == 0xC1 ) )
				immediate_size = 1;
		}
		break;

	case 3:
		{
			// Only TEST (REG/OPCODE filed of ModR/M byte == 000)
			if ( ( m_modrm_data & OPCODE_FIELD_MASK ) == 0x00 )
			{
				// ===========================================================
				// Either Ib (Immediate-byte) or Iv (Immediate-variable[16 or 32])
				// This is determined by opcode byte (not "REG/OPCODE" field of 
				// MorR/M.
				// ===========================================================
				if ( opcode == 0xF6 )
					immediate_size = 1;
				else if ( opcode == 0xF7 )
					immediate_size = operand_size_is_32 ? 4 : 2;
				else 
					assert(0);
			}
		}
		break;

	case 8:
		immediate_size = 1; // always Ib (Immidiate-byte)
		break;

	case 0x0A:
		immediate_size = 1; // always Ib (Immediate-byte)
		break;

	default:
		immediate_size = 0;
	}
	return immediate_size;
}

// ===========================================================
// Parse a strem of byte to extract ModR/M byte and possible
// SIB byte that immediately follows.
// ===========================================================
byte* IA32ModrmPart::Parse(const byte* bytestream)
{
	assert(!IsBadReadPtr(reinterpret_cast<void*>(m_instruction), sizeof(void*)));
	assert(!IsBadReadPtr(const_cast<byte*>(bytestream), sizeof(byte*)));
	assert(m_sib_accompanies == false);

	byte* current_position = const_cast<byte*>(bytestream);

	// ===========================================================
	// If ModR/M is not required for the current instruction,
	// just bail out.
	// ===========================================================
	if ( ! m_required ) return current_position;

	const byte	MOD_FIELD_NO_SIB	= 0xC0;
	const byte  MOD_FIELD_MASK		= 0xC0;
	const byte	RM_FIELD_SIB		= 0x04;
	const byte  RM_FIELD_MASK		= 0x07;

	m_modrm_data = *current_position;

	// ===========================================================
	// Check if SIB byte will follow this ModR/M byte.
	// ===========================================================
	if ( ( ( m_modrm_data & MOD_FIELD_MASK ) != MOD_FIELD_NO_SIB ) &&
		 ( ( m_modrm_data & RM_FIELD_MASK ) == RM_FIELD_SIB ) 
	   )
	{  
		++current_position;
		m_sib_data = *current_position;
		m_sib_accompanies = true;
	}

	// ===========================================================
	// MorR/M sometiems specify "displacement" as a part of addressing
	// mode (its possible that it takes no displacement at all). 
	// ===========================================================
	m_instruction->Displacement().SetSize(findDisplacementDataSize());

	// ===========================================================
	// Find out about immediate data requirement.
	// ===========================================================
	if ( 0 == m_instruction->Immediate().Size() )
		m_instruction->Immediate().SetSize(findImmediateDataSize());


	return ++current_position;
}

// ===========================================================
// Reset the "per-instruction" state to the default. Client
// must call this method for each instruction to flash
// previous state data.
// ===========================================================
void IA32ModrmPart::Reset()
{
	m_required			= false; 
	m_sib_accompanies	= false;
};
