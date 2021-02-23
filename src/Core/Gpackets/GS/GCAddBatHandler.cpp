//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBatHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCAddBat.h"

void GCAddBatHandler::execute ( GCAddBat * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pPacket->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pPacket->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
