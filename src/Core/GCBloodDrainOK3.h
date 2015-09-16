//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK3.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_3_H__
#define __GC_BLOOD_DRAIN_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3 : public Packet {

public :
	
	// constructor
	GCBloodDrainOK3() throw();
	
	// destructor
	~GCBloodDrainOK3() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_BLOOD_DRAIN_OK_3; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szObjectID; }

	// get packet's name
	string getPacketName() const throw() { return "GCBloodDrainOK3"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3Factory;
//
// Factory for GCBloodDrainOK3
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK3Factory() throw() {}
	
	// destructor
	virtual ~GCBloodDrainOK3Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCBloodDrainOK3(); }

	// get packet name
	string getPacketName() const throw() { return "GCBloodDrainOK3"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_BLOOD_DRAIN_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3Handler {

public :

	// execute packet's handler
	static void execute(GCBloodDrainOK3* pGCBloodDrainOK3, Player* pPlayer) throw(Error);

};

#endif
