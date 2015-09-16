//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 					기술을 쓴 자신에게 보내는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_1_H__
#define __GC_SKILL_TO_OBJECT_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToObjectOK1() throw();
	
	// destructor
	~GCSkillToObjectOK1() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_TO_OBJECT_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szSkillType + szCEffectID + szObjectID + szDuration + szBYTE + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCSkillToObjectOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set CEffectID
	CEffectID_t getCEffectID() const throw() { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID) throw() { m_CEffectID = CEffectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }

	// get / set Duration
	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

	BYTE getGrade() const throw() { return m_Grade; }
	void setGrade(BYTE grade) throw() { m_Grade = grade; }

private :
	
	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// Duration
	Duration_t m_Duration;

	// Grade
	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1Factory;
//
// Factory for GCSkillToObjectOK1
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK1Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillToObjectOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szCEffectID + szObjectID + szDuration + szBYTE + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK1* pGCSkillToObjectOK1, Player* pPlayer) throw(Error);

};

#endif
