//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_1_H__
#define __GC_THROW_ITEM_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1 : public Packet {

public :
	
	// constructor
	GCThrowItemOK1() throw();
	
	// destructor
	~GCThrowItemOK1() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_THROW_ITEM_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID ; }

	// get packet's name
	string getPacketName() const throw() { return "GCThrowItemOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set TargetObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// TargetObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1Factory;
//
// Factory for GCThrowItemOK1
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK1Factory() throw() {}
	
	// destructor
	virtual ~GCThrowItemOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCThrowItemOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCThrowItemOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_THROW_ITEM_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1Handler {

public :

	// execute packet's handler
	static void execute(GCThrowItemOK1* pGCThrowItemOK1, Player* pPlayer) throw(Error);

};

#endif
