//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExchangeList.h
// Written By  : Exchange System
// Description : Server sends listing list to client
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_EXCHANGE_LIST_H__
#define __GC_EXCHANGE_LIST_H__

#include "Packet.h"
#include <vector>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// ExchangeListing structure (partial, for packet transfer)
//////////////////////////////////////////////////////////////////////////////

struct ExchangeListing {
    int64_t     listingID;
    int16_t     serverID;
    string      sellerAccount;
    string      sellerPlayer;
    uint8_t     sellerRace;
    uint8_t     itemClass;
    uint16_t    itemType;
    int64_t     itemID;
    int         objectID;
    int         pricePoint;
    uint8_t     currency;
    uint8_t     status;
    string      buyerAccount;
    string      buyerPlayer;
    uint8_t     taxRate;
    int         taxAmount;
    string      createdAt;
    string      expireAt;
    string      soldAt;
    string      cancelledAt;
    string      updatedAt;
    int         version;

    // Snapshot fields for UI display
    string      itemName;
    uint8_t     enchantLevel;
    uint16_t    grade;
    int         durability;
    uint16_t    silver;
    uint8_t     optionType1;
    uint8_t     optionType2;
    uint8_t     optionType3;
    uint16_t    optionValue1;
    uint16_t    optionValue2;
    uint16_t    optionValue3;
    int         stackCount;
};

//////////////////////////////////////////////////////////////////////////////
// class GCExchangeList
//////////////////////////////////////////////////////////////////////////////

class GCExchangeList : public Packet {
public:
    GCExchangeList() : m_Page(1), m_PageSize(20), m_Total(0) {};
    virtual ~GCExchangeList() {};

    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);  // Stub for server side

    PacketSize_t getPacketSize() const;
    PacketID_t getPacketID() const { return PACKET_GC_EXCHANGE_LIST; }
    string getPacketName() const { return "GCExchangeList"; }
    string toString() const;

    // Setters
    void setListings(const vector<ExchangeListing>& listings);
    void setPage(int page) { m_Page = page; }
    void setPageSize(int pageSize) { m_PageSize = pageSize; }
    void setTotal(int total) { m_Total = total; }

    // Getters
    const vector<ExchangeListing>& getListings() const { return m_Listings; }
    int getPage() const { return m_Page; }
    int getPageSize() const { return m_PageSize; }
    int getTotal() const { return m_Total; }

private:
    vector<ExchangeListing> m_Listings;
    int     m_Page;
    int     m_PageSize;
    int     m_Total;
};

//////////////////////////////////////////////////////////////////////////////
// class GCExchangeListHandler
//////////////////////////////////////////////////////////////////////////////

class GCExchangeListHandler {
public:
    static void execute(GCExchangeList* pPacket, Player* pPlayer);
};

#endif // __GC_EXCHANGE_LIST_H__
