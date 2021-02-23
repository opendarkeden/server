//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK3.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 				기술을 사용한 사람을 볼 수 있는 분들이 받으시는 패킷(기술에 당한 사람은 볼수 없는)
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_3_H__
#define __GC_SKILL_TO_OBJECT_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3 : public Packet {

public :
	
	// constructor
	GCSkillToObjectOK3() throw();
	
	// destructor
	~GCSkillToObjectOK3() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_TO_OBJECT_OK_3; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSkillType + szCoord*2 + szBYTE; }

	// get packet's name
	string getPacketName() const throw() { return "GCSkillToObjectOK3"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Target X,Y
	Coord_t getTargetX() const throw() { return m_TargetX; }
	Coord_t getTargetY() const throw() { return m_TargetY; }
	void setTargetXY(Coord_t X, Coord_t Y) throw() { m_TargetX = X; m_TargetY = Y; }

	
	// get / set CEffectID 
//	CEffectID_t getCEffectID() const throw() { return m_CEffectID; }
//	void setCEffectID(CEffectID_t e) throw() { m_CEffectID = e; }

	BYTE getGrade() const throw() { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// TargetObjectID
	Coord_t m_TargetX, m_TargetY;
	

	// CEffectID
//	CEffectID_t m_CEffectID;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3Factory;
//
// Factory for GCSkillToObjectOK3
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK3Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK3Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK3(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillToObjectOK3"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_3; }

	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSkillType + szCoord*2 + szBYTE; }


};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK3* pGCSkillToObjectOK3, Player* pPlayer) throw(Error);

};

#endif
