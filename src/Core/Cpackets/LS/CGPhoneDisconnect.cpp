//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPhoneDisconnect.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPhoneDisconnect.h"

CGPhoneDisconnect::CGPhoneDisconnect () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGPhoneDisconnect::~CGPhoneDisconnect () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGPhoneDisconnect::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGPhoneDisconnect::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_SlotID);

	__END_CATCH
}

void CGPhoneDisconnect::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGPhoneDisconnectHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPhoneDisconnect::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPhoneDisconnect("
		<< "SlotID: " << (int)m_SlotID
		<< ")";
	return msg.toString();

	__END_CATCH
}
