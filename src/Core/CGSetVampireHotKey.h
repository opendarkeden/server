//////////////////////////////////////////////////////////////////////
//
// Filename    : CGSetVampireHotKey.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SET_VAMPIRE_HOT_KEY_H__
#define __CG_SET_VAMPIRE_HOT_KEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKey;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKey : public Packet {
public:
    CGSetVampireHotKey() {};
    virtual ~CGSetVampireHotKey() {};
    // Initialize the packet by reading data from the input stream.
    void read(SocketInputStream& iStream);

    // Serialize the packet into the output stream.
    void write(SocketOutputStream& oStream) const;

    // execute packet's handler
    void execute(Player* pPlayer);

    // get packet id
    PacketID_t getPacketID() const {
        return PACKET_CG_SET_VAMPIRE_HOT_KEY;
    }

    // get packet's body size
    // *OPTIMIZATION HINT*
    // Use CGSetVampireHotKeyPacketSize if that constant is defined.
    PacketSize_t getPacketSize() const {
        return szSkillType * 8;
    }

    // get packet name
    string getPacketName() const {
        return "CGSetVampireHotKey";
    }

    // get packet's debug string
    string toString() const;

public:
    // get/set X Coordicate
    SkillType_t getHotKey(BYTE pos) const {
        return m_HotKey[pos];
    }
    void setHotKey(BYTE pos, SkillType_t SkillType) {
        m_HotKey[pos] = SkillType;
    }

private:
    SkillType_t m_HotKey[8];
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyFactory;
//
// Factory for CGSetVampireHotKey
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKeyFactory : public PacketFactory {
public:
    // create packet
    Packet* createPacket() {
        return new CGSetVampireHotKey();
    }

    // get packet name
    string getPacketName() const {
        return "CGSetVampireHotKey";
    }

    // get packet id
    PacketID_t getPacketID() const {
        return Packet::PACKET_CG_SET_VAMPIRE_HOT_KEY;
    }

    // get packet's max body size
    // *OPTIMIZATION HINT*
    // Use CGSetVampireHotKeyPacketSize if that constant is defined.
    PacketSize_t getPacketMaxSize() const {
        return szSkillType * 8;
    }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKeyHandler {
public:
    // execute packet's handler
    static void execute(CGSetVampireHotKey* pPacket, Player* player);
};

#endif
