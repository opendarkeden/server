//--------------------------------------------------------------------------------
//
// Filename    : GCDeleteObjectHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GCDeleteObject.h"

#ifdef __GAME_CLIENT__
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCDeleteObjectHandler::execute ( GCDeleteObject * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	//cout << "Object[" << pPacket->getObjectID() << "] deleted from zone." << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}
