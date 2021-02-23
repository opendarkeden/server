//----------------------------------------------------------------------
//
// Filename    : PacketValidator
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PACKET_ID_SET_H__
#define __PACKET_ID_SET_H__

// include files
#include "Packet.h"
#include "PlayerStatus.h"

#if __LINUX__
	#include <hash_set>
	typedef hash_set<PacketID_t> PACKET_ID_SET;
#elif __WINDOWS__
	#include <set>
	typedef set<PacketID_t> PACKET_ID_SET;
#endif

//----------------------------------------------------------------------
//
// class PacketValidator;
//
// 패킷의 순서를 인증한다.
//
//----------------------------------------------------------------------

class PacketIDSet {

public :

	enum PacketIDSetType {
		PIST_NORMAL ,
		PIST_ANY ,
		PIST_NONE ,
		PIST_IGNORE_EXCEPT
	};

public :

	// constructor
	PacketIDSet (PlayerStatus playerStatus, PacketIDSetType packetIDSetType = PIST_NORMAL) throw ();

	// destructor
	~PacketIDSet () throw ();

	// add packet id to set
	void addPacketID (PacketID_t packetID) throw (DuplicatedException);

	// delete packet id from set
	void deletePacketID (PacketID_t packetID) throw (NoSuchElementException);

	// has packet id?
	bool hasPacketID (PacketID_t packetID) const throw (NoSuchElementException, IgnorePacketException);

	// get player status 
	PlayerStatus getPlayerStatus () const throw () { return m_PlayerStatus; }

	// get debug string
	string toString () const throw ();

private :

	// Packet ID Set Type 
	PacketIDSetType m_PacketIDSetType;

	// 플레이어 상태
	PlayerStatus m_PlayerStatus;

	// 허용되는 패킷의 해쉬맵
	PACKET_ID_SET m_PacketIDSet;

};

#endif
