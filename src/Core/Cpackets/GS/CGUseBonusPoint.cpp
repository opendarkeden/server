//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseBonusPoint.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseBonusPoint.h"

CGUseBonusPoint::CGUseBonusPoint () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGUseBonusPoint::~CGUseBonusPoint () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUseBonusPoint::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_Which);

	__END_CATCH
}

void CGUseBonusPoint::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_Which);

	__END_CATCH
}

void CGUseBonusPoint::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGUseBonusPointHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGUseBonusPoint::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseBonusPoint("
		<< "Which:" << (int)m_Which 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
