//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyPositionHandler.cpp
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyPosition.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Gpackets/GCPartyPosition.h"
	#include "Party.h"
	#include "Creature.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyPositionHandler::execute (CGPartyPosition* pPacket , Player* pPlayer)
	     throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		GCPartyPosition gcPartyPosition;
		gcPartyPosition.setName( pCreature->getName() );
		gcPartyPosition.setZoneID( pPacket->getZoneID() );
		gcPartyPosition.setXY( pPacket->getX(), pPacket->getY() );
		gcPartyPosition.setMaxHP( pPacket->getMaxHP() );
		gcPartyPosition.setHP( pPacket->getHP() );

		Party* pParty = g_pGlobalPartyManager->getParty(pCreature->getPartyID());
		if ( pParty != NULL )
		{
			pParty->broadcastPacket( &gcPartyPosition );
		}
	}

#endif

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}
