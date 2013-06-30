// IA32OpcodePart.cpp: implementation of the IA32OpcodePart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32OpcodePart.h"
#include "IA32InstructionBody.h"

// ===========================================================
// This is 16x16 bit map for ModR/M byte requirement for 
// "One Byte Opcode".
// ===========================================================
const ushort IA32OpcodePart::ONE_BYTE_OPCODE_MODREF_REQUIREMENT[] =
{
	0xF0F0,	//0 1111 0000  1111 000*
	0xF0F0,	//1	1111 0000  1111 0000
	0xF0F0,	//2	1111 0000  1111 0000
	0xF0F0,	//3	1111 0000  1111 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x3050,	//6 0011 0000  0101 0000
	0x0000,	//7 0000 0000  0000 0000
	0xFFFF,	//8 1111 1111  1111 1111
	0x0000,	//9 0000 0000  0000 0000
	0x0000,	//A 0000 0000  0000 0000
	0x0000,	//B 0000 0000  0000 0000
	0xCF00,	//C 1100 1111  0000 0000
	0xF000,	//D 1111 00-0  1111 1111
	0x0000,	//E 0000 0000  0000 0000
	0x0303	//F 0-00 0011  0000 0011
};

// ===========================================================
// This is 16x16 bit map for ModR/M byte requirement for 
// "Two Byte Opcode".
// ===========================================================
const ushort IA32OpcodePart::TWO_BYTE_OPCODE_MODREF_REQUIREMENT[] =
{
	0xB000, //0 1-11 --0-  00-0 ---- 
	0x0000,	//1	---- ----  ---- ----
	0xF000,	//2	1111 ----  ---- ----
	0xF000,	//3	1111 ----  ---- ----
	0xFFFF,	//4	1111 1111  1111 1111
	0x0000,	//5 ---- ----  ---- ----
	0xFFF3,	//6 1111 1111  1111 --11
	0x7E03,	//7 -111 1110  ---- --11
	0x0000,	//8 0000 0000  0000 0000
	0xFFFF,	//9	1111 1111  1111 1111
	0x1C1D,	//A	0001 11--  0001 11-1
	0xFF3F,	//B	1111 1111  -011 1111
	0xC100,	//C 11-- ---1  0000 0000
	0x74DD,	//D	-111 -1--  11-1 11-1
	0x64DD,	//E	-11- -1--  11-1 11-1
	0x74EE  //F	-111 -1--  111- 111-
};

