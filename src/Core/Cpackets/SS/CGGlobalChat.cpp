//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGlobalChat.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGGlobalChat.h"

void CGGlobalChat::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
	iStream.read( m_Color );
		
	BYTE szMessage;
	iStream.read(szMessage);
	if (szMessage == 0) throw InvalidProtocolException("szMessage == 0");
	if (szMessage > 128) throw InvalidProtocolException("too large message length");
	iStream.read(m_Message , szMessage);

	__END_CATCH
}

void CGGlobalChat::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write( m_Color );
	
	BYTE szMessage = m_Message.size();

	if (szMessage == 0) throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128) throw InvalidProtocolException("too large message length");

	oStream.write(szMessage);

	oStream.write(m_Message);

	__END_CATCH
}

void CGGlobalChat::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGGlobalChatHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGGlobalChat::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGGlobalChat(Color:" << m_Color << ",Message:" << m_Message << ")" ;
	return msg.toString();

	__END_CATCH
}
