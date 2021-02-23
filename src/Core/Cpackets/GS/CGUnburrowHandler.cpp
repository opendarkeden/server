//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUnburrowHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGUnburrow.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCUnburrowFail.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUnburrowHandler::execute (CGUnburrow* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		// 이 상태에서는 크리처가 옳게 로딩되었어야 하므로, NULL 이 아니어야 한다.
		// PLAYER_INGAME 자체가 크리처 로딩이 성공되었음을 의미한다.
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		if (pCreature->isDead())
			return;

		Zone* pZone = NULL;
		if ((pZone = pCreature->getZone()) == NULL)
			return;
		
		int packetX = pPacket->getX(), packetY = pPacket->getY();
        int x = pCreature->getX(), y = pCreature->getY();
        int minX = max(0, x-1), maxX = min(x+1, pZone->getWidth()-1);
        int minY = max(0, y-1), maxY = min(y+1, pZone->getHeight()-1);

		if (!((minX <= packetX && maxX >= packetX) && (minY <= packetY && maxY >= packetY))) {
			GCUnburrowFail gcUnburrowFail;
			pGamePlayer->sendPacket(&gcUnburrowFail);
			return;
		}
								
		if (!pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			GCUnburrowFail gcUnburrowFail;
			pGamePlayer->sendPacket(&gcUnburrowFail);
			return;
		}
	
		addUnburrowCreature(pZone, pCreature , pPacket->getX() , pPacket->getY() , pPacket->getDir());
	}

#endif
	
	__END_DEBUG_EX __END_CATCH
}
