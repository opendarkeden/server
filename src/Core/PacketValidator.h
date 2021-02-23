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
#include "PacketIDSet.h"
#include "PlayerStatus.h"
#include <vector>

//----------------------------------------------------------------------
//
// class PacketValidator;
//
// 플레이어의 특정 상태에서 허용되는 패킷들의 리스트를 관리함.
// XXXPlayer::processCommand() 에서 패킷 아이디가 들어왔을 경우
// 이 아이디를 플레이어의 상태에 따라서 검증해본다. 이때 맞으면
// 계속 처리하면 되지만 틀리면 접속을 종료해야 한다.
//
//----------------------------------------------------------------------

class PacketValidator {

public :

	// constructor
	PacketValidator () throw ();

	// destructor
	~PacketValidator () throw ();

	// init
	void init () throw (Error);

	// add packet id set
	void addPacketIDSet (PlayerStatus playerStatus, PacketIDSet* pPacketID) throw (DuplicatedException, Error);

	// delete packet id
	void deletePacketIDSet (PlayerStatus playerStatus, PacketIDSet* pPacketID) throw (NoSuchElementException, Error);

	// is valid packet?
	bool isValidPacketID (PlayerStatus playerStatus, PacketID_t packetID) throw (NoSuchElementException, IgnorePacketException, Error);

	// get debug string
	string toString () const throw ();

private :

	vector< PacketIDSet* > m_PacketIDSets;

};

//----------------------------------------------------------------------
// global variable declaration
//----------------------------------------------------------------------
extern PacketValidator* g_pPacketValidator;

#endif
