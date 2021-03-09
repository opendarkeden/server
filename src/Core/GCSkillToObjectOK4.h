//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK4.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 				기술에 당한 사람을 볼 수 있는 분들이 받으시는 패킷(기술을 사용한 사람은 볼수 없는)
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_4_H__
#define __GC_SKILL_TO_OBJECT_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4 : public Packet {

public :
	
	// constructor
	GCSkillToObjectOK4() ;
	
	// destructor
	~GCSkillToObjectOK4() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SKILL_TO_OBJECT_OK_4; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID + szSkillType + szDuration + szBYTE; }

	// get packet's name
	string getPacketName() const  { return "GCSkillToObjectOK4"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const  { return m_ObjectID; }
	void setTargetObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType() const  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }
	
/*
	// get / set Target X,Y
	Coord_t getTargetX() const  { return m_TargetX; }
	Coord_t getTargetY() const  { return m_TargetY; }
	void setTargetXY(Coord_t X, Coord_t Y)  { m_TargetX = X; m_TargetY = Y; }
*/
	
	// get / set Duration
	Duration_t getDuration() const  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }
	
	// get / set CEffectID 
//	CEffectID_t getCEffectID() const  { return m_CEffectID; }
//	void setCEffectID(CEffectID_t e)  { m_CEffectID = e; }

	BYTE getGrade() const  { return m_Grade; }
	void setGrade(BYTE grade )  { m_Grade = grade; }

private :
	
	// ObjectID(Target)
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	// CEffectID
//	CEffectID_t m_CEffectID;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4Factory;
//
// Factory for GCSkillToObjectOK4
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK4Factory()  {}
	
	// destructor
	virtual ~GCSkillToObjectOK4Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToObjectOK4(); }

	// get packet name
	string getPacketName() const  { return "GCSkillToObjectOK4"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_4; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szSkillType + szDuration + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK4* pGCSkillToObjectOK4, Player* pPlayer) ;

};

#endif
