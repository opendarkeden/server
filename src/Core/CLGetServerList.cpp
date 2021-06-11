//////////////////////////////////////////////////////////////////////////////
// Filename    : CLGetServerList.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLGetServerList.h"

void CLGetServerList::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	__END_CATCH
}

void CLGetServerList::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CLGetServerList::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
	CLGetServerListHandler::execute(this, pPlayer);
	__END_CATCH
}

