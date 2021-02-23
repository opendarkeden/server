//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCUntransformOK.h 
// Written By  :  Elca
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNTRANSFORM_OK_H__
#define __GC_UNTRANSFORM_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOK;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCUntransformOK : public Packet {

public :

	// constructor
	GCUntransformOK() throw() {}
	GCUntransformOK(Coord_t x, Coord_t y, Dir_t dir) throw() : m_X(x), m_Y(y), m_Dir(dir) {}


public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_UNTRANSFORM_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szCoord + szCoord + szDir; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCUntransformOK"; }
	
	// get packet's debug string
	string toString() const throw();
	

public :

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y ; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }
	

private : 

	Coord_t m_X;   // 목표 X 좌표
	Coord_t m_Y;   // 목표 Y 좌표
	Dir_t m_Dir;   // 목표 방향

};


//////////////////////////////////////////////////////////////////////
//
// class GCUntransformOKFactory;
//
// Factory for GCUntransformOK
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUntransformOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCUntransformOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_UNTRANSFORM_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szCoord + szCoord + szDir; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKHandler {

public :

	// execute packet's handler
	static void execute( GCUntransformOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
