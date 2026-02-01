//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExchangeBuy.h
// Written By  : Exchange System
// Description : Client requests to buy an item
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_EXCHANGE_BUY_H__
#define __CG_EXCHANGE_BUY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeBuy
//////////////////////////////////////////////////////////////////////////////

class CGExchangeBuy : public Packet {
public:
    CGExchangeBuy() : m_ListingID(0) {};
    virtual ~CGExchangeBuy() {};

    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);

    PacketSize_t getPacketSize() const;
    PacketID_t getPacketID() const { return PACKET_CG_EXCHANGE_BUY; }
    string getPacketName() const { return "CGExchangeBuy"; }
    string toString() const;

    // Getters/Setters
    int64_t getListingID() const { return m_ListingID; }
    void setListingID(int64_t id) { m_ListingID = id; }

    const string& getIdempotencyKey() const { return m_IdempotencyKey; }
    void setIdempotencyKey(const string& key) { m_IdempotencyKey = key; }

private:
    int64_t m_ListingID;
    string  m_IdempotencyKey;
};

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeBuyFactory
//////////////////////////////////////////////////////////////////////////////

class CGExchangeBuyFactory : public PacketFactory {
public:
    Packet* createPacket() { return new CGExchangeBuy(); }
    string getPacketName() const { return "CGExchangeBuy"; }
    PacketID_t getPacketID() const { return Packet::PACKET_CG_EXCHANGE_BUY; }
    PacketSize_t getPacketMaxSize() const {
        return sizeof(uint64_t) + // listingID
               64;                 // idempotencyKey (max 64 chars)
    }
};

//////////////////////////////////////////////////////////////////////////////
// class CGExchangeBuyHandler
//////////////////////////////////////////////////////////////////////////////

class GCExchangeBuy;

class CGExchangeBuyHandler {
public:
    static void execute(CGExchangeBuy* pPacket, Player* pPlayer);
};

#endif // __CG_EXCHANGE_BUY_H__
