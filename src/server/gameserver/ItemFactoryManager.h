//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemFactoryManager.h 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_FACTORY_MANAGER_H__
#define __ITEM_FACTORY_MANAGER_H__

#include "Item.h"
#include "ItemFactory.h"
#include <hash_map>

#define CREATE_ITEM(C, T, O) g_pItemFactoryManager->createItem(C, T, O)

//////////////////////////////////////////////////////////////////////////////
// class ItemFactoryManager
//////////////////////////////////////////////////////////////////////////////

class ItemFactoryManager 
{
public:
	ItemFactoryManager() throw();
	~ItemFactoryManager() throw();

public:
	void init() throw(Error);

	void addFactory(ItemFactory* pFactory) throw(Error);

	Item* createItem(Item::ItemClass IClass, ItemType_t ItemType, const list<OptionType_t>& OptionType) throw(NoSuchElementException, Error);

	string getItemName(Item::ItemClass IClass) throw();

	Item::ItemClass getItemClassByName( const string & ClassName ) throw();

	string toString() const throw();

private:
	ItemFactory ** m_Factories; // 아이템팩토리의 배열
	ushort         m_Size;      // 아이템팩토리배열의 크기
	hash_map<string, Item::ItemClass> m_ItemClassMap;

};

extern ItemFactoryManager* g_pItemFactoryManager;

#endif
