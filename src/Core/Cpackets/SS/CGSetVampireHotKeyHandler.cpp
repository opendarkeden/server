//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSetVampireHotKeyHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSetVampireHotKey.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
//	#include "Vampire.h"
//	#include "Slayer.h"
//	#include "Zone.h"
#endif

void CGSetVampireHotKeyHandler::execute (CGSetVampireHotKey* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

/*	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

//	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) {

	// 이 상태에서는 크리처가 옳게 로딩되었어야 하므로, NULL 이 아니어야 한다.
	// PLAYER_INGAME 자체가 크리처 로딩이 성공되었음을 의미한다.
	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	if (pCreature->isVampire()) {
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		for(int i = 0; i < 8; i++) {
			pVampire->setHotKey(i, pPacket->getHotKey(i));
		}
	}
	
//	}*/

#endif

	__END_DEBUG_EX __END_CATCH
}
