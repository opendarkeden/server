//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartySayHandler.cpp
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartySay.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "Gpackets/GCPartySay.h"
	#include "Party.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartySayHandler::execute (CGPartySay* pPacket , Player* pPlayer)
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

		GCPartySay gcPartySay;
		gcPartySay.setName( pCreature->getName() );
		gcPartySay.setColor( pPacket->getColor() );
		gcPartySay.setMessage( pPacket->getMessage() );

		Party* pParty = g_pGlobalPartyManager->getParty(pCreature->getPartyID());
		if ( pParty != NULL )
		{
			pParty->broadcastPacket( &gcPartySay );
		}
	}

#endif

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}
