//////////////////////////////////////////////////////////////////////////////
// Filename    : CGVisibleHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGVisible.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "ZoneUtil.h"
	#include "Gpackets/GCVisibleFail.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGVisibleHandler::execute (CGVisible* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) {


		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		if (pCreature->isDead()) return;

		Zone* pZone = NULL;
		if ((pZone = pCreature->getZone()) == NULL) return;

		if (!(pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF) 
				|| pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)) 
			)	
		{
			GCVisibleFail gcVisibleFail;
			pGamePlayer->sendPacket(&gcVisibleFail);
			return;
		}
		addVisibleCreature(pZone, pCreature, true);
	}
#endif
	
	__END_DEBUG_EX __END_CATCH
}
