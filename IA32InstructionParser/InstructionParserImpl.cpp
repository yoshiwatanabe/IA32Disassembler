#include "stdafx.h"
#include "InstructionParserImpl.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InstructionParserImpl::InstructionParserImpl() 
		: m_stream_begin(NULL)
		, m_stream_size(0)
		, m_current_position(NULL)
		, m_new_position(NULL)
{
};

InstructionParserImpl::~InstructionParserImpl() 
{
};

// 
// Set the begining of bytestrem and its maximum size. Parser performs
// parsing on this bytestream. This method must be called prior to
// calling any other methods (such as GetFirstRawInstructionData).
// 
void InstructionParserImpl::Initialize(byte* bytestream, uint stream_size)
{
	assert(!IsBadReadPtr((void*)bytestream, stream_size));
	m_stream_begin = bytestream;
	m_stream_size = stream_size;
	m_instruction_body.Initialize();
};


// 
// Provide client with a stream of raw data that makes a complete
// single instruction. Return value indicates the number of bytes
// of the raw data.
//
// This GetFirstXXX method must be called first time. After that,
// client can typicaly set up a loop, testing against NO_MORE_INSTRUCTION
// in the return value. use GetNextXXX emthod to continue parsing.
// 
int InstructionParserImpl::GetFirstRawInstructionData(byte* buffer)
{ 
	assert(!IsBadWritePtr((void*)buffer, MINIMUM_BUFFER_SIZE));
	assert(m_stream_begin != NULL);
	assert(m_stream_size != 0);

	// ===========================================================
	// Set parsing pointers to the initial location - begining of
	// the stream of bytes.
	// ===========================================================
	m_current_position	= m_stream_begin;
	m_new_position		= m_stream_begin;

	byte	temp_buffer[MINIMUM_BUFFER_SIZE];
	int		raw_data_size = 0;

	// ===========================================================
	// Start the actual parsing at the current location in the 
	// stream. If new position is greater than the postion passed,
	// we got some data parsed, so get the "raw data" and
	// copy the data to OUT parameter "buffer".
	// ===========================================================
	m_new_position = m_instruction_body.Parse(m_current_position);
	if ( m_new_position > m_current_position )
	{
		raw_data_size = m_instruction_body.GetRawInstructionData(temp_buffer);

		if ( ( raw_data_size > 0 ) && ( raw_data_size <= MINIMUM_BUFFER_SIZE ) ) 
		{
			memcpy( buffer, temp_buffer, raw_data_size );
		}

		m_current_position = m_new_position;
	}
	else if ( m_new_position == m_current_position )
	{
		// ===========================================================
		// If parser couln't interpret the byte, we copy that byte
		// to OUT parameter "buffer". Client will know that parsing
		// failed by looking at the return value being euqal to 0.
		// ===========================================================
		memcpy(buffer, m_current_position, 1 );
		m_new_position = ++m_current_position;
	}
	else assert(0); // new_position < current_position should never occur.

	return raw_data_size; 
};

// 
// Provide client with a stream of raw data that makes a complete
// single instruction. Return value indicates the number of bytes
// of the raw data.
//
// This GetNextXXX method must be called after GetFirstXXX method
// is called. client can typicaly set up a loop, testing against 
// NO_MORE_INSTRUCTION in the return value.
//
// RETURN:	if ( 1 ... n )
//			data is copied. Size is equal to return value.
//
//			if (0)			
//			indicates that the byte at the current location
//			couln't be interpreted. That byte is still 
//			stored in the OUT parameter 'buffer'. This is
//			not a fatal error, so you can continue calling
//			this method.
//
//			if ( NO_MORE_INSTRUCTION )
//			Indicates that we reached to the end of bytestream
//			the client gave. No more data to parse so client
//			should quite calling this method here.
// 
int InstructionParserImpl::GetNextRawInstructionData(byte* buffer)
{ 
	assert(!IsBadWritePtr((void*)buffer, MINIMUM_BUFFER_SIZE));
	assert(m_stream_begin != NULL);
	assert(m_stream_size != 0);

	if 	( m_current_position >= m_stream_begin + m_stream_size )
	{
		return NO_MORE_INSTRUCTION;
	}

	byte	temp_buffer[MINIMUM_BUFFER_SIZE];
	int		raw_data_size = 0;

	// ===========================================================
	// Start the actual parsing at the current location in the 
	// stream. If new position is greater than the postion passed,
	// we got some data parsed, so get the "raw data" and
	// copy the data to OUT parameter "buffer".
	// ===========================================================
	m_new_position = m_instruction_body.Parse(m_current_position);
	if ( m_new_position > m_current_position )
	{
		raw_data_size = m_instruction_body.GetRawInstructionData(temp_buffer);

		if ( ( raw_data_size > 0 ) && ( raw_data_size <= MINIMUM_BUFFER_SIZE ) ) 
		{
			memcpy( buffer, temp_buffer, raw_data_size );
		}

		m_current_position = m_new_position;
	}
	else if ( m_new_position == m_current_position )
	{
		// ===========================================================
		// If parser couln't interpret the byte, we copy that byte
		// to OUT parameter "buffer". Client will know that parsing
		// failed by looking at the return value being euqal to 0.
		// ===========================================================
		memcpy(buffer, m_current_position, 1 );
		m_new_position = ++m_current_position;
	}
	else assert(0); // new_position < current_position should never occur.

	return raw_data_size; 
};
