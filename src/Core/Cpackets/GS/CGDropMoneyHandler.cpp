//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDropMoneyHandler.cc
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDropMoney.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "LogClient.h"
	#include "ItemFactoryManager.h"
	#include "VariableManager.h"

	#include "item/Money.h"

	#include "Gpackets/GCDeleteandPickUpOK.h"
	#include "Gpackets/GCDeleteObject.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDropMoneyHandler::execute (CGDropMoney* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG	

#ifdef __GAME_SERVER__

	// -_-; 무시
//	return;
	throw DisconnectException( "돈은 버릴 수 없습니다." );

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pPC         = pGamePlayer->getCreature();
		Gold_t      amount      = pPacket->getAmount();
		Slayer*     pSlayer     = NULL;
		Vampire*    pVampire    = NULL;
		Ousters*    pOusters    = NULL;
		Zone*       pZone       = NULL;
		ZoneCoord_t ZoneX       = pPC->getX();
		ZoneCoord_t ZoneY       = pPC->getY();

		if (amount == 0)
		{
			// 현재로서는 걍 리턴한다.
			// 돈 떨어뜨리기를 실패했다는 패킷을 만들어야 하는 걸까?
			return;
		}

		if (pPC->isSlayer()) 
		{
			pSlayer = dynamic_cast<Slayer*>(pPC);
			pZone   = pSlayer->getZone();
		}
		else if (pPC->isVampire())
		{
			pVampire = dynamic_cast<Vampire*>(pPC);
			pZone    = pVampire->getZone();
		}
		else if (pPC->isOusters())
		{
			pOusters = dynamic_cast<Ousters*>(pPC);
			pZone    = pOusters->getZone();
		}
		else throw ProtocolException("CGDropMoneyHandler::execute() : 알 수 없는 플레이어 크리쳐.");

		// 플레이어가 떨어뜨리고자 하는 액수만큼의 돈을 가지고 있는지 확인한다.
		Item* pItem = NULL;
		list<OptionType_t> optionNULL;
		if (pPC->isSlayer())
		{
			if (pSlayer->getGold() < amount)  return;

			pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MONEY, 0, optionNULL);
		}
		else if (pPC->isVampire())
		{
			if (pVampire->getGold() < amount) return;

			pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MONEY, 1, optionNULL);
		}
		else if (pPC->isOusters())
		{
			if (pOusters->getGold() < amount) return;

			pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MONEY, 2, optionNULL);
		}

		// 돈 아이템을 생성한다.
	
		dynamic_cast<Money*>(pItem)->setAmount(amount);

		// 돈 아이템을 등록한다.
		pZone->getObjectRegistry().registerObject(pItem);

		// 돈을 존에다 떨어뜨린다.
		TPOINT pt = pZone->addItem(pItem, ZoneX, ZoneY);
		if (pt.x != -1)
		{
			//pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);	
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='', Storage=%d, StorageID=%lu, X=%d, Y=%d", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
			pItem->tinysave(pField);

			//pItem->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

			// 돈로그 남길 액수면 돈로그 남긴다
			if ( amount >= g_pVariableManager->getMoneyTraceLogLimit() )
			{
				char zoneName[15];
				sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), ZoneX, ZoneY);
				remainMoneyTraceLog( pPC->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP, amount);
			}


			log(LOG_DROP_MONEY, pPC->getName(), "", pItem->toString());
		}
		else
		{
			log(LOG_DROP_MONEY, pPC->getName(), "", "CANNOT DROP! : " + pItem->toString());

			//cout << "#############################################" << endl;
			//cout << "# CRITICAL ERROR! CANNOT ADD MONEY TO ZONE! #" << endl;
			//cout << "#############################################" << endl;

			SAFE_DELETE(pItem);
			return;
		}

		// 플레이어로부터 돈을 뺏는다.
		//if (pPC->isSlayer())       pSlayer->setGoldEx(pSlayer->getGold() - amount);
		//else if (pPC->isVampire()) pVampire->setGoldEx(pVampire->getGold() - amount);

		// by sigi. 2002.9.4
		if (pPC->isSlayer())       pSlayer->decreaseGoldEx(amount);
		else if (pPC->isVampire()) pVampire->decreaseGoldEx(amount);
		else if (pPC->isOusters()) pOusters->decreaseGoldEx(amount);

	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
