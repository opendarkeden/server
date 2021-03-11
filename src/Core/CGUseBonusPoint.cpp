//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseBonusPoint.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseBonusPoint.h"

CGUseBonusPoint::CGUseBonusPoint () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGUseBonusPoint::~CGUseBonusPoint () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUseBonusPoint::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Which);

	__END_CATCH
}

void CGUseBonusPoint::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_Which);

	__END_CATCH
}

void CGUseBonusPoint::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGUseBonusPointHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGUseBonusPoint::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseBonusPoint("
		<< "Which:" << (int)m_Which 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
