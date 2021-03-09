//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttack.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_H__
#define __GC_ATTACK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttack;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCAttack : public Packet {

public :
	
	// constructor
	GCAttack() ;
	
	// destructor
	~GCAttack() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_ATTACK; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord + szCoord + szDir ; }

	// get packet's name
	string getPacketName() const  { return "GCAttack"; }
	
	// get packet's debug string
	string toString() const ;

	// get Object ID 
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID)  { m_ObjectID = objectID; }

	// get/set X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	// get/set Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }


private :

	ObjectID_t m_ObjectID;		// 크리처 아이디
	Coord_t m_X;				// X 좌표
	Coord_t m_Y;				// Y 좌표
	Dir_t m_Dir;				// 방향

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackFactory;
//
// Factory for GCAttack
//
//////////////////////////////////////////////////////////////////////

class GCAttackFactory : public PacketFactory {

public :
	
	// constructor
	GCAttackFactory()  {}
	
	// destructor
	virtual ~GCAttackFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCAttack(); }

	// get packet name
	string getPacketName() const  { return "GCAttack"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ATTACK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord + szDir ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackHandler {

public :

	// execute packet's handler
	static void execute(GCAttack* pGCAttack, Player* pPlayer) ;

};

#endif
