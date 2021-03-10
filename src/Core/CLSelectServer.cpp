//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectServer.h"

void CLSelectServer::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_ServerGroupID);

	__END_CATCH
}

void CLSelectServer::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	
	oStream.write(m_ServerGroupID);

	__END_CATCH
}

void CLSelectServer::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CLSelectServerHandler::execute (this , pPlayer);
		
	__END_CATCH
}

