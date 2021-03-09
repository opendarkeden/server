//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCreatureDied.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CREATURE_DIED_H__
#define __GC_CREATURE_DIED_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDied;
//
// 게임 서버가 특정 플레이어의 CreatureDied 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 CreatureDied 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDied : public Packet {

public :
	GCCreatureDied() {};
    ~GCCreatureDied() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_CREATURE_DIED; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "GCCreatureDied"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set dead creature's creature id
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID)  { m_ObjectID = creatureID; }
	

private :
	
	// dead creature's creature id
	ObjectID_t m_ObjectID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDiedFactory;
//
// Factory for GCCreatureDied
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDiedFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCCreatureDied(); }

	// get packet name
	string getPacketName() const  { return "GCCreatureDied"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_CREATURE_DIED; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCCreatureDiedPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDiedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDiedHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCCreatureDied* pPacket, Player* pPlayer) ;

};

#endif
