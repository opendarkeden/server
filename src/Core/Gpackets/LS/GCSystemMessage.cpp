//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSystemMessage.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSystemMessage.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szMessage;

	iStream.read( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 256 )
		throw InvalidProtocolException("too large message length");

	iStream.read( m_Message , szMessage );

	iStream.read( m_Color );

	BYTE t;
	iStream.read( t );
	m_Type = (SystemMessageType)t;

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szMessage = m_Message.size();

	oStream.write( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 256 )
		throw InvalidProtocolException("too large message length");

	oStream.write( m_Message );

	oStream.write( m_Color );

	BYTE t = (BYTE)m_Type;
	oStream.write( t );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSystemMessageHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCSystemMessage::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCSystemMessage("
		<< "Type:" << (int)m_Type 
		<< ",Color:" << m_Color 
		<< ",Message:" << m_Message 
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


