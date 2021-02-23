//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestStoreInfoHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestStoreInfo.h"

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
void CGRequestStoreInfoHandler::execute (CGRequestStoreInfo* pPacket , Player* pPlayer)
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

	if ( pPacket->getOwnerObjectID() == 0 )
	{
		GCMyStoreInfo gcInfo;
		gcInfo.setStoreInfo( &(pPC->getStore()->getStoreInfo()) );
		pGamePlayer->sendPacket( &gcInfo );
	}
	else
	{
		PlayerCreature* pTargetPC = dynamic_cast<PlayerCreature*>(pPC->getZone()->getCreature(pPacket->getOwnerObjectID()));
		if ( pTargetPC != NULL && pTargetPC->getRace() == pPC->getRace() )
		{
			cout << pTargetPC->getName() << " 의 상점 정보를 보냅니다." << endl;
			GCOtherStoreInfo gcInfo;
			gcInfo.setObjectID( pTargetPC->getObjectID() );
			gcInfo.setRequested(1);
			gcInfo.setStoreInfo( &(pTargetPC->getStore()->getStoreInfo()) );
			pGamePlayer->sendPacket( &gcInfo );
		}
	}
	
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

