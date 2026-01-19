//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddGearToInventory.h
// Written By  : crazydog
// Description :
// Skill ShieldStrike�� ���� �߻�. shield�� ����â���� inventory��
// ������.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_GEAR_TO_INVENTORY_H__
#define __GC_ADD_GEAR_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventory : public Packet {
public:
    GCAddGearToInventory();
    ~GCAddGearToInventory() noexcept;

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);
    PacketID_t getPacketID() const {
        return PACKET_GC_ADD_GEAR_TO_INVENTORY;
    }
    PacketSize_t getPacketSize() const {
        return szSlotID + szCoordInven + szCoordInven;
    }
    string getPacketName() const {
        return "GCAddGearToInventory";
    }
    string toString() const;

public:
    SlotID_t getSlotID() {
        return m_SlotID;
    }
    void setSlotID(SlotID_t SlotID) {
        m_SlotID = SlotID;
    }

    CoordInven_t getInvenX() const {
        return m_InvenX;
    }
    void setInvenX(CoordInven_t InvenX) {
        m_InvenX = InvenX;
    }

    CoordInven_t getInvenY() const {
        return m_InvenY;
    }
    void setInvenY(CoordInven_t InvenY) {
        m_InvenY = InvenY;
    }

private:
    SlotID_t m_SlotID;     // wear part ID
    CoordInven_t m_InvenX; // Inventory�� X, Y ��ǥ.
    CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryFactory : public PacketFactory {
public:
    Packet* createPacket() {
        return new GCAddGearToInventory();
    }
    string getPacketName() const {
        return "GCAddGearToInventory";
    }
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_ADD_GEAR_TO_INVENTORY;
    }
    PacketSize_t getPacketMaxSize() const {
        return szSlotID + szCoordInven + szCoordInven;
    }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryHandler {
public:
    static void execute(GCAddGearToInventory* pPacket, Player* player);
};


#endif
