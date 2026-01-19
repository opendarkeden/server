#ifndef __GQUEST_INVENTORY_H__
#define __GQUEST_INVENTORY_H__

#include <string>

#include "Exception.h"
#include "GCGQuestInventory.h"
#include "Types.h"

class Packet;

class GQuestInventory {
public:
    list<ItemType_t>& getItems() {
        return m_Inventory.getItemList();
    }
    const list<ItemType_t>& getItems() const {
        return m_Inventory.getItemList();
    }

    Packet* getInventoryPacket() {
        return &m_Inventory;
    }
    void load(const string& ownerName);

    void removeOne(const string& ownerName, ItemType_t item);

    void addOne(ItemType_t item);
    void saveOne(const string& ownerName, ItemType_t item);

private:
    GCGQuestInventory m_Inventory;
};

#endif
