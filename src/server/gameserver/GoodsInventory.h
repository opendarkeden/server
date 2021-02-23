//////////////////////////////////////////////////////////////////////////
// Filename			: GoodsInventory.h
// Written By		: bezz
// Description		: 홈페이지에서 구매한 아이템이 담겨 있는 Inventory
//////////////////////////////////////////////////////////////////////////

#ifndef __GOODS_INVENTORY_H__
#define __GOODS_INVENTORY_H__

#include "Types.h"
#include "Item.h"

#include <list>

typedef struct
{
	string		m_ID;
	Item* 		m_pItem;
} BuyItem;

//////////////////////////////////////////////////////////////
// Class GoodsInventory
//////////////////////////////////////////////////////////////

class GoodsInventory
{
public:
	typedef list<BuyItem>				ListItem;
	typedef ListItem::iterator			ListItemItr;
	typedef ListItem::const_iterator	ListItemConstItr;

public:
	GoodsInventory() {};
	~GoodsInventory() throw();

public:
	ListItem& getGoods() throw() { return m_Goods; }

	// 아이템 추가
	void addItem( string ID, Item* pItem ) throw();

	// 아이템 가져오기
	Item* popItem( ObjectID_t oid ) throw();

	// 아이템 걍가져오기
	Item* getItem( ObjectID_t oid ) throw();

	// 인벤토리가 비었나?
	bool empty() throw() { return m_Goods.empty(); }

	void clear() throw();

	// 인벤토리에 있는 아이템 개수
	int getNum() const { return m_Goods.size(); }

private:
	ListItem m_Goods;
};

#endif
