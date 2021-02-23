//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK6.h 
// Written By  : elca@ewestsoft.com
// Description : 기술에 당했는데 사용자는 볼 수 없는 자가 받는 packet 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_6_H__
#define __GC_SKILL_TO_TILE_OK_6_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK6;
//
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToTileOK6() throw();
	
	// destructor
	~GCSkillToTileOK6() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_TO_TILE_OK_6; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szCoord*2 + szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szObjectID* m_CListNum + szBYTE + ModifyInfo::getPacketSize(); }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 2 

	// get packet's name
	string getPacketName() const throw() { return "GCSkillToTileOK6"; }
	
	// get packet's debug string
	string toString() const throw();

	// get orign x, y
	Coord_t getOrgX() const throw() { return m_OrgX;}
	Coord_t getOrgY() const throw() { return m_OrgY;}
	// set origin x, y
	void setOrgXY(Coord_t X, Coord_t Y) throw() { m_OrgX = X; m_OrgY = Y;}
	

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	// get / set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }
	
	// get / set Range
	Range_t getRange() const throw() { return m_Range; }
	void setRange(Range_t r) throw() { m_Range = r; }

	// get / set Duration
	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

    // get / set Creature List Number
    BYTE getCListNum() const throw() { return m_CListNum; }
    void setCListNum(BYTE CListNum) throw() { m_CListNum = CListNum; }


    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) throw();

	// Clear Creature List
    void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade() const throw() { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }


private :
	
	// ObjectID
	Coord_t m_OrgX, m_OrgY;	// 기술 사용자의 위치.

	// SkillType
	SkillType_t m_SkillType;

	// X, Y
	Coord_t m_X;

	Coord_t m_Y;

	// Range
	Range_t m_Range;

	// Duration
	Duration_t m_Duration;

	// Creature List Num
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK6Factory;
//
// Factory for GCSkillToTileOK6
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK6Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToTileOK6Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToTileOK6(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillToTileOK6"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_TO_TILE_OK_6; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szCoord*2 + szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szWORD + szObjectID + szBYTE + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK6Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK6* pGCSkillToTileOK6, Player* pPlayer) throw(Error);

};

#endif
