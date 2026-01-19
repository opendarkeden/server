//----------------------------------------------------------------------
//
// Filename    : PacketValidator
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PACKET_VALIDATOR_H__
#define __PACKET_VALIDATOR_H__

// include files
#include <vector>

#include "PacketIDSet.h"
#include "PlayerStatus.h"

//----------------------------------------------------------------------
//
// class PacketValidator;
//
// Maintains the list of packet IDs that are valid for a given player
// status. XXXPlayer::processCommand() should confirm that the incoming
// packet ID is allowed for the player's current state and drop anything
// unexpected to avoid incorrect processing.
//
//----------------------------------------------------------------------

class PacketValidator {
public:
    // constructor
    PacketValidator();

    // destructor
    ~PacketValidator() noexcept;

    // init
    void init();

    // add packet id set
    void addPacketIDSet(PlayerStatus playerStatus, PacketIDSet* pPacketID);

    // delete packet id
    void deletePacketIDSet(PlayerStatus playerStatus, PacketIDSet* pPacketID);

    // is valid packet?
    bool isValidPacketID(PlayerStatus playerStatus, PacketID_t packetID);

    // get debug string
    string toString() const;

private:
    vector<PacketIDSet*> m_PacketIDSets;
};

//----------------------------------------------------------------------
// global variable declaration
//----------------------------------------------------------------------
extern PacketValidator* g_pPacketValidator;

#endif
