#ifndef __GQUEST_INVENTORY_H__
#define __GQUEST_INVENTORY_H__

#include "Types.h"
#include "Exception.h"
#include "Gpackets/GCGQuestInventory.h"

#include <string>

class Packet;

class GQuestInventory
{
public:
	list<ItemType_t>&			getItems() { return m_Inventory.getItemList(); }
	const list<ItemType_t>&	getItems() const { return m_Inventory.getItemList(); }

	Packet*	getInventoryPacket() { return &m_Inventory; }
	void load(const string& ownerName) throw (Error);

	void removeOne(const string& ownerName, ItemType_t item);

	void addOne(ItemType_t item);
	void saveOne(const string& ownerName, ItemType_t item);

private:
	GCGQuestInventory	m_Inventory;
};

#endif
