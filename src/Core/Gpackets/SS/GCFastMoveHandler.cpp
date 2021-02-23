//--------------------------------------------------------------------------------
//
// Filename    : GCFastMoveHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GCFastMove.h"
#include "Player.h"

#ifdef __GAME_CLIENT__
	#include "Cpackets/CGFastMove.h"
	#include "ClientPlayer.h"
#endif


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCFastMoveHandler::execute ( GCFastMove * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	#if __LINUX__

//		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		//cout << "ObjectID[" << pPacket->getObjectID() << "] move to (" 
			 << (int)pPacket->getX() << "," << (int)pPacket->getY() << ")" << endl;

	#elif __WINDOW__

		AfxMessageBox( pPacket->toString().c_str() );

	#endif

#endif

	__END_DEBUG_EX __END_CATCH
}
