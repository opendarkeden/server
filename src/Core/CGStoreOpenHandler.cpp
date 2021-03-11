//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreOpenHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreOpen.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Store.h"
	#include "Zone.h"
	#include "skill/SkillUtil.h"

	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCOtherStoreInfo.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStoreOpenHandler::execute (CGStoreOpen* pPacket , Player* pPlayer)
	 
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

	if ( checkZoneLevelToHitTarget(pPC) )
	{
		return;
	}

	Store* pStore = pPC->getStore();
	Assert( pStore != NULL );

	if ( pStore->isOpen() )
	{
		filelog("Store.log", "[%s:%s] 이미 상점이 열려있습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str());
		return;
	}

	pStore->open();
	cout << pPC->getName() << " 의 상점이 열렸습니다." << endl;

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

