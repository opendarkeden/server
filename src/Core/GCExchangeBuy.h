//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExchangeBuy.h
// Written By  : Exchange System
// Description : Server responds to buy request
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_EXCHANGE_BUY_H__
#define __GC_EXCHANGE_BUY_H__

#include "Packet.h"

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// class GCExchangeBuy
//////////////////////////////////////////////////////////////////////////////

class GCExchangeBuy : public Packet {
public:
    GCExchangeBuy() : m_Success(false), m_OrderID(0) {};
    virtual ~GCExchangeBuy() {};

    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);  // Stub for server side

    PacketSize_t getPacketSize() const;
    PacketID_t getPacketID() const { return PACKET_GC_EXCHANGE_BUY; }
    string getPacketName() const { return "GCExchangeBuy"; }
    string toString() const;

    // Setters
    void setSuccess(bool success) { m_Success = success; }
    void setMessage(const string& message) { m_Message = message; }
    void setOrderID(int64_t orderID) { m_OrderID = orderID; }

    // Getters
    bool getSuccess() const { return m_Success; }
    const string& getMessage() const { return m_Message; }
    int64_t getOrderID() const { return m_OrderID; }

private:
    bool    m_Success;
    string  m_Message;
    int64_t m_OrderID;
};

//////////////////////////////////////////////////////////////////////////////
// class GCExchangeBuyHandler
//////////////////////////////////////////////////////////////////////////////

class GCExchangeBuyHandler {
public:
    static void execute(GCExchangeBuy* pPacket, Player* pPlayer);
};

#endif // __GC_EXCHANGE_BUY_H__
