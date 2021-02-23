//////////////////////////////////////////////////////////////////////////////
// Filename    : CLLogout.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLLogout.h"

void CLLogout::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CLLogout::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CLLogout::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLLogoutHandler::execute (this , pPlayer);
		
	__END_CATCH
}

