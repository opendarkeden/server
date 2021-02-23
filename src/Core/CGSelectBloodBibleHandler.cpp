//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectBloodBibleHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectBloodBible.h"

#ifdef __GAME_SERVER__
	#include "PlayerCreature.h"
	#include "GamePlayer.h"
	#include "BloodBibleBonus.h"
	#include "BloodBibleBonusManager.h"
	#include "BloodBibleSignInfo.h"
	#include "GCBloodBibleSignInfo.h"
	#include "GCSystemMessage.h"
	#include <algorithm>
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectBloodBibleHandler::execute (CGSelectBloodBible* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPC != NULL);

	BloodBibleBonus* pBonus = NULL;

	try
	{
		pBonus = g_pBloodBibleBonusManager->getBloodBibleBonus(pPacket->getBloodBibleID());
		if (pBonus == NULL ) return;
	}
	catch (NoSuchElementException& e )
	{
		return;
	}

	if (pPC->getRace() != pBonus->getRace() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("사용할 수 없는 징표입니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}

	BloodBibleSignInfo* pInfo = pPC->getBloodBibleSign();
	if (pInfo->getOpenNum() <= pInfo->getList().size() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("빈 슬롯이 없습니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}
	
	if (find(pInfo->getList().begin(), pInfo->getList().end(), pPacket->getBloodBibleID() ) != pInfo->getList().end() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("이미 장착하고 있는 징표입니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}

	GCSystemMessage gcSM;
	gcSM.setMessage("피의 성서 징표가 장착되었습니다.");
	pGamePlayer->sendPacket(&gcSM);

	pInfo->getList().push_back(pPacket->getBloodBibleID());
	GCBloodBibleSignInfo gcInfo;
	gcInfo.setSignInfo(pInfo);
	pGamePlayer->sendPacket(&gcInfo);

	pPC->initAllStatAndSend();

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

