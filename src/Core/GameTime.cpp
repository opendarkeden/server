//--------------------------------------------------------------------------------
//
// Filename    : GameTime.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GameTime.h"


//--------------------------------------------------------------------------------
// read from socket input stream
//--------------------------------------------------------------------------------
void GameTime::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_Year );
	iStream.read( m_Month );
	iStream.read( m_Day );
	iStream.read( m_Hour );
	iStream.read( m_Minute );
	iStream.read( m_Second );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket output stream
//--------------------------------------------------------------------------------
void GameTime::write ( SocketOutputStream & oStream ) const
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_Year );
	oStream.write( m_Month );
	oStream.write( m_Day );
	oStream.write( m_Hour );
	oStream.write( m_Minute );
	oStream.write( m_Second );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string GameTime::toString () const 
	throw () 
{
	StringStream msg;
	msg << (int)m_Year << "년 " << (int)m_Month << "월 " << (int)m_Day << "일 " << (int)m_Hour << "시 " << (int)m_Minute << "분 " << (int)m_Second << "초";
	return msg.toString();
}
