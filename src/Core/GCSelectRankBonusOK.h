//////////////////////////////////////////////////////////////////////
//
// Filename    :  GCSelectRankBonusOK.h
// Written By  :  elca@ewestsoft.com
// Description :  Å
//
//
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_RANK_BONUS_OK_H__
#define __GC_SELECT_RANK_BONUS_OK_H__

// include files
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOK;
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusOK : public Packet {
public:
    // constructor
    GCSelectRankBonusOK();

    // destructor
    ~GCSelectRankBonusOK();


public:
    // ÀÔ·Â½ºÆ®¸²(¹öÆÛ)À¸·ÎºÎÅÍ µ¥ÀÌÅ¸¸¦ ÀÐ¾î¼­ ÆÐÅ¶À» ÃÊ±âÈ­ÇÑ´Ù.
    void read(SocketInputStream& iStream);

    // Ãâ·Â½ºÆ®¸²(¹öÆÛ)À¸·Î ÆÐÅ¶ÀÇ ¹ÙÀÌ³Ê¸® ÀÌ¹ÌÁö¸¦ º¸³½´Ù.
    void write(SocketOutputStream& oStream) const;

    // execute packet's handler
    void execute(Player* pPlayer);

    // get packet id
    PacketID_t getPacketID() const {
        return PACKET_GC_SELECT_RANK_BONUS_OK;
    }

    // get packet size
    PacketSize_t getPacketSize() const {
        return szDWORD;
    }

    // get packet's name
    string getPacketName() const {
        return "GCSelectRankBonusOK";
    }

    // get packet's debug string
    string toString() const;

    // get/set m_RankBonusType
    DWORD getRankBonusType() const {
        return m_RankBonusType;
    }
    void setRankBonusType(DWORD rankBonusType) {
        m_RankBonusType = rankBonusType;
    }

private:
    // RankBonusType
    DWORD m_RankBonusType;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOKFactory;
//
// Factory for  GCSelectRankBonusOK
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusOKFactory : public PacketFactory {
public:
    // constructor
    GCSelectRankBonusOKFactory() {}

    // destructor
    virtual ~GCSelectRankBonusOKFactory() {}


public:
    // create packet
    Packet* createPacket() {
        return new GCSelectRankBonusOK();
    }

    // get packet name
    string getPacketName() const {
        return "GCSelectRankBonusOK";
    }

    // get packet id
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_SELECT_RANK_BONUS_OK;
    }

    // get Packet Max Size
    PacketSize_t getPacketMaxSize() const {
        return szDWORD;
    }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusOKHandler {
public:
    // execute packet's handler
    static void execute(GCSelectRankBonusOK* pGCSelectRankBonusOK, Player* pPlayer);
};

#endif
