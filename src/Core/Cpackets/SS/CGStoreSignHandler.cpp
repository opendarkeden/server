//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreSignHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreSign.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Store.h"
	#include "Zone.h"
	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCOtherStoreInfo.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStoreSignHandler::execute (CGStoreSign* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

//#ifndef __TEST_SERVER__
//	return;
//#endif

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Store* pStore = pPC->getStore();
	Assert( pStore != NULL );

	if ( pPacket->getSign().size() > MAX_SIGN_SIZE )
	{
		filelog("Store.log", "[%s:%s] (%s) 간판 길이가 너무 깁니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getSign().c_str());
		return;
	}

	pStore->setSign( pPacket->getSign() );

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pGamePlayer->sendPacket( &gcInfo );

	if ( pStore->isOpen() )
	{
		GCOtherStoreInfo gcOtherInfo;
		gcOtherInfo.setObjectID(pPC->getObjectID());
		gcOtherInfo.setRequested(0);
		gcOtherInfo.setStoreInfo( &(pStore->getStoreInfo()) );
		pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcOtherInfo, pPC );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

