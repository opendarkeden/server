//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemFactory.h 
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_FACTORY_H__
#define __ITEM_FACTORY_H__

#include "Item.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class ItemFactory
//////////////////////////////////////////////////////////////////////////////

class ItemFactory 
{
public:
	virtual ~ItemFactory() throw() {}

public:
	//virtual Item* createItem(ItemType_t ItemType, OptionType_t OptionType) throw() = 0;
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() = 0;
	virtual Item::ItemClass getItemClass() const throw() = 0;
	virtual string getItemClassName() const throw() = 0;
};

#endif
