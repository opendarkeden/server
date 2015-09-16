//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOff.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OFF_H__
#define __GC_TAKE_OFF_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCTakeOff;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCTakeOff : public Packet {

public :
	
	// constructor
	GCTakeOff() throw();
	
	// destructor
	~GCTakeOff() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_TAKE_OFF; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSlotID; }

	// get packet's name
	string getPacketName() const throw() { return "GCTakeOff"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private :

	// ObjectID
	ObjectID_t m_ObjectID;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOffFactory;
//
// Factory for GCTakeOff
//
//////////////////////////////////////////////////////////////////////

class GCTakeOffFactory : public PacketFactory {

public :
	
	// constructor
	GCTakeOffFactory() throw() {}
	
	// destructor
	virtual ~GCTakeOffFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCTakeOff(); }

	// get packet name
	string getPacketName() const throw() { return "GCTakeOff"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TAKE_OFF; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSlotID;}

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOffHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOffHandler {

public :

	// execute packet's handler
	static void execute(GCTakeOff* pGCTakeOff, Player* pPlayer) throw(Error);

};

#endif
