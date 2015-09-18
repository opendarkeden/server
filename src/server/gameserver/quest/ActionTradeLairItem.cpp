////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeLairItem.cpp
// Written By  : 장홍창
// Description :
//               레어 마스터를 죽였을 경우 생기는 아이템을
//               NPC와 교환하는 로직이다.
//               생성되는 아이템은 Random하게 결정된다. (이 경우 Gameble을
//               잘 이용하면 쉬울 듯 하다)
//
// 
// History.
//
//  Date        Writer         Description
// ---------- ----------- ------------------------------------------------------
// 2002.09.04   장홍창     신규 생성
////////////////////////////////////////////////////////////////////////////////

#include "ActionTradeLairItem.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "Treasure.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "MonsterInfo.h"
#include "QuestItem.h"
#include "ItemUtil.h"
#include "StringPool.h"
#include "ItemMineInfo.h"
#include "PacketUtil.h"
#include "ItemGradeManager.h"
#include <list>

#include "GCCreateItem.h"
#include "GCNPCResponse.h"
#include "GCSystemMessage.h"
#include "GCDeleteInventoryItem.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTradeLairItem::read(PropertyBuffer & propertyBuffer)
    throw(Error)
{
    __BEGIN_TRY

 	try
	{
		// 받을 돈의 양을 읽어들인다.
		m_Type = (ItemType_t)propertyBuffer.getPropertyInt("Type");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

   __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTradeLairItem::execute(Creature * pCreature1 , Creature * pCreature2) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	if (m_Type <= 5 )
	{
		SYSTEM_RETURN_IF_NOT(SYSTEM_MASTER_LAIR);
	}

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);
	StringStream message;

	/*

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage("아직 지원되지 않는 기능입니다");
	pPlayer->sendPacket(&gcSystemMessage);
	*/


	//cout << "ActionTradeLairItem" << ":" << m_Type;

	Inventory* pInventory = pPC->getInventory();

	// 먼저 아이템을 가지고 있는가를 체크한다.
	Item* pMasterItem = NULL;
	MonsterType_t MonsterType = 0;

	Item* pItem1 = NULL;
	bool bUpgrade = false;
	
	// 옵션에 따라서 다른 아이템을 검사해야 한다.
	// 코난 : 팬던트/ 비쥬만 체크한다.
	// 브리콜라카스: 테페즈 펜던트/비쥬만 체크해야 한다
	// 카임 : 바토리 팬던트/비쥬만 체크해야 한다.

	if (m_Type == 0) // 코난, 비쥬
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 0);
		MonsterType = BATORI_TYPE;

		if (pMasterItem == NULL )
		{
			pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 2);
			MonsterType = TEPEZ_TYPE;
			if (pMasterItem == NULL )
			{
				pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 8); //질드레 비쥬
				MonsterType = GDR_TYPE;
				bUpgrade = true;
			}
		}
	}
	else if (m_Type == 1) // 코난, 팬던트
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 1);
		MonsterType = BATORI_TYPE;

		if (pMasterItem == NULL)
		{
			pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 3);
			MonsterType = TEPEZ_TYPE;
			if (pMasterItem == NULL )
			{
				pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 9); //질드레 펜던트
				MonsterType = GDR_TYPE;
				bUpgrade = true;
			}
		}
	}
	else if (m_Type == 2) // 브리콜라카스, 비쥬
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 2);
//		if (pMasterItem == NULL ) pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 8); //질드레 비쥬
		MonsterType = TEPEZ_TYPE;
	}
	else if (m_Type == 3) // 브리콜라카스, 팬던트
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 3);
//		if (pMasterItem == NULL ) pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 9); //질드레 펜던트
		MonsterType = TEPEZ_TYPE;
	}
	else if (m_Type == 4) // 카임, 비쥬
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 0);
//		if (pMasterItem == NULL ) pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 8); //질드레 비쥬
		MonsterType = BATORI_TYPE;
	}
	else if (m_Type == 5) // 카임, 팬던트
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 1);
//		if (pMasterItem == NULL ) pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 9); //질드레 펜던트
		MonsterType = BATORI_TYPE;
	}
	else if (m_Type == 10) // 질드레, 비쥬
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 8);
		bUpgrade = true;
		MonsterType = GDR_TYPE;
	}
	else if (m_Type == 11) // 질드레, 팬던트
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 9);
		bUpgrade = true;
		MonsterType = GDR_TYPE;
	}
	else if (m_Type == 6) // 젬스톤이지롱~
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 4);
		MonsterType = BATORI_TYPE;
	}
	else if (m_Type == 7) // 보름달~
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 5);
		ItemMineInfo* pItemMineInfo;

		if (pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert(pSlayer != NULL);

			Attr_t totalAttr = pSlayer->getTotalAttr(ATTR_BASIC);

			if (totalAttr <= 130 )	// 하드코딩 ㅜ.ㅠ
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(0);
			else if (totalAttr <= 210 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(1);
			else if (totalAttr <= 270 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(2);
			else if (totalAttr <= 300 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(3);
			else
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(4);
		}
		else if (pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			Assert(pVampire != NULL);

			Level_t level = pVampire->getLevel();

			if (level <= 20 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(5);
			else if (level <= 40 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(6);
			else if (level <= 60 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(7);
			else if (level <= 90 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(8);
			else
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(9);
		}
		else if (pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			Assert(pOusters != NULL);

			Level_t level = pOusters->getLevel();

			if (level <= 20 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(10);
			else if (level <= 40 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(11);
			else if (level <= 60 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(12);
			else if (level <= 90 )
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(13);
			else
				pItemMineInfo = g_pItemMineInfoManager->getItemMineInfo(14);
		}
		else Assert(false);

		pItem1 = pItemMineInfo->getItem();
		setItemGender(pItem1, (pPC->getSex()==FEMALE)?GENDER_FEMALE:GENDER_MALE);
	}
	else if (m_Type == 8) // 그믐달~
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 6);

		if (pPC->isSlayer() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(15, 32);
		}
		else if (pPC->isVampire() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(33, 45);
		}
		else if (pPC->isOusters() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(46, 61);
		}

		setItemGender(pItem1, (pPC->getSex()==FEMALE)?GENDER_FEMALE:GENDER_MALE);
	}
	else if (m_Type == 9) // 빨간색 복주머니
	{
		pMasterItem = pInventory->findItem(Item::ITEM_CLASS_QUEST_ITEM, 7);

		if (pPC->isSlayer() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(62, 81);
		}
		else if (pPC->isVampire() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(82, 96);
		}
		else if (pPC->isOusters() )
		{
			pItem1 = g_pItemMineInfoManager->getRandomItem(97, 112);
		}
	}
	else
	{
		// 거래를 위한 NPC의 Property가 잘못되었다. 이런 경우에는
		// 운영팀으로 문의를 하면 바로 처리를 할 수 있다.
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_NPC_ERROR ));
		pPlayer->sendPacket(&gcSystemMessage);

		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);
		return;
	}
	
	if (pMasterItem == NULL)
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_NO_LAIR_ITEM ));
		pPlayer->sendPacket(&gcSystemMessage);

		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);

		return;
	}

	Zone* pZone = pPC->getZone();

