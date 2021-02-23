//----------------------------------------------------------------------
// 
// Filename    : LGKickCharacter.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __LG_KICK_CHARACTER_H__
#define __LG_KICK_CHARACTER_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class LGKickCharacter;
//
// '이미 접속중' 문제 해결을 위해서
// 이미 접속중인 캐릭터를 제거하려고 하는 패킷이다.
//
// 이 packet의 결과는 LGKickVerify이다.
//
//----------------------------------------------------------------------

class LGKickCharacter : public DatagramPacket {

public:
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LG_KICK_CHARACTER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_PCName.size()		// PC name
				+ szuint;
	}

	// get packet name
	string getPacketName() const throw() { return "LGKickCharacter"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set pcName
	string getPCName() const throw() { return m_PCName; }
	void setPCName(const string& pcName) throw() { m_PCName = pcName; }
	
	uint getID() const throw() { return m_ID; }
	void setID(uint id) throw() { m_ID = id; }

private :

	// PC name
	string m_PCName;

	uint   m_ID; 
};


//////////////////////////////////////////////////////////////////////
//
// class LGKickCharacterFactory;
//
// Factory for LGKickCharacter
//
//////////////////////////////////////////////////////////////////////

class LGKickCharacterFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LGKickCharacter(); }

	// get packet name
	string getPacketName() const throw() { return "LGKickCharacter"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LG_KICK_CHARACTER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGKickCharacterPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 20		// PC name
				+ szuint;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGKickCharacterHandler;
//
//////////////////////////////////////////////////////////////////////

class LGKickCharacterHandler {
	
public:

	// execute packet's handler
	static void execute(LGKickCharacter* pPacket) throw(ProtocolException, Error);

};

#endif
