//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPhoneSay.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPhoneSay.h"

void CGPhoneSay::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	BYTE szMessage;

	iStream.read(m_SlotID);

	iStream.read(szMessage);

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	iStream.read(m_Message , szMessage);

	__END_CATCH
}
		    
void CGPhoneSay::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
	oStream.write(m_SlotID);
		
	BYTE szMessage = m_Message.size();

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	oStream.write(szMessage);

	oStream.write(m_Message);

	__END_CATCH
}

void CGPhoneSay::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGPhoneSayHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGPhoneSay::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPhoneSay("
		<< "SlotID :" << (int)m_SlotID
		<< ",Message:" << m_Message
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
