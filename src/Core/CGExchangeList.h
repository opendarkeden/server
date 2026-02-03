//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExchangeList.h
// Written By  : Exchange System
// Description : Client requests to browse exchange listings
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_EXCHANGE_LIST_H__
#define __CG_EXCHANGE_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeList
//////////////////////////////////////////////////////////////////////////////

class CGExchangeList : public Packet {
public:
    CGExchangeList() {};
    virtual ~CGExchangeList() {};

    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);

    PacketSize_t getPacketSize() const;
    PacketID_t getPacketID() const { return PACKET_CG_EXCHANGE_LIST; }
    string getPacketName() const { return "CGExchangeList"; }
    string toString() const;

    // Getters
    int getPage() const { return m_Page; }
    void setPage(int page) { m_Page = page; }

    int getPageSize() const { return m_PageSize; }
    void setPageSize(int size) { m_PageSize = size; }

    uint8_t getItemClass() const { return m_ItemClass; }
    void setItemClass(uint8_t itemClass) { m_ItemClass = itemClass; }

    uint16_t getItemType() const { return m_ItemType; }
    void setItemType(uint16_t itemType) { m_ItemType = itemType; }

    int getMinPrice() const { return m_MinPrice; }
    void setMinPrice(int price) { m_MinPrice = price; }

    int getMaxPrice() const { return m_MaxPrice; }
    void setMaxPrice(int price) { m_MaxPrice = price; }

    const string& getSellerFilter() const { return m_SellerFilter; }
    void setSellerFilter(const string& filter) { m_SellerFilter = filter; }

private:
    int     m_Page;          // Page number (1-based)
    int     m_PageSize;      // Items per page
    uint8_t m_ItemClass;     // Filter by item class (0xFF = all)
    uint16_t m_ItemType;     // Filter by item type (0xFFFF = all)
    int     m_MinPrice;      // Minimum price filter (0 = no min)
    int     m_MaxPrice;      // Maximum price filter (0 = no max)
    string  m_SellerFilter;  // Filter by seller name
};

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeListFactory
//////////////////////////////////////////////////////////////////////////////

class CGExchangeListFactory : public PacketFactory {
public:
    Packet* createPacket() { return new CGExchangeList(); }
    string getPacketName() const { return "CGExchangeList"; }
    PacketID_t getPacketID() const { return Packet::PACKET_CG_EXCHANGE_LIST; }
    PacketSize_t getPacketMaxSize() const {
        return szBYTE +      // m_Page
               szBYTE +      // m_PageSize
               szBYTE +      // m_ItemClass
               szWORD +      // m_ItemType (uint16)
               sizeof(int) + // m_MinPrice
               sizeof(int) + // m_MaxPrice
               64;           // m_SellerFilter (max 64 chars)
    }
};

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeListHandler
//////////////////////////////////////////////////////////////////////////////

class GCExchangeList;

class CGExchangeListHandler {
public:
    static void execute(CGExchangeList* pPacket, Player* pPlayer);
};

#endif // __CG_EXCHANGE_LIST_H__
