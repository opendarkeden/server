//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReady.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReady.h"

void CGReady::read (SocketInputStream & iStream)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void CGReady::write (SocketOutputStream & oStream) const
	
{
	__BEGIN_TRY
	__END_CATCH
}

void CGReady::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGReadyHandler::execute(this , pPlayer);
		
	__END_CATCH
}
