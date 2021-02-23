//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFriendChatting.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCFriendChatting.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
GCFriendChatting::GCFriendChatting()
{

	m_Command = 0;
	m_IsBlack = 0;
	m_IsOnLine = 0;
}
void GCFriendChatting::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_Command );

	BYTE szPlayerName;
	iStream.read( szPlayerName );
	if ( szPlayerName>32 )
		throw InvalidProtocolException("PlayerName Lenth error");
	iStream.read(m_PlayerName, szPlayerName);

	WORD szMessage;
	iStream.read( szMessage);
	if ( szMessage > 128 )
		throw InvalidProtocolException("Too large Message length");
	iStream.read( m_Message , szMessage );

	iStream.read(m_IsBlack);
	iStream.read(m_IsOnLine);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Command );

	BYTE szPlayerName = m_PlayerName.size();
	if(szPlayerName>32)
		throw InvalidProtocolException("Too Large PlayerName Lenth");
	oStream.write(szPlayerName);
	oStream.write(m_PlayerName);

	WORD szMessage = m_Message.size();
	if(szMessage>512)
		throw InvalidProtocolException("Too Large Message Lenth");
	oStream.write(szMessage);
	oStream.write(m_Message);

	oStream.write(m_IsBlack);
	oStream.write(m_IsOnLine);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		 
	GCFriendChattingHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCFriendChatting::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCFriendChatting("
		<< "Command:" << m_Command 
		<< ",PlayerName:" << m_PlayerName
		<< ",Message:" << m_Message 
		<< ",m_IsBlack:"<<m_IsBlack
		<< ",m_IsOnLine:"<<m_IsOnLine
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


