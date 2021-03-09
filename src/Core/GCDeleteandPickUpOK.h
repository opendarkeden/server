//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDeleteandPickUpOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DELETE_AND_PICKUP_OK_H__
#define __GC_DELETE_AND_PICKUP_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOK;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOK : public Packet {

public :
	GCDeleteandPickUpOK() {};
    ~GCDeleteandPickUpOK() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DELETE_AND_PICKUP_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCDeleteandPickUpOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "GCDeleteandPickUpOK"; }
	
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
// class GCDeleteandPickUpOKFactory;
//
// Factory for GCDeleteandPickUpOK
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCDeleteandPickUpOK(); }

	// get packet name
	string getPacketName() const  { return "GCDeleteandPickUpOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DELETE_AND_PICKUP_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCDeleteandPickUpOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCDeleteandPickUpOK* pPacket, Player* player) ;
};

#endif
