////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegenEventShop.cpp
// Written By  : excel96
// Description : 
// 크리스마스 이벤트용 상점을 갱신하는 액션
////////////////////////////////////////////////////////////////////////////////

#include "ActionRegenEventShop.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "ShopTemplate.h"
#include "OptionInfo.h"
#include "DB.h"
#include "LogClient.h"
#include "ItemFactoryManager.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionRegenEventShop::ActionRegenEventShop()
	
{
	__BEGIN_TRY

	m_Period.tv_sec     = 0;
	m_Period.tv_usec    = 0;
	m_NextRegen.tv_sec  = 0;
	m_NextRegen.tv_usec = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionRegenEventShop::~ActionRegenEventShop()
	
{
	__BEGIN_TRY

	clearList();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionRegenEventShop::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
	    // read NPC id
		int        NPCID   = propertyBuffer.getPropertyInt("NPCID");
		Statement* pStmt   = NULL;
		Result*    pResult = NULL;

		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT ID from ShopTemplate where NPCID = %d", NPCID);
			
			while (pResult->next())
			{
				ShopTemplateID_t id = pResult->getInt(1);
				addListElement(id);
			}

			delete pStmt;
		}
		END_DB(pStmt)

		// 상점 업데이트 주기를 읽어들인다. (초 단위)
		int nSecond = propertyBuffer.getPropertyInt("Period");
		m_Period.tv_sec = nSecond;

		// 다음 상점 업데이트를 언제 할 것인가를 세팅해 준다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		m_NextRegen = currentTime;
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
// NOTE : ShopTemplate은 이 액션이 실행되기 전에 모두 로드되어 있어야 한다.
////////////////////////////////////////////////////////////////////////////////
void ActionRegenEventShop::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert(pNPC != NULL);

	// 이벤트용 NPC로 설정해준다. 
	pNPC->setShopType(SHOPTYPE_EVENT);

	Zone* pZone = pNPC->getZone();
	Assert(pZone != NULL);

	// 현재 시간을 얻어낸다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// 업데이트할 시간이 아직 되직 않았다면 걍 리턴한다.
	if (currentTime < m_NextRegen) return;

	// 주위에 PC랑 이야기하고 있는 플레이어가 없는지 먼저 검사한다.
	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
	int centerX = pNPC->getX();
	int centerY = pNPC->getY();
	try
	{
		for (int zx = centerX - 5; zx <= centerX+5; zx++)
		{
			for (int zy = centerY - 5; zy <= centerY+5; zy++)
			{
				// 좌표가 한계를 넘어가지 않았는지 체크...
				if (!rect.ptInRect(zx, zy))
				{
					continue;
				}

				Tile& tile = pZone->getTile(zx, zy);

				// 걸어다니는 크리쳐를 검색
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					Assert(pNearCreature != NULL);
					// NPC랑 이야기하고 있는 놈이 있으면 걍 리턴
					if (pNearCreature->isPC())
					{
						return;
					}
				}
				// 날아다니는 크리쳐를 검색
				if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					Assert(pNearCreature != NULL);
					// NPC랑 이야기하고 있는 놈이 있으면 걍 리턴
					if (pNearCreature->isPC())
					{
						return;
					}
				}
			}
		}
	}
	catch (Throwable & t)
	{
		filelog("shopbug.txt", "%s", t.toString().c_str());
		return;
	}

	// 먼저 NPC가 가지고 있는 아이템을 전부 날리고...상점 버전을 올린다.
	// 일단 클리어하기 전에 로그를 한다.
	for (ShopRackType_t rackType=0; rackType<SHOP_RACK_TYPE_MAX; rackType++)
	{
		for (BYTE rackIndex=0; rackIndex<SHOP_RACK_INDEX_MAX; rackIndex++)
		{
			Item* pShopItem = pNPC->getShopItem(rackType, rackIndex);
			if (pShopItem != NULL)
				log(LOG_SHOP_DESTROY_ITEM, pNPC->getName(), "", pShopItem->toString());
		}
	}

	pNPC->clearShopItem();

	for (int i=0; i<SHOP_RACK_TYPE_MAX; i++)
		pNPC->increaseShopVersion(i);

	// 아이템을 만든다.
	list<ShopTemplateID_t> IDList[SHOP_RACK_TYPE_MAX];
	int                    combi[SHOP_RACK_TYPE_MAX] = {0,0,0};
	int                    count[SHOP_RACK_TYPE_MAX] = {0,0,0};
	int                    trialMax = 0;
	ShopTemplate*          pTemplate = NULL;
	ShopRackType_t         shopType;
	int                    itemClass;
	ItemType_t             minItemType, maxItemType, itemType;
	uint                   minOptionLevel, maxOptionLevel;
	OptionType_t           optionType;

	// 각각의 샵템플릿은 아이템 클래스와 최소, 최대 타입을 가지고 있다.
	// 최소, 최대 타입을 가지고, 해당하는 아이템 몇 가지를
	// 생성해야 하는 것을 알 수 있다. 예를 들면 다음과 같다.
	// MinItemType : 0, MaxItemType : 0 --> 1가지
	// MinItemType : 0, MaxItemType : 2 --> 3가지
	for (list<ShopTemplateID_t>::const_iterator itr=m_List.begin(); itr != m_List.end(); itr++)
	{
		pTemplate = g_pShopTemplateManager->getTemplate((*itr));

		Assert(pTemplate != NULL);
		
		shopType    = pTemplate->getShopType();
		itemClass   = pTemplate->getItemClass();
		minItemType = pTemplate->getMinItemType();
		maxItemType = pTemplate->getMaxItemType();
		
		// 샵의 종류(노멀, 스페셜...)에 따라, 
		// 생성할 샵 템플릿의 ID를 리스트에 집어넣어 두고,
		// 생성할 아이템의 종류수를 저장해 둔다.
		IDList[shopType].push_back(*itr);
		combi[shopType] += (maxItemType - minItemType + 1);
	}

	// 각 샵에다 아이템을 생성한다.
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
	{
		// 한 타입의 샵에는 20개까지의 아이템이 들어간다.
		// 만일 생성해야 할 아이템의 종류가 5가지라면,
		// 각각의 아이템을 4개까지 집어넣을 수 있다.
		// 종류가 6가지라면, 3개까지 집어넣을 수 있다.
		// 이 시도 횟수를 trialMax 변수에다 집어넣는다.
		if (combi[i] == 0) trialMax = 0;
		else trialMax = (int)(floor(SHOP_RACK_INDEX_MAX/combi[i]));

		// 만일 샵 타입이 노멀이라면, 같은 아이템을 여러 개
		// 생성하는 것은 의미가 없으므로, 한번만 아이템을 생성한다.
		if (i == SHOP_RACK_NORMAL
			|| i == SHOP_RACK_MYSTERIOUS) trialMax = 1;

		// 아까 저장해 놓았던 샵 템플릿 ID 리스트에서 하나씩을 뽑아와서,
		// 상점 아이템을 생성한다.
		for (list<ShopTemplateID_t>::const_iterator itr=IDList[i].begin(); itr != IDList[i].end(); itr++)
		{
			pTemplate      = g_pShopTemplateManager->getTemplate((*itr));
			itemClass      = pTemplate->getItemClass();
			minItemType    = pTemplate->getMinItemType();
			maxItemType    = pTemplate->getMaxItemType();
			minOptionLevel = pTemplate->getMinOptionLevel();
			maxOptionLevel = pTemplate->getMaxOptionLevel();

			// 먼저 생성가능한 옵션 타입의 벡터를 생성해둔다.
			//vector<OptionType_t> optionVector = g_pOptionInfoManager->getPossibleOptionVector((Item::ItemClass)itemClass, minOptionLevel, maxOptionLevel);
			// ShopTemplate에서 ItemType이 2,3이 나온다면 optionType은 +2로 조절하고
			// ShopTemplate에서 ItemType이 다른 것이라면, +3까지 주도록 한다.

			vector<OptionType_t> optionVector;
			if(minItemType == 2 && maxItemType == 3)
			{
				optionVector.push_back(2);  // STR+2
				optionVector.push_back(7);  // DEX+2
				optionVector.push_back(12); // INT+2
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(79); // ASPEED+2
			}
			else if(minItemType == 4 && maxItemType ==5)
			{
				optionVector.push_back(3);  // STR+3
				optionVector.push_back(8);  // DEX+3
				optionVector.push_back(13); // INT+3
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(80); // ASPEED+3
			}
			else if(minItemType == 6 && maxItemType == 6)
			{
				optionVector.push_back(4);  // STR+4
				optionVector.push_back(9);  // DEX+4
				optionVector.push_back(14); // INT+4
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(80); // ASPEED+3
			}

			for (ItemType_t type=minItemType; type<=maxItemType; type++)
			{
				// 한 타입의 샵에는 20개까지의 아이템이 들어간다.
				// 만일 생성해야 할 아이템의 종류가 5가지라면,
				// 각각의 아이템을 4개까지 집어넣을 수 있다.
				// 종류가 6가지라면, 3개까지 집어넣을 수 있다.
				for (int tc=0; tc<trialMax; tc++)
				{
					itemType = type;

					// 옵션 벡터 내에서 무작위로 옵션을 뽑아낸다.
					// 당연히 가능한 옵션이 없다면, optionType은 0(무옵션)이다.
					if (optionVector.size() > 0)
					{
						int randValue = rand();
						int size      = optionVector.size();
						int index     = randValue%size;

						optionType = optionVector[index];
					}
					else optionType = 0;

					// 실제로 아이템을 만든다.
					Item::ItemClass IClass = Item::ItemClass(itemClass);
					list<OptionType_t> optionTypes;
					if (optionType!=0)
						optionTypes.push_back( optionType );
					Item* pItem = g_pItemFactoryManager->createItem(IClass, itemType, optionTypes);
					Assert(pItem != NULL);

					// zone의 object registery에 등록.
					(pZone->getObjectRegistry()).registerObject(pItem);

					// 해당 진열장에 자리가 있다면 아이템을 더한다.
					if (count[i] < SHOP_RACK_INDEX_MAX)
					{
						pNPC->insertShopItem(i, count[i], pItem);
						count[i] = count[i] + 1;
					}
				}
			}
		}
	}

	// 다음 업데이트할 시간을 정해준다.
	m_NextRegen = m_NextRegen + m_Period;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRegenEventShop::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	int          i = 0;

	msg << "ActionRegenEventShop(";
	list<ShopTemplateID_t>::const_iterator itr=m_List.begin();
	for (; itr != m_List.end(); itr++)
		msg << "Item" << i++ << ":" 
			<< (int)(*itr) << ",";
	msg << ")";
	
	return msg.toString();
	
	__END_CATCH
}
