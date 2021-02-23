//////////////////////////////////////////////////////////////////////
// 
// Filename    : GGServerChat.cpp 
// Written By  : inthesky
// Description : 서버간 Whisper Chat을 수행한다.
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GGServerChat.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GGServerChat::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read command
	//--------------------------------------------------
	BYTE szSender, szReceiver, szMessage;
	
	iDatagram.read( szSender );
    if ( szSender == 0 ) 
        throw InvalidProtocolException( "szSender == 0" );
    if ( szSender > 10 )
        throw InvalidProtocolException( "too long Sender length" );
	iDatagram.read( m_Sender, szSender );
	
	iDatagram.read( szReceiver );
    if ( szReceiver == 0 ) 
        throw InvalidProtocolException( "szReceiver == 0" );
    if ( szReceiver > 10 )
        throw InvalidProtocolException( "too long Receiver length" );
	iDatagram.read( m_Receiver, szReceiver );

	iDatagram.read( m_Color );

	iDatagram.read( szMessage );
	if ( szMessage == 0 )
        throw InvalidProtocolException( "szMessage == 0" );
    if ( szSender > 128 )
        throw InvalidProtocolException( "too long Message length" );
	iDatagram.read( m_Message, szMessage );
			
	iDatagram.read( m_Race );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GGServerChat::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write client IP
	//--------------------------------------------------
	BYTE szSender 	= m_Sender.size();
	BYTE szReceiver	= m_Receiver.size();
	BYTE szMessage 	= m_Message.size();

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender == 0" );
	if ( szSender > 10 )
		throw InvalidProtocolException( "too long Sender length" );

    if ( szReceiver == 0 )
        throw InvalidProtocolException( "szReceiver== 0" );
    if ( szReceiver > 10 )
        throw InvalidProtocolException( "too long Receiver length" );

	if ( szMessage == 0 )
		throw InvalidProtocolException( "szMessage == 0" );
	if ( szMessage > 128 )
		throw InvalidProtocolException( "too long Message length" );

	oDatagram.write( szSender );
	oDatagram.write( m_Sender );
	
	oDatagram.write( szReceiver );
	oDatagram.write( m_Receiver );

	oDatagram.write( m_Color );
	
	oDatagram.write( szMessage );
	oDatagram.write( m_Message );

	oDatagram.write( m_Race );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GGServerChat::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GGServerChatHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GGServerChat::toString () const
    throw ()
{
	StringStream msg;

	msg << "GGServerChat("
		<< ",Sender:" << m_Sender
		<< ",Receiver:" << m_Receiver
		<< ",Color:" << (int)m_Color
		<< ",Message:" << m_Message
		<< ",Race:" << (int)m_Race
		<< ")";

	return msg.toString();
}

