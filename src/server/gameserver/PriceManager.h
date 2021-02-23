//////////////////////////////////////////////////////////////////////////////
// Filename    : PriceManager.h
// Written By  : 김성민
// Description : 
// 아이템을 상점에서 사고 팔 때, 그 매매가격을 결정하는 클래스이다. 
// 내부적으로는 ItemInfoManager의 원래 가격을 이용해 계산을 한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PRICEMANAGER_H__
#define __PRICEMANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class PriceManager
//////////////////////////////////////////////////////////////////////////////

//class Item;
class Creature;

class PriceManager
{
public:

	// 아이템 정보를 참조해 실제 물건값을 정한다.
	Price_t getPrice(Item* pItem, MarketCond_t nDiscount, ShopRackType_t shopType, Creature* pCreature) const;

	// Mysterious Item 가격
	Price_t getMysteriousPrice(Item::ItemClass itemClass, Creature* pCreature) const;

	// 아이템을 수리할 때의 비용
	Price_t getRepairPrice(Item* pItem, Creature* pCreature=NULL) const;

	// 아이템에 은 도금할 때의 비용
	Price_t getSilverCoatingPrice(Item* pItem, Creature* pCreature=NULL) const;

	// 보관함의 가격
	Price_t getStashPrice(BYTE index, Creature* pCreature=NULL) const;

	// 이벤트용 가격 함수
	int getStarPrice(Item* pItem, XMAS_STAR& star) const;
	int getBallPrice(int price, XMAS_STAR& star) const;
};

// global variable declaration
extern PriceManager* g_pPriceManager;

#endif