//	if (MonsterType != 0 ) // 루팅표를 참조해서 아이템을 만들어오는 경우
	if (pItem1 == NULL )
	{
		QuestItemInfo* pItemInfo = dynamic_cast<QuestItemInfo*>(g_pQuestItemInfoManager->getItemInfo(pMasterItem->getItemType() ));
		Assert(pItemInfo!=NULL);

		///////////////////////////////////////////////////////////////////////////////
		// 가장 난감한 부분
		//   아이템을 랜덤하게 선택해야 한다.
		//   일단은 기본 아이템 하나로 한다.
		//////////////////////////////////////////////////////////////////////////////
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(MonsterType);
		TreasureList *pTreasureList = NULL;

		// 종족에 따라서 주는 아이템도 달라야 한다.
		if (pCreature2->isSlayer())
			pTreasureList = pMonsterInfo->getSlayerTreasureList();
		else if (pCreature2->isVampire())
			pTreasureList = pMonsterInfo->getVampireTreasureList();
		else if (pCreature2->isOusters())
			pTreasureList = pMonsterInfo->getOustersTreasureList();

		const list<Treasure*>& treasures = pTreasureList->getTreasures();

		list<Treasure*>::const_iterator itr = treasures.begin();

		ITEM_TEMPLATE it;

		for(; itr != treasures.end(); itr++)
		{
			Treasure* pTreasure = (*itr);

			it.ItemClass = Item::ITEM_CLASS_MAX;
			it.ItemType = 0;

			// QuestItem 마다 다른.. 옵션이 2개 붙을 확률
			it.NextOptionRatio = pItemInfo->getBonusRatio();

			//cout << "TradeLairItem: BonusRatio = " << it.NextOptionRatio << endl;

			if (pTreasure->getRandomItem(&it) )
			{
/*				if (bUpgrade && isPossibleUpgradeItemType(it.ItemClass ) )
				{
					it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, 1);
				}
*/
				pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
				Assert(pItem1 != NULL);
			}
		}

		if (pItem1 == NULL)
		{
			StringStream msg;
			msg << "ActionTradeLairItem: "
				<< (int)it.ItemClass << ", "
				<< (int)it.ItemType << ", "
				<< (int)it.bCreateOption << ", "
				<< getOptionTypeToString(it.OptionType);

			filelog("tradeLairItemBUG.txt", "%s", msg.toString().c_str());

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage(g_pStringPool->getString(STRID_ITEM_CREATE_ERROR ));
			pPlayer->sendPacket(&gcSystemMessage);

			GCNPCResponse response;
			response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&response);

			return;
		}
	}

	TPOINT pt;

	pItem1->setGrade(min(7,ItemGradeManager::Instance().getRandomBeadGrade()));
	pZone->registerObject(pItem1);

	// 만약 inventory에 공간이 있다면, 넣는다. 
	if(pInventory->addItem(pItem1, pt))
	{
		pItem1->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

		GCCreateItem gcCreateItem;
/*		gcCreateItem.setObjectID(pItem1->getObjectID());
		gcCreateItem.setItemClass(pItem1->getItemClass());
		gcCreateItem.setItemType(pItem1->getItemType());
		gcCreateItem.setOptionType(pItem1->getOptionTypeList());
		gcCreateItem.setDurability(pItem1->getDurability());
		gcCreateItem.setItemNum(pItem1->getNum());
		gcCreateItem.setInvenX(pt.x);
		gcCreateItem.setInvenY(pt.y);
		gcCreateItem.setGrade(pItem1->getGrade());*/

		makeGCCreateItem(&gcCreateItem, pItem1, pt.x, pt.y);

		pPlayer->sendPacket(&gcCreateItem);

		// ItemTraceLog 를 남긴다
		if (pItem1 != NULL && pItem1->isTraceItem() )
		{
			remainTraceLog(pItem1, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		}

		// 기존의 아이템을 없앤다
		GCDeleteInventoryItem gcDeleteInventoryItem;
		gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
		pPlayer->sendPacket(&gcDeleteInventoryItem);

		// 서버에서 없애준다.
		pInventory->deleteItem(pMasterItem->getObjectID());	// 좌표로 바꿔주면 좋을건데..
		// ItemTraceLog 를 남긴다
		if (pMasterItem != NULL && pMasterItem->isTraceItem() )
		{
			remainTraceLog(pMasterItem, pCreature2->getName(), pCreature1->getName(), ITEM_LOG_DELETE, DETAIL_EVENTNPC);
		}
		pMasterItem->destroy();
		SAFE_DELETE(pMasterItem);

		// 사용자에게 성공 메시지 출력
//		StringStream message;
//		message << "성공적으로 교환되었습니다";
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_TRADE_SUCCESS ));
		pPlayer->sendPacket(&gcSystemMessage);
	}
	else
	{
//		StringStream buf;
//		buf << "인벤토리에 공간이 부족합니다";

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_NOT_ENOUGH_INVENTORY_SPACE ));
		pPlayer->sendPacket(&gcSystemMessage);
	}

	GCNPCResponse response;
	response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPlayer->sendPacket(&response);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTradeLairItem::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTradeLairItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
