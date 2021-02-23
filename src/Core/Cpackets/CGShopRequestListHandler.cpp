//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestListHandler.cpp
// Written By  : 김성민
// Description : CGShopRequestList의 핸들러이다.
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestList.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "PlayerCreature.h"

	#include "quest/TriggerManager.h"
	#include "quest/Trigger.h"
	#include "quest/Condition.h"
	#include "quest/Action.h"

	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCShopList.h"
	#include "Gpackets/GCShopListMysterious.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestListHandler::execute(CGShopRequestList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 패킷에서 정보를 뽑아낸다.	
	ObjectID_t     NPCID = pPacket->getObjectID();
	ShopRackType_t type  = pPacket->getRackType();

	// 파라미터 및 패킷에서 뽑아낸 정보를 가공
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature*   pPC         = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Zone*       pZone       = pPC->getZone();
	Creature*   pNPCBase    = NULL;
	
	/*
	try
	{
		pNPCBase = pZone->getCreature(NPCID);
	}
	catch (NoSuchElementException & nsee)
	{
		pNPCBase = NULL;
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID);

	if (pNPCBase == NULL || pNPCBase->isNPC() == false)
	{
		GCNPCResponse gcNPCResponse;
		pPlayer->sendPacket(&gcNPCResponse);
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);

	if (type == SHOP_RACK_SPECIAL)
	{
		// 상품의 리스트를 패킷에다 작성한다.
		GCShopList pkt;
		pkt.setNPCShopType(pNPC->getShopType());
		pkt.setObjectID(NPCID);
		pkt.setShopVersion(pNPC->getShopVersion(type));
		pkt.setShopType(type);

		for (BYTE i=0; i<SHOP_RACK_INDEX_MAX; i++) 
		{
			// 각각의 아이템 정보를 적는다.
			Item* pItem = pNPC->getShopItem(type, i);
			if (pItem != NULL) pkt.setShopItem(i, pItem);
		}

		pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
//		pkt.setMarketCondSell(pNPC->getMarketCondSell());
		pkt.setMarketCondSell(pNPC->getTaxRatio(pPC));

		// 패킷을 보내자.
		pPlayer->sendPacket(&pkt);
	}
	else if (type == SHOP_RACK_MYSTERIOUS)
	{
		// 상품의 리스트를 패킷에다 작성한다.
		GCShopListMysterious pkt;
		pkt.setObjectID(NPCID);
		pkt.setShopVersion(pNPC->getShopVersion(type));
		pkt.setShopType(type);

		for (BYTE i=0; i<SHOP_RACK_INDEX_MAX; i++) 
		{
			// 각각의 아이템 정보를 적는다.
			Item* pItem = pNPC->getShopItem(type, i);
			if (pItem != NULL)
				pkt.setShopItem(i, pItem);
		}

		pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
//		pkt.setMarketCondSell(pNPC->getMarketCondSell());
		pkt.setMarketCondSell(pNPC->getTaxRatio(pPC));

		// 패킷을 보내자.
		pPlayer->sendPacket(&pkt);
	}
	else 
	{
		throw ProtocolException("NORMAL shop item list not allowed!!!");
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
