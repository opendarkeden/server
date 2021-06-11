//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectPortal.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectPortal.h"

CGSelectPortal::CGSelectPortal () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGSelectPortal::~CGSelectPortal () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSelectPortal::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ZoneID);

	__END_CATCH
}

void CGSelectPortal::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ZoneID);

	__END_CATCH
}

void CGSelectPortal::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSelectPortalHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectPortal::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectPortal(ZoneID " <<(int) m_ZoneID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
