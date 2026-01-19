//////////////////////////////////////////////////////////////////////
//
// Filename    : CGVerifyTime.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VERIFY_TIME_H__
#define __CG_VERIFY_TIME_H__

// include files

// #ifdef __GAME_SERVER__
// #include "GamePlayer.h"
// #endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTime;
//
// Client sends this VerifyTime packet.
// Use the new VerifyTime string instead of the old payload fields.
//
//////////////////////////////////////////////////////////////////////

class Player;
class GamePlayer;

class CGVerifyTime : public Packet {
public:
    CGVerifyTime() {};
    virtual ~CGVerifyTime() {};
    // Initialize packet from the input stream.
    void read(SocketInputStream& iStream);

    // Write the packet body to the output stream.
    void write(SocketOutputStream& oStream) const;

    // execute packet's handler
    void execute(Player* pPlayer);

    // get packet id
    PacketID_t getPacketID() const {
        return PACKET_CG_VERIFY_TIME;
    }

    // get packet's body size
    PacketSize_t getPacketSize() const {
        return 0;
    }

    // get packet name
    string getPacketName() const {
        return "CGVerifyTime";
    }

    // get packet's debug string
    string toString() const;

private:
};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeFactory;
//
// Factory for CGVerifyTime
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeFactory : public PacketFactory {
public:
    // create packet
    Packet* createPacket() {
        return new CGVerifyTime();
    }

    // get packet name
    string getPacketName() const {
        return "CGVerifyTime";
    }

    // get packet id
    PacketID_t getPacketID() const {
        return Packet::PACKET_CG_VERIFY_TIME;
    }

    // get packet's max body size
    // Reserve enough space for the message payload.
    PacketSize_t getPacketMaxSize() const {
        return 0;
    }
};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeHandler;
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeHandler {
public:
    // execute packet's handler
    static void execute(CGVerifyTime* pPacket, Player* pPlayer);

    // Persist players flagged for speed-hack detection.
    static void saveSpeedHackPlayer(Player* pPlayer);
};

#endif
