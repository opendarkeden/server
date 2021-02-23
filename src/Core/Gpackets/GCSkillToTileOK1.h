//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 				기술 사용자에게 보내는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_1_H__
#define __GC_SKILL_TO_TILE_OK_1_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK1 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToTileOK1() throw();
	
	// destructor
	~GCSkillToTileOK1() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_TO_TILE_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szSkillType + szCEffectID + szCoord* 2
			+ szDuration + szBYTE + szRange + szObjectID* m_CListNum + szBYTE + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCSkillToTileOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set CEffectID
	CEffectID_t getCEffectID() const throw() { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID) throw() { m_CEffectID = CEffectID; }

	// get / set Duration
	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

	// get / set X, Y
	Coord_t getX() { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY() { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

	Range_t getRange() { return m_Range;}
	void setRange(Range_t r) { m_Range = r;}

	// get / set Creature List Number
	BYTE getCListNum() const throw() { return m_CListNum; }
	void setCListNum(BYTE CListNum) throw() { m_CListNum = CListNum; }

	// add / delete  Creature List
	void addCListElement(ObjectID_t ObjectID) throw();
	void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

	// pop front Element in Status List
	ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade() const { return m_Grade; }
	void setGrade( BYTE grade ) { m_Grade = grade; }

private :
	
	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// Duration
	Duration_t m_Duration;

	// Range
	Range_t m_Range;

	// X, Y Position
	Coord_t m_X;
	Coord_t m_Y;

	// CreatureList Element Number 
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK1Factory;
//
// Factory for GCSkillToTileOK1
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK1Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToTileOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToTileOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillToTileOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_TO_TILE_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szCEffectID + szCoord* 2
			+ szDuration + szBYTE + szBYTE + +szRange + szWORD + szObjectID + szBYTE + ModifyInfo::getPacketMaxSize(); }

};



//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK1Handler;
//
//////////////////////////////////////////////////////////////////////
class GCSkillToTileOK1Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK1* pGCSkillToTileOK1, Player* pPlayer) throw(Error);

};

#endif
