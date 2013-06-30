// IA32PrefixPart.cpp: implementation of the IA32PrefixPart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IA32PrefixPart.h"

const byte IA32PrefixPart::PREFIX_BYTE_ARRAY[] =
{
	0xf3,
	0xf2,
	0xf0,
	0x2e,
	0x36,
	0x3e,
	0x26,
	0x64,
	0x65,
	0x66,
	0x67
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IA32PrefixPart::IA32PrefixPart(uint default_size)
	: m_default_segment_size( default_size )
	, m_default_stack_size( default_size )
	, m_prefix_data( new byte[4] )
{
};


IA32PrefixPart::~IA32PrefixPart()
{
	delete m_prefix_data;	 
}

// ===========================================================
// Parse a stream of bytes that could possibly contain upto 
// 4 types of 'prefixes' as follows. Save prefixe byte(s)
// as they are discovered.
//
// INPUT:	pointer to byte stream to start parsing.
// 
// OUTPUT:	pointer to byte - either just passed prefix byte(s)
//			that we found, or the same location if none is fount.
//
// ===========================================================
byte* IA32PrefixPart::Parse(const byte* bytestream)
{
	assert( !IsBadReadPtr(const_cast<byte*>(bytestream), sizeof(byte*)) );
	assert( m_operand_size_overriden == false );
	assert( m_address_size_overriden == false );

	byte* current_position = const_cast<byte*>(bytestream);

	uint count			= 0;
	const byte* begin	= &PREFIX_BYTE_ARRAY[ 0 ];
	const byte* end		= &PREFIX_BYTE_ARRAY[ sizeof(PREFIX_BYTE_ARRAY) ];

	// ===========================================================
	// We loop up to 4 because 4 byte is maximum number of prefex
	// possibly appear in the stream at a time.
	// An array PREFIX_BYTE_ARRAY contains all prefix bytes. Compare
	// with each, and if we find any match, save and proceed.
	// Otherwise get out.
	// ===========================================================
	while( count < 4 )	
	{
		while ( ( begin != end ) && ( *begin != *current_position ) ) ++begin; 

		
		if ( begin != end )
		{
			m_prefix_data[count] = *current_position;	// save	the byte
			++count;									// bump the counter
			++current_position;							// advance the pointer
		}

		else break; // we must reached the end, so break out.
	}

	return current_position ;
};

// ===========================================================
// Set internal state to default. Clinet must call this for each
// instruction to flush previous state.
// ===========================================================
void IA32PrefixPart::Reset()
{ 
	m_operand_size_overriden = false;
	m_address_size_overriden = false;
};

// ===========================================================
// Tells you the size of 'operand' for the current instruction.
// The valid value is either 16 or 32 (16-bit/32-bit)
// ===========================================================
uint IA32PrefixPart::EffectiveOperandSize()
{
	if ( m_operand_size_overriden )
		return ( m_default_segment_size == 16 ) ? 32 : 16;	
	else
		return m_default_segment_size;
};

// ===========================================================
// Tells you the size of 'address' for the current instruction.
// The valid value is either 16 or 32 (16-bit/32-bit)
// ===========================================================
uint IA32PrefixPart::EffectiveAddressSize()
{
	if ( m_address_size_overriden )
		return ( m_default_segment_size == 16 ) ? 32 : 16;
	else
		return m_default_segment_size;
};

