//////////////////////////////////////////////////////////////////////
// 
// Filename    : GGGuildChat.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GGGuildChat.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GGGuildChat::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read command
	//--------------------------------------------------
	iDatagram.read( m_Type );
	iDatagram.read( m_GuildID );

	BYTE szSender;

	iDatagram.read( szSender );

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender == 0" );
	if ( szSender > 10 )
		throw InvalidProtocolException( "too long Sender length" );

	iDatagram.read( m_Sender, szSender );
	iDatagram.read( m_Color );

	BYTE szMessage;

	iDatagram.read( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException( "szMessage == 0" );
	if ( szSender > 128 )
		throw InvalidProtocolException( "too long Message length" );

	iDatagram.read( m_Message, szMessage );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GGGuildChat::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write client IP
	//--------------------------------------------------
	BYTE szSender = m_Sender.size();
	BYTE szMessage = m_Message.size();

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender == 0" );
	if ( szSender > 10 )
		throw InvalidProtocolException( "too long Sender length" );

	if ( szMessage == 0 )
		throw InvalidProtocolException( "szMessage == 0" );
	if ( szMessage > 128 )
		throw InvalidProtocolException( "too long Message length" );

	oDatagram.write( m_Type );
	oDatagram.write( m_GuildID );
	oDatagram.write( szSender );
	oDatagram.write( m_Sender );
	oDatagram.write( m_Color );
	oDatagram.write( szMessage );
	oDatagram.write( m_Message );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GGGuildChat::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GGGuildChatHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GGGuildChat::toString () const
    throw ()
{
	StringStream msg;

	msg << "GGGuildChat("
		<< "GuildID:" << (int)m_GuildID
		<< ",Sender:" << m_Sender
		<< ",Color:" << (int)m_Color
		<< ",Message:" << m_Message
		<< ")";

	return msg.toString();
}

