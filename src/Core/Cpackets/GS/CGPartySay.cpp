//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartySay.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartySay.h"

CGPartySay::CGPartySay () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGPartySay::~CGPartySay () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGPartySay::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_Color);
	BYTE szMessage;
	iStream.read(szMessage);
	iStream.read(m_Message, szMessage);
	
	__END_CATCH
}
		    
void CGPartySay::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_Color);
	BYTE szMessage = m_Message.size();
	oStream.write(szMessage);
	oStream.write(m_Message);

	__END_CATCH
}

void CGPartySay::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGPartySayHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPartySay::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPartySay("
		<< "Message :" << m_Message
		<< ")";
	return msg.toString();

	__END_CATCH
}
