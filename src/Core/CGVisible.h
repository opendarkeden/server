//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVisible.h 
// Written By  : crazydog
// Description : 박쥐나 늑대에서 원래모습으로 돌아오고싶을때..
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VISIBLE_H__
#define __CG_VISIBLE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGVisible;
//
//////////////////////////////////////////////////////////////////////

class CGVisible : public Packet {

public:
	CGVisible() {};
    virtual ~CGVisible() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_VISIBLE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGVisiblePacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet name
	string getPacketName() const  { return "CGVisible"; }
	
	// get packet's debug string
	string toString() const ;

};


//////////////////////////////////////////////////////////////////////
//
// class CGVisibleFactory;
//
// Factory for CGVisible
//
//////////////////////////////////////////////////////////////////////

class CGVisibleFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGVisible(); }

	// get packet name
	string getPacketName() const  { return "CGVisible"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_VISIBLE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGVisiblePacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGVisibleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGVisibleHandler {
	
public:

	// execute packet's handler
	static void execute(CGVisible* pPacket, Player* player) ;
};

#endif
