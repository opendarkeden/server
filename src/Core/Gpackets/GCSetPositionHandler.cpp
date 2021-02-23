//----------------------------------------------------------------------
//
// Filename    : GCSetPositionHandler.cc
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GCSetPosition.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif

//----------------------------------------------------------------------
// 
// GCSetPositionHander::execute
//
//----------------------------------------------------------------------
void GCSetPositionHandler::execute ( GCSetPosition * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	//cout << "Set Position To ( " 
			<< (int)pPacket->getX() << " , " 
			<< (int)pPacket->getY() << " , " 
			<< Dir2String[pPacket->getDir()] 
			<< " )";

	pClientPlayer->setXY( pPacket->getX() , pPacket->getY() );

	pClientPlayer->setPlayerStatus( CPS_NORMAL ); 

#endif
	
	__END_DEBUG_EX __END_CATCH
}
