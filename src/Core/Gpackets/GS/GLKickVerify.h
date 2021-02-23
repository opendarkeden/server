//----------------------------------------------------------------------
// 
// Filename    : GLKickVerify.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GL_KICK_VERIFY_H__
#define __GL_KICK_VERIFY_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GLKickVerify;
//
// '이미 접속 중' 문제를 해결하기 위한...
// LGKickCharacter에 대응하는 결과 패킷이다.
//
//----------------------------------------------------------------------

class GLKickVerify : public DatagramPacket {

public :
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GL_KICK_VERIFY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + szBYTE + m_PCName.size() + szuint;
	}

	// get packet name
	string getPacketName() const throw() { return "GLKickVerify"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set playerID
	bool isKicked() const throw() { return m_bKicked; }
	void setKicked(bool bKicked=true) throw() { m_bKicked = bKicked; }

  	// get/set pcName
    string getPCName() const throw() { return m_PCName; }
    void setPCName(const string& pcName) throw() { m_PCName = pcName; }

    uint getID() const throw() { return m_ID; }
    void setID(uint id) throw() { m_ID = id; }

	
private :

	// Player ID
	bool   m_bKicked;

	string m_PCName;

	uint   m_ID;
};


//////////////////////////////////////////////////////////////////////
//
// class GLKickVerifyFactory;
//
// Factory for GLKickVerify
//
//////////////////////////////////////////////////////////////////////

class GLKickVerifyFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GLKickVerify(); }

	// get packet name
	string getPacketName() const throw() { return "GLKickVerify"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GL_KICK_VERIFY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLKickVerifyPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + szBYTE + 20 + szuint;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLKickVerifyHandler;
//
//////////////////////////////////////////////////////////////////////

class GLKickVerifyHandler {
	
public :

	// execute packet's handler
	static void execute(GLKickVerify* pPacket) throw(ProtocolException, Error);

};

#endif
