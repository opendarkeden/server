//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOutFail.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OUT_FAIL_H__
#define __GC_TAKE_OUT_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFail;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFail : public Packet {

public :
	GCTakeOutFail() {};
    ~GCTakeOutFail() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_TAKE_OUT_FAIL; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "GCTakeOutFail"; }
	
	// get packet's debug string
	string toString() const ;
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailFactory;
//
// Factory for GCTakeOutFail
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCTakeOutFail(); }

	// get packet name
	string getPacketName() const  { return "GCTakeOutFail"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_TAKE_OUT_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailHandler {
	
public :

	// execute packet's handler
	static void execute(GCTakeOutFail* pPacket, Player* player) ;
};

#endif
