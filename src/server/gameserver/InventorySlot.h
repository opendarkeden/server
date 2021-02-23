//////////////////////////////////////////////////////////////////////////////
// Filename    : InventorySlot.h
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_SLOT_H__
#define __INVENTORY_SLOT_H__

#include "Item.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class InventorySlot
//////////////////////////////////////////////////////////////////////////////

class InventorySlot 
{
public: 
	InventorySlot() throw()	: m_pItem(NULL) {}
	~InventorySlot() throw(Error);

public:
	Item* getItem() throw() { return m_pItem; }
	void addItem(Item* pItem) throw();
	void deleteItem() throw(Error);

private: 
	Item* m_pItem;

};

#endif	// __INVENTORY_SLOT_H__
