//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreCloseHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreClose.h"

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
void CGStoreCloseHandler::execute (CGStoreClose* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Store* pStore = pPC->getStore();
	Assert( pStore != NULL );

	if ( !pStore->isOpen() )
	{
		filelog("Store.log", "[%s:%s] 이미 상점이 닫혀있습니다..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str());
		return;
	}

	pStore->close();
	cout << pPC->getName() << " 의 상점이 닫혔습니다닏." << endl;

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pGamePlayer->sendPacket( &gcInfo );

	GCOtherStoreInfo gcOtherInfo;
	gcOtherInfo.setObjectID( pPC->getObjectID() );
	gcOtherInfo.setRequested(0);
	gcOtherInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcOtherInfo, pPC );

	
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

