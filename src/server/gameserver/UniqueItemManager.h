//////////////////////////////////////////////////////////////////////////////
// Filename    : UniqueItemInfo.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __UNIQUE_ITEM_MANAGER_H__
#define __UNIQUE_ITEM_MANAGER_H__

#include "Types.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class UniqueItemInfo
//////////////////////////////////////////////////////////////////////////////

class UniqueItemManager 
{
public :

	void init() ;

	// unique item을 하나 생성한다.
	//Item* getRandomUniqueitem() ;

	// 아이템 생성 가능한가? (아이템 개수 제한)
	static bool isPossibleCreate(Item::ItemClass itemClass, ItemType_t itemType) ;

	// 아이템 생성했다. (개수 변경)
	static void createItem(Item::ItemClass itemClass, ItemType_t itemType) ;

	// 아이템 생성했다. (개수 변경)
	static void deleteItem(Item::ItemClass itemClass, ItemType_t itemType) ;

private :
	//Ratio_t 	m_TotalUniqueItemRatio;
	//Ratio_t*	m_Ratios[Item::ITEM_CLASS_MAX];
};

extern UniqueItemManager* g_pUniqueItemManager;

#endif	// __UNIQUE_ITEM_MANAGER_H__
