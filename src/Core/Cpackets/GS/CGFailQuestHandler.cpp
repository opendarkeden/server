//////////////////////////////////////////////////////////////////////////////
// Filename    : CGFailQuestHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGFailQuest.h"

#ifdef __GAME_SERVER__

#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "mission/EventQuestAdvance.h"
#include "mission/QuestManager.h"
#include "mission/QuestInfoManager.h"

#include "Gpackets/GCNPCResponse.h"

#include <cstdio>

#endif	// __GAME_SERVER__

void CGFailQuestHandler::execute (CGFailQuest* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	GamePlayer* pGP = dynamic_cast<GamePlayer*>( pPlayer );
	Assert( pGP != NULL );
		
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());

	pPC->getQuestManager()->adjustQuestStatus();

	QuestMessage code;
	if ( pPacket->isFail() )
		code = pPC->getQuestManager()->failQuest();
	else
		code = pPC->getQuestManager()->cancelQuest();

	if ( code == CANCEL_SUCCESS )
	{
		pPC->sendCurrentQuestInfo();

		//cout << "Quest 시작 " << pPC->getName() << " " << pPacket->getQuestID() << endl;
	}
	else
	{
		//cout << "Quest 시작 실패 " << pPC->getName() << " " << (int)code << endl;
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

