//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareShop.cpp
// Written By  : 
// Description : 
// 상점 NPC를 제일 처음 로딩할 때, 상점 NPC가 팔게 될 아이템을
// 준비하는 액션이다. ShopTemplate 클래스와 매니저를 참고할 것.
//////////////////////////////////////////////////////////////////////////////

#include "ActionPrepareShop.h"
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

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ActionPrepareShop::ActionPrepareShop()
	throw()
{
	__BEGIN_TRY

	m_ListNum        = 0;
	m_MarketCondBuy  = 100;
	m_MarketCondSell = 100;
	m_TaxingCastleZoneID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ActionPrepareShop::~ActionPrepareShop()
	throw()
{
	__BEGIN_TRY

	clearList();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ActionPrepareShop::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
	__BEGIN_TRY

	try 
	{
		int        NPCID = propertyBuffer.getPropertyInt("NPCID");
		Statement* pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		BEGIN_DB
		{
			Result* pResult = pStmt->executeQuery("SELECT ID from ShopTemplate where NPCID = %d", NPCID);
			while (pResult->next())
			{
				ShopTemplateID_t id = pResult->getInt(1);
				addListElement(id);
			}
			delete pStmt;
		}
		END_DB(pStmt)

		m_MarketCondBuy  = propertyBuffer.getPropertyInt("MarketConditionBuy");
		m_MarketCondSell = propertyBuffer.getPropertyInt("MarketConditionSell");

//		propertyBuffer.getPropertyInt("CastleZoneID", (int&)m_TaxingCastleZoneID);
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
// NOTE : ShopTemplate은 이 액션이 실행되기 전에 모두 로드되어 있어야 한다.
//////////////////////////////////////////////////////////////////////////////
void ActionPrepareShop::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC * pNPC = dynamic_cast<NPC*>(pCreature1);

	// IDList    : ShopTemplate ID를 진열장 종류에 따라 분류해 저장하기
	//             위한 리스트들.
	// combi[]   : Class마다 minItemType과 maxItemType에 의해서 조합이 생긴다.
	//             이 조합의 총 갯수를 저장하기 위한 배열
	// count[]   : 현재 NPC가 진열장에 가지고 있는 아이템의 수. 역시 종류별.
	
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
	// 생성해야 한다는 것을 알 수 있다. 예를 들면 다음과 같다.
	// MinItemType : 0, MaxItemType : 0 --> 1가지
	// MinItemType : 0, MaxItemType : 2 --> 3가지
	for (list<ShopTemplateID_t>::const_iterator itr=m_List.begin(); itr != m_List.end(); itr++)
	{
		// 템플릿 리스트에서 하나를 뽑아온다.
		pTemplate = g_pShopTemplateManager->getTemplate((*itr));

		Assert(pTemplate != NULL);
		
		shopType    = pTemplate->getShopType();
		itemClass   = pTemplate->getItemClass();
		minItemType = pTemplate->getMinItemType();
		maxItemType = pTemplate->getMaxItemType();
		
		// 샵의 종류(노멀, 스페셜...)에 따라
		// 생성할 샵 템플릿의 ID를 리스트에 집어넣어 두고,
		// 생성할 아이템의 종류 수를 저장해 둔다.
		IDList[shopType].push_back(*itr);
		combi[shopType] += (maxItemType - minItemType + 1);
	}

	// 각 샵에다 아이템을 생성한다.
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
	{
		// 조합의 숫자로서 한 클래스의 한 타입 아이템이 얼마나 많이 진열장에
		// 배치될 수 있는지 알아낸다.
		// ex) 전체 아이템의 조합이 9가지이라면, 20/9 = 3. 즉 한 클래스의
		// 한 타입 아이템은 최대 3개까지 진열장에 나타날 수 있다.
		if (combi[i] == 0) trialMax = 0;
		else trialMax = (int)(floor(SHOP_RACK_INDEX_MAX/combi[i]));

		// 만일 샵 타입이 노멀이라면, 같은 아이템을 여러 개 
		// 생성하는 것은 의미가 없으므로, 한번만 아이템을 생성한다.
		if (i == SHOP_RACK_NORMAL
			|| i==SHOP_RACK_MYSTERIOUS) trialMax = 1;

		// 아까 저장해 놓았던 샵 템플릿 ID 리스트에서 하나씩을 뽑아와서
		// 상점 아이템을 생성한다.
		for (list<ShopTemplateID_t>::const_iterator itr=IDList[i].begin(); itr != IDList[i].end(); itr++)
		{
			pTemplate      = g_pShopTemplateManager->getTemplate((*itr));
			itemClass      = pTemplate->getItemClass();
			minItemType    = pTemplate->getMinItemType();
			maxItemType    = pTemplate->getMaxItemType();
			minOptionLevel = pTemplate->getMinOptionLevel();
			maxOptionLevel = pTemplate->getMaxOptionLevel();

			// 먼저 생성 가능한 옵션 타입의 벡터를 생성해둔다.
			vector<OptionType_t> optionVector = g_pOptionInfoManager->getPossibleOptionVector((Item::ItemClass)itemClass, minOptionLevel, maxOptionLevel);

			for (ItemType_t type=minItemType; type<=maxItemType; type++)
			{
				// 한 타입의 샵에는 20까지의 아이템이 들어간다.
				// 만일 생성해야 할 아이템의 종류가 5가지라면
				// 각각의 아이템을 4개까지 집어넣을 수 있다.
				// 종류가 6가지라면, 3개까지 집어넣을 수 있다.
				for (int tc=0; tc<trialMax; tc++)
				{
					itemType  = type;

					// 옵션 벡터 내에서 무작위로 옵션을 뽑아낸다.
					// 당연히 가능한 옵션이 없다면, optionType은 0(무옵션)이다.
					Item::ItemClass IClass = Item::ItemClass(itemClass);
					list<OptionType_t> optionTypes; 
					if (i!=SHOP_RACK_MYSTERIOUS && optionVector.size() > 0) 
					{
						optionType = optionVector[(rand()%optionVector.size())];

						if (optionType!=0)
							optionTypes.push_back( optionType );
					}
					
					// 실제로 아이템을 만든다.
					Item* pItem = g_pItemFactoryManager->createItem(IClass, itemType, optionTypes);
					Assert(pItem != NULL);

					// zone의 object registery에 등록.
					(pNPC->getZone()->getObjectRegistry()).registerObject(pItem);

					// 해당 진열장에 자리가 있다면 아이템을 더한다.
					if (count[i] < SHOP_RACK_INDEX_MAX)
					{
						pNPC->insertShopItem(i, count[i], pItem);

						count[i] = count[i]++;

						log(LOG_SHOP_CREATE_ITEM, pNPC->getName(), "", pItem->toString());
					}
				}
			}
		}
	}

	pNPC->setMarketCondBuy(m_MarketCondBuy);
	pNPC->setMarketCondSell(m_MarketCondSell);
//	pNPC->setTaxingCastleZoneID(m_TaxingCastleZoneID);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ActionPrepareShop::addListElement(ShopTemplateID_t id)
	throw()
{
	__BEGIN_TRY
		
	m_List.push_back(id);
	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string ActionPrepareShop::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	int          i = 0;

	msg << "ActionPrepareShop(";
	list<ShopTemplateID_t>::const_iterator itr=m_List.begin();
	for (;itr != m_List.end(); itr++)
		msg << "Item" << i++ << ":" << (int)(*itr) << ",";
	msg << ")";

	return msg.toString();

	__END_CATCH
}
