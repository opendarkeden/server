//////////////////////////////////////////////////////////////////////
//
// Filename    : GCFastMove.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FAST_MOVE_H__
#define __GC_FAST_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFastMove;
//
// Packet sent to clients when a creature moves rapidly. Contains the
// creature ID and start/end positions.
//
//////////////////////////////////////////////////////////////////////

class GCFastMove : public Packet {
public:
    // constructor
    GCFastMove() {}
    GCFastMove(ObjectID_t objectID, Coord_t x, Coord_t y, Coord_t x2, Coord_t y2)
        : m_ObjectID(objectID), m_FromX(x), m_FromY(y), m_ToX(x2), m_ToY(y2) {}
    ~GCFastMove() {};


public:
    // Initialize the packet by reading data from the input stream.
    void read(SocketInputStream& iStream);

    // Serialize the packet into the output stream.
    void write(SocketOutputStream& oStream) const;

    // execute packet's handler
    void execute(Player* pPlayer);

    // get packet id
    PacketID_t getPacketID() const {
        return PACKET_GC_FAST_MOVE;
    }

    // get packet's body size
    // *OPTIMIZATION HINT*
    // Use GCFastMovePacketSize if that constant is defined.
    PacketSize_t getPacketSize() const {
        return szObjectID + 4 * szCoord + szSkillType;
    }

    // get packet's name
    string getPacketName() const {
        return "GCFastMove";
    }

    // get packet's debug string
    string toString() const;


public:
    // get/set Creature ID
    ObjectID_t getObjectID() const {
        return m_ObjectID;
    }
    void setObjectID(ObjectID_t objectID) {
        m_ObjectID = objectID;
    }

    void setXY(Coord_t x, Coord_t y, Coord_t x2, Coord_t y2) {
        m_FromX = x;
        m_FromY = y;
        m_ToX = x2;
        m_ToY = y2;
    }

    // get
    Coord_t getFromX() const {
        return m_FromX;
    }
    Coord_t getFromY() const {
        return m_FromY;
    }
    Coord_t getToX() const {
        return m_ToX;
    }
    Coord_t getToY() const {
        return m_ToY;
    }

    SkillType_t getSkillType() const {
        return m_SkillType;
    }
    void setSkillType(SkillType_t skillType) {
        m_SkillType = skillType;
    }


private:
    ObjectID_t m_ObjectID;                  // Creature ID
    Coord_t m_FromX, m_FromY, m_ToX, m_ToY; // Start and end coordinates
    SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveFactory;
//
// Factory for GCFastMove
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveFactory : public PacketFactory {
public:
    // create packet
    Packet* createPacket() {
        return new GCFastMove();
    }

    // get packet name
    string getPacketName() const {
        return "GCFastMove";
    }

    // get packet id
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_FAST_MOVE;
    }

    // get packet's max body size
    // *OPTIMIZATION HINT*
    // Use GCFastMovePacketSize if that constant is defined.
    PacketSize_t getPacketMaxSize() const {
        return szObjectID + 4 * szCoord + szSkillType;
    }
};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveHandler {
public:
    // execute packet's handler
    static void execute(GCFastMove* pPacket, Player* pPlayer);
};

#endif
