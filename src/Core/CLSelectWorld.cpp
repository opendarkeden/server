//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectWorld.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectWorld.h"

void CLSelectWorld::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_WorldID);

	__END_CATCH
}

void CLSelectWorld::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	
	oStream.write(m_WorldID);

	__END_CATCH
}

void CLSelectWorld::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CLSelectWorldHandler::execute (this , pPlayer);
		
	__END_CATCH
}

