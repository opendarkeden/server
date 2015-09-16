//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCrossCounterOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CROSS_COUNTER_OK_1_H__
#define __GC_CROSS_COUNTER_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1 : public ModifyInfo {

public :
	
	// constructor
	GCCrossCounterOK1() throw();
	
	// destructor
	~GCCrossCounterOK1() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_CROSS_COUNTER_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID + ModifyInfo::getPacketSize() + szSkillType; }

	// get packet's name
	string getPacketName() const throw() { return "GCCrossCounterOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set CEffectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// Counter SkillType
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1Factory;
//
// Factory for GCCrossCounterOK1
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCCrossCounterOK1Factory() throw() {}
	
	// destructor
	virtual ~GCCrossCounterOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCCrossCounterOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCCrossCounterOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CROSS_COUNTER_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + ModifyInfo::getPacketMaxSize() + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1Handler {

public :

	// execute packet's handler
	static void execute(GCCrossCounterOK1* pGCCrossCounterOK1, Player* pPlayer) throw(Error);

};

#endif
