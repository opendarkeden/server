////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradePrepare.h
// Written By  : elca@ewestsoft.com
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_PREPARE_H__
#define __GC_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// Trade status codes
////////////////////////////////////////////////////////////////////////////////

enum {
    // Requester asks to start a trade; notify the target player.
    GC_TRADE_PREPARE_CODE_REQUEST = 0,

    // Requester cancelled the trade before the target responded.
    GC_TRADE_PREPARE_CODE_CANCEL,

    // Target accepted the trade request; notify the requester.
    GC_TRADE_PREPARE_CODE_ACCEPT,

    // Target rejected the trade request; notify the requester.
    GC_TRADE_PREPARE_CODE_REJECT,

    // Target is busy and cannot trade.
    GC_TRADE_PREPARE_CODE_BUSY,

    GC_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepare : public Packet {
public:
    GCTradePrepare() {};
    ~GCTradePrepare() {};
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);
    PacketID_t getPacketID() const {
        return PACKET_GC_TRADE_PREPARE;
    }
    PacketSize_t getPacketSize() const {
        return szObjectID + szBYTE;
    }
    string getPacketName() const {
        return "GCTradePrepare";
    }
    string toString() const;

public:
    ObjectID_t getTargetObjectID() const {
        return m_TargetObjectID;
    }
    void setTargetObjectID(ObjectID_t id) {
        m_TargetObjectID = id;
    }

    BYTE getCode() const {
        return m_Code;
    }
    void setCode(BYTE code) {
        m_Code = code;
    }

private:
    ObjectID_t m_TargetObjectID; // Trading target object OID
    BYTE m_Code;                 // Trade status code
};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareFactory : public PacketFactory {
public:
    Packet* createPacket() {
        return new GCTradePrepare();
    }
    string getPacketName() const {
        return "GCTradePrepare";
    }
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_TRADE_PREPARE;
    }
    PacketSize_t getPacketMaxSize() const {
        return szObjectID + szBYTE;
    }
};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareHandler {
public:
    static void execute(GCTradePrepare* pPacket, Player* pPlayer);
};

#endif
