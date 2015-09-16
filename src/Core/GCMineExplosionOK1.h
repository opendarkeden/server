//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMineExplosionOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술에 당한 자가 받는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MINE_EXPLOSION_OK_1_H__
#define __GC_MINE_EXPLOSION_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMineExplosionOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK1 : public ModifyInfo {

public :
	
	// constructor
	GCMineExplosionOK1() throw();
	
	// destructor
	~GCMineExplosionOK1() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MINE_EXPLOSION_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szCoord*2 + szDir + szItemType 
		+ szBYTE + szObjectID* m_CListNum +  ModifyInfo::getPacketSize(); }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 2 

	// get packet's name
	string getPacketName() const throw() { return "GCMineExplosionOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	// get / set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }
	
	// get / set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t r) throw() { m_Dir = r; }

	// get / set ItemType
	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t r) throw() { m_ItemType = r; }

	void setXYDir(Coord_t X, Coord_t Y, Dir_t R) throw() { m_X = X; m_Y = Y; m_Dir = R;}

    // get / set Creature List Number
    BYTE getCListNum() const throw() { return m_CListNum; }
    void setCListNum(BYTE CListNum) throw() { m_CListNum = CListNum; }

    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) throw();

	// Clear Creature List
    void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }


private :
	
	// X, Y
	Coord_t m_X;

	Coord_t m_Y;

	// Dir
	Dir_t m_Dir;

	ItemType_t m_ItemType;

	// Creature List Num
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;

};


//////////////////////////////////////////////////////////////////////
//
// class GCMineExplosionOK1Factory;
//
// Factory for GCMineExplosionOK1
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCMineExplosionOK1Factory() throw() {}
	
	// destructor
	virtual ~GCMineExplosionOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMineExplosionOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCMineExplosionOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MINE_EXPLOSION_OK_1; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szCoord*2 + szDir + szItemType
	   + szBYTE + szWORD + szObjectID + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMineExplosionOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK1Handler {

public :

	// execute packet's handler
	static void execute(GCMineExplosionOK1* pGCMineExplosionOK1, Player* pPlayer) throw(Error);

};

#endif
