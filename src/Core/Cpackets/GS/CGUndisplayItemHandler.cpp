//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUndisplayItemHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGUndisplayItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Store.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCRemoveStoreItem.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUndisplayItemHandler::execute (CGUndisplayItem* pPacket , Player* pPlayer)
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

	if ( pPacket->getIndex() > MAX_ITEM_NUM )
	{
		filelog("Store.log", "[%s:%s] (%u) 잘못된 인덱스입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getIndex());
		return;
	}

	BYTE result = pStore->removeStoreItem( pPacket->getIndex() );
	if ( result != 0 )
	{
		filelog("Store.log", "[%s:%s] (%u) 아이템을 뺄 수 없습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), result);
		return;
	}
	
	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pGamePlayer->sendPacket( &gcInfo );

	if ( pStore->isOpen() )
	{
		GCRemoveStoreItem gcRemove;
		gcRemove.setOwnerObjectID( pPC->getObjectID() );
		gcRemove.setIndex( pPacket->getIndex() );
		pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcRemove, pPC );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

