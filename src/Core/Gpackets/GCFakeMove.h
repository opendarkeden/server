//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFakeMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FAKE_MOVE_H__
#define __GC_FAKE_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMove;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(ObjectID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCFakeMove : public Packet {

public :

	// constructor
	GCFakeMove() throw()
	{
	}

	GCFakeMove(ObjectID_t objectID, Coord_t x, Coord_t y, Coord_t x2, Coord_t y2) throw()
		: m_ObjectID(objectID), m_ToX(x2), m_ToY(y2)
	{
	}


public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_FAKE_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCFakeMovePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szObjectID + 2*szCoord; }

	// get packet's name
	string getPacketName() const throw() { return "GCFakeMove"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set Creature ID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	void setXY(Coord_t x2, Coord_t y2)
	{
		m_ToX = x2; 
		m_ToY = y2;
	}

	// get
	Coord_t getToX() const throw() { return m_ToX; }
	Coord_t getToY() const throw() { return m_ToY; }
	


private :
	
	ObjectID_t m_ObjectID;		// 크리처 아이디
	Coord_t m_ToX, m_ToY;		// 도착좌표 
};


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMoveFactory;
//
// Factory for GCFakeMove
//
//////////////////////////////////////////////////////////////////////

class GCFakeMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCFakeMove(); }

	// get packet name
	string getPacketName() const throw() { return "GCFakeMove"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_FAKE_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCFakeMovePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + 2*szCoord ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFakeMoveHandler {

public :

	// execute packet's handler
	static void execute(GCFakeMove* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
