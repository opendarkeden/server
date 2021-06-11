//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMineExplosionOK2.h 
// Written By  : elca@ewestsoft.com
// Description : 기술에 당한 자가 받는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MINE_EXPLOSION_OK_2_H__
#define __GC_MINE_EXPLOSION_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMineExplosionOK2;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK2 : public Packet {

public :
	
	// constructor
	GCMineExplosionOK2() ;
	
	// destructor
	~GCMineExplosionOK2() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_MINE_EXPLOSION_OK_2; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szCoord*2+ szDir + szItemType
	   + szBYTE + szObjectID* m_CListNum; }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 5 

	// get packet's name
	string getPacketName() const  { return "GCMineExplosionOK2"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get / set Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }
	
	// get / set Dir
	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t r)  { m_Dir = r; }
	
	// get / set ItemType
	ItemType_t getItemType() const  { return m_ItemType; }
	void setItemType(ItemType_t r)  { m_ItemType = r; }

	void setXYDir(Coord_t X, Coord_t Y, Dir_t R)  { m_X = X; m_Y = Y; m_Dir = R;}

    // get / set Creature List Number
    BYTE getCListNum() const  { return m_CListNum; }
    void setCListNum(BYTE CListNum)  { m_CListNum = CListNum; }


    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) ;

	// Clear Creature List
    void clearCList()  { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement()  { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }


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
// class GCMineExplosionOK2Factory;
//
// Factory for GCMineExplosionOK2
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCMineExplosionOK2Factory()  {}
	
	// destructor
	virtual ~GCMineExplosionOK2Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCMineExplosionOK2(); }

	// get packet name
	string getPacketName() const  { return "GCMineExplosionOK2"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MINE_EXPLOSION_OK_2; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize() const  { return szCoord*2 + szDir + szItemType 
		+ szBYTE + szWORD + szObjectID + 255; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMineExplosionOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCMineExplosionOK2Handler {

public :

	// execute packet's handler
	static void execute(GCMineExplosionOK2* pGCMineExplosionOK2, Player* pPlayer) ;

};

#endif
