//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashRequestBuyHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStashRequestBuy.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Stash.h"
	#include "PriceManager.h"

	#include "GCNPCResponse.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStashRequestBuyHandler::execute (CGStashRequestBuy* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer*     pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pPC             = pGamePlayer->getCreature();
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pPC);

	BYTE curStashNum = pPlayerCreature->getStashNum();

	// ������ �ִ� �������� �ƽ���� ����
	if (curStashNum >= STASH_RACK_MAX)
	{
		GCNPCResponse failpkt;
		failpkt.setCode(NPC_RESPONSE_STASH_SELL_FAIL_MAX);
		pPlayer->sendPacket(&failpkt);
		return;
	}

	Price_t price = g_pPriceManager->getStashPrice(curStashNum+1);

	// ���� ���ڶ� ������.
	if (pPlayerCreature->getGold() < price)
	{
		GCNPCResponse failpkt;
		failpkt.setCode(NPC_RESPONSE_STASH_SELL_FAIL_MONEY);
		pPlayer->sendPacket(&failpkt);
		return;
	}

	// ������ ������ �� ĭ �÷��ְ�...
	pPlayerCreature->setStashNumEx(curStashNum+1);

	// ���� ���δ�.
	//pPlayerCreature->setGoldEx(pPlayerCreature->getGold() - price);

	// by sigi. 2002.9.4
	pPlayerCreature->decreaseGoldEx(price);

	// ���������� OK ��Ŷ�� �����ش�.
	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_STASH_SELL_OK);
	pPlayer->sendPacket(&okpkt);

#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
