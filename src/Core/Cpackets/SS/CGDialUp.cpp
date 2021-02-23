//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDialUp.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDialUp.h"

CGDialUp::CGDialUp () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGDialUp::~CGDialUp () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGDialUp::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_PhoneNumber);

	__END_CATCH
}

void CGDialUp::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_PhoneNumber);

	__END_CATCH
}

void CGDialUp::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGDialUpHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGDialUp::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGDialUp("
		<< "PhoneNumber: " << (int)m_PhoneNumber 
		<< ")";
	return msg.toString();

	__END_CATCH
}