// ===========================================================
// One Byte Opcode whose Displacement data size is 1 Byte
// ===========================================================
const ushort IA32OpcodePart::ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0xFFFF,	//7 1111 1111  1111 1111
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000 //exception 9A
	0xA000,	//A 1010 0000  0000 0000
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0xF010,	//E 1111 0000  0001 0000 //exception EA
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// One Byte Opcode whose Displacement data size is 2 or 4 Bytes
// ===========================================================
const ushort IA32OpcodePart::ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x5000,	//A 0101 0000  0000 0000 // MOV Ov
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x00C0,	//E 0000 0000  1100 0000 // CALL Jv
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// Two Byte Opcode whose Displacement data size is 1 Byte
// ===========================================================
const ushort IA32OpcodePart::TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x0000,	//A 0000 0000  0000 0000
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x0000,	//E 0000 0000  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// Two Byte Opcode whose Displacement data size is 2 or 4 bytes
// ===========================================================
const ushort IA32OpcodePart::TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0x0000,	//7 0000 0000  0000 0000
	0xFFFF,	//8 1111 1111  1111 1111 // Long displacement jumps
	0x0000,	//9 0000 0000  0000 0000
	0x0000,	//A 0000 0000  0000 0000
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x0000,	//E 0000 0000  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// One Byte Opcode whose Immediate data size is 1 Byte
// ===========================================================
const ushort IA32OpcodePart::ONE_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE[] =
{
	0x0808,	//0 0000 1000  0000 1000
	0x0808,	//1	0000 1000  0000 1000
	0x0808,	//2	0000 1000  0000 1000
	0x0808,	//3	0000 1000  0000 1000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0030,	//6 0000 0000  0011 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x0080,	//A 0000 0000  1000 0000
	0xFF00,	//B 1111 1111  0000 0000
	0x0200,	//C 0000 0010  0000 0100
	0x0000,	//D 0000 0000  0000 0000
	0x0F00,	//E 0000 1111  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// One Byte Opcode whose Immediate data size is 2 or 4 bytes
// ===========================================================
const ushort IA32OpcodePart::ONE_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE[] =
{
	0x0404,	//0 0000 0100  0000 0100
	0x0404,	//1	0000 0100  0000 0100
	0x0404,	//2	0000 0100  0000 0100
	0x0404,	//3	0000 0100  0000 0100
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x00C0,	//6 0000 0000  1100 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x0040,	//A 0000 0000  0100 0000
	0x00FF,	//B 0000 0000  1111 1111
	0x0100,	//C 0000 0001  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x0000,	//E 0000 0000  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// Two Byte Opcode whose Immediate data size is 1 byte
// ===========================================================
const ushort IA32OpcodePart::TWO_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x0808,	//A 0000 1000  0000 1000
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x0000,	//E 0000 0000  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// Two Byte Opcode whose Immediate data size is 2 or 4 bytes
// ===========================================================
const ushort IA32OpcodePart::TWO_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE[] =
{
	0x0000,	//0 0000 0000  0000 0000
	0x0000,	//1	0000 0000  0000 0000
	0x0000,	//2	0000 0000  0000 0000
	0x0000,	//3	0000 0000  0000 0000
	0x0000,	//4 0000 0000  0000 0000
	0x0000,	//5	0000 0000  0000 0000
	0x0000,	//6 0000 0000  0000 0000
	0x0000,	//7 0000 0000  0000 0000
	0x0000,	//8 0000 0000  0000 0000
	0x0000,	//9 0000 0000  0000 0000
	0x0000,	//A 0000 0000  0000 0000
	0x0000,	//B 0000 0000  0000 0000
	0x0000,	//C 0000 0000  0000 0000
	0x0000,	//D 0000 0000  0000 0000
	0x0000,	//E 0000 0000  0000 0000
	0x0000	//F 0000 0000  0000 0000
};

// ===========================================================
// Look up in the given table to see if a bit is set. The 
// routine uses bytecode parameter to index into 16x16 (256 entry)
// table.
// ===========================================================
bool IA32OpcodePart::isBitSetInTable(byte bytecode, const ushort* table)
{
	byte	row_index;
	byte	col_index;

	row_index = 0xF0 & bytecode;
	row_index = row_index >> 4;
	col_index = 0x0F & bytecode;

	ushort databits = table[row_index];
	uint the_bit;

	switch ( col_index )
	{
		case 0x00: the_bit = databits & 0x8000; break;
		case 0x01: the_bit = databits & 0x4000; break;
		case 0x02: the_bit = databits & 0x2000; break;
		case 0x03: the_bit = databits & 0x1000; break;
		case 0x04: the_bit = databits & 0x0800; break;
		case 0x05: the_bit = databits & 0x0400; break;
		case 0x06: the_bit = databits & 0x0200; break;
		case 0x07: the_bit = databits & 0x0100; break;
		case 0x08: the_bit = databits & 0x0080; break;
		case 0x09: the_bit = databits & 0x0040; break;
		case 0x0A: the_bit = databits & 0x0020; break;
		case 0x0B: the_bit = databits & 0x0010; break;
		case 0x0C: the_bit = databits & 0x0008; break;
		case 0x0D: the_bit = databits & 0x0004; break;
		case 0x0E: the_bit = databits & 0x0002; break;
		case 0x0F: the_bit = databits & 0x0001; break;
		default: assert(0);
	};

	return ( the_bit > 0 ) ? true : false ;
}

// ===========================================================
// Set the "per-instruction" states to default. Client must
// call this method for each instruction to flush the previous
// state.
// ===========================================================
void IA32OpcodePart::Reset()
{ 
	m_two_bytes = false; 
	m_extension_group_id = 0;
};


// ===========================================================
// Returns whether or not ModR/M byte is required for this
// opcode. (In another word, ModR/M byte will follow a given
// opcode byte if this routine returns 'true'.
// ===========================================================
bool IA32OpcodePart::isModrefRequired()
{
	const ushort* table = 
		m_two_bytes ? TWO_BYTE_OPCODE_MODREF_REQUIREMENT 
				    : ONE_BYTE_OPCODE_MODREF_REQUIREMENT;

	if ( isBitSetInTable( m_opcode_data, table ) ) 
		return true;
	else
		return false;
}

// ===========================================================
// Find out the size of displacement, including none, solely
// based on "opcode" part of the instruction. (implies that
// other part of instruction usch as ModR/M can specify
// displacement.
// ===========================================================
uint IA32OpcodePart::findDisplacementDataSize()
{
	byte opcode = m_opcode_data;
	bool operand_size_32 = false;
	

	// ===========================================================
	// 
	// ===========================================================
	if ( m_instruction->Prefix().EffectiveAddressSize() == 32 ) 
		 operand_size_32 = true;

	if ( ( opcode == 0x9A ) || ( opcode == 0xEA ) )
	{
		m_instruction->Displacement().SetFullDisplacement();
		return  operand_size_32 ?  6 : 4;
	}

	// ===========================================================
	// [1] This is "One Byte Opcode"
	// [2] This opcode takes 1 byte immediate.
	// [3] This opcode takes either 4 or 2 byte immediate.
	// [4] This is "Two Byte Opcode"
	// [5] This opcode takes 1 byte immediate.
	// [6] This opcode takes 4 or 2 byte immediate.
	// ===========================================================
	
	if ( m_two_bytes == false )		// [1]

	{
		if ( isBitSetInTable( opcode, ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE ) )
		{
			return 1;						// [2]
		}

		if ( isBitSetInTable( opcode, ONE_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE ) )
		{
			return operand_size_32 ? 4 : 2;	// [3]
		}
	}
	else									// [4]
	{
		if ( isBitSetInTable( opcode, TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_BYTE ) )
		{
			return 1;						// [5]
		}

		if ( isBitSetInTable( opcode, TWO_BYTE_OPCODE_DISPLACEMENT_SIZE_VARIABLE ) )
		{
			return operand_size_32 ? 4 : 2;	// [6]
		}
	}

	return 0;
}

uint IA32OpcodePart::findImmediateDataSize()
{
	byte opcode				= m_opcode_data;
	bool operand_size_32	= false;

	if ( m_instruction->Prefix().EffectiveOperandSize() == 32 ) 
		 operand_size_32 = true;

	// ===========================================================
	// Handle special cases first.
	// ===========================================================
	if ( ( opcode == 0xC2 ) || ( opcode == 0xCA ) )
	{
		// RET Iw
		// RET far Iw
		return  2;
	}

	if ( opcode == 0xC8 )
	{
		// ===========================================================
		// Come back to this.  ENTER takes WORD, byte
		// ===========================================================
		return 3;
	}
								  
	// ===========================================================
	// [1] This is "One Byte Opcode"
	// [2] This opcode takes 1 byte immediate.
	// [3] This opcode takes either 4 or 2 byte immediate.
	// [4] This is "Two Byte Opcode"
	// [5] This opcode takes 1 byte immediate.
	// [6] This opcode takes 4 or 2 byte immediate.
	// ===========================================================

	if ( m_two_bytes == false )		// [1]
	{
		if ( isBitSetInTable( opcode, ONE_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE ) )
		{
			return 1;						// [2]
		}

		if ( isBitSetInTable( opcode, ONE_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE ) )
		{
			return operand_size_32 ? 4 : 2;	// [3]
		}
	}
	else									// [4]
	{		
		if ( isBitSetInTable( opcode, TWO_BYTE_OPCODE_IMMEDIATE_SIZE_BYTE ) )
		{
			return 1;						// [5]
		}

		if ( isBitSetInTable( opcode, TWO_BYTE_OPCODE_IMMEDIATE_SIZE_VARIABLE ) )
		{
			return operand_size_32 ? 4 : 2; // [6]
		}
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32OpcodePart::IA32OpcodePart()
	: m_instruction(NULL)
	, m_two_bytes(false)
{
}

IA32OpcodePart::~IA32OpcodePart()
{
}

void IA32OpcodePart::Initialize(IA32InstructionBody* instruction)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(instruction), sizeof(void*)) );

	m_instruction = instruction;
}

// ===========================================================
// RESPONSIBILITY:
// IA32OpcodePart::Parse method is respondible for:
// 
// - parsing opcode byte(s)
// - interpreting the parsed opcode byte(s) to:
//   - set flag to indicate that ModR/M should follow
//   - set flag to indicate that displacement should follow
//   - set flag to indicate that immediate data should follow.
//
// 
// - What is NOT this mothod's responsibility.
// Notice that it is not this methd's responsibility to parse
// ModR/M byte, displacement byte(s), and immediate data byte(s).
// All it dose is to set flag to 'true' to indicate that 
// parsing for these elements is required for a particular opcode.
//
// - Location of flags.
// Flags it may set is maintained by 'instruction' object, not
// this object. 'instruction' object must act in accordance
// with these flags.
// 
// - Collaboration with other objects.
// This method set these flags solely based on what it can 
// find out from opcdes, but nothing else. For instance, ModR/M
// byte also indicate that it needs displacement byte(s), so
// object responsible for parsing ModR/M would also work with
// the flags.
// ===========================================================
byte* IA32OpcodePart::Parse(const byte* bytestream)
{
	assert( !IsBadReadPtr(reinterpret_cast<void*>(m_instruction), sizeof(void*)) );
	assert( !IsBadReadPtr(const_cast<byte*>(bytestream), sizeof(byte*)) );
	assert( m_two_bytes == false );

	byte* current_position = const_cast<byte*>(bytestream);

	// ===========================================================
	// 0x0F is the "Two Byte Opcode" escape byte.
	// If this byte is found, advance the position to the following
	// byte, which is actual Opcode.
	// ===========================================================
	if ( *current_position == 0x0F ) 
	{
		++current_position;
		m_two_bytes = true;
	}

	m_opcode_data = *current_position;

	// ===========================================================
	// Check if this opcode is "extended opcode".
	// ===========================================================
	markExtendedOpcode();//(current_position);

	// ===========================================================
	// Find out if a ModR/M byte will be following this opcode.
	// If so, let 'instruction' object be aware about this fact so 
	// that he will parse the stream to extract ModR/M byte.
	// ===========================================================
	if ( isModrefRequired())//(current_position) )
		m_instruction->Modrm().SetRequired();
 

	// ===========================================================
	// Find out if any displacement should follow.
	// If so, then also find out how big it is (1,2 or 4 bytes).
	// Let 'instruction' object be aware about this fact so that
	// he will parse the stream, looking for displacement. 
	// ===========================================================
	m_instruction->Displacement().SetSize ( 
		findDisplacementDataSize()//(current_position) 
										  );

	// ===========================================================
	// Find out if any immediate data should follow. 
	// If so, then also find out how big it is (1,2 or 4 bytes).
	// Let 'instruction' object be aware about this fact so that
	// he will parse the stream, looking for immediate data. 
	// ===========================================================
	m_instruction->Immediate().SetSize(
		findImmediateDataSize()//(current_position) 
									  );

	return ++current_position;
}

// ===========================================================
// Check to see if this opcode is "extended opcode". This
// kind of opcode has "sub-opcode" in ModR/M byte. That means
// determining opcode is defered until MorR/M byte is analyzed.
// ===========================================================
void IA32OpcodePart::markExtendedOpcode()//(byte* pOpcode)
{
	//assert( !IsBadReadPtr(reinterpret_cast<void*>(pOpcode), sizeof(void*)) );

	uint opcode;
	//opcode = static_cast<uint>(*pOpcode);
	opcode = m_opcode_data;

	// ===========================================================
	// [1] "One Byte opcode"
	// [2] Check to see if the opcode belong to any group.
	// [3] "Two Byte opcode"
	// [4] Check to see if the opcode belong to any group.
	// ===========================================================
	if ( ! m_two_bytes )	// [1]
	{
		switch ( opcode )		// [2]
		{
			case 0x80: case 0x81: 
			case 0x82: case 0x83:
			m_extension_group_id = 1;
			break;

			case 0xC0: case 0xC1: 
			case 0xD0: case 0xD1: 
			case 0xD2: case 0xD3:
			m_extension_group_id = 2;
			break;

			case 0xF6: case 0xF7:
			m_extension_group_id = 3;
			break;

			case 0xFE:
			m_extension_group_id = 4;
			break;

			case 0xFF:
			m_extension_group_id = 5;
			break;

			default:
			m_extension_group_id = 0;
		}
	}
	else					// [3]
	{
		switch ( opcode )	// [4]
		{
			case 0x00:
			m_extension_group_id = 6;
			break;

			case 0x01:
			m_extension_group_id = 7;
			break;

			case 0xC7:
			m_extension_group_id = 9;
			break;

			case 0x71: case 0x72: case 0x73:
			m_extension_group_id = 0x0A;
			break;

			default:
			m_extension_group_id = 0;
		}
	}
}

