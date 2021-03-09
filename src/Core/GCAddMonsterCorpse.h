//--------------------------------------------------------------------------------
// 
// Filename    : GCAddMonsterCorpse.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_MONSTER_CORPSE_H__
#define __GC_ADD_MONSTER_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpse;
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpse : public Packet {

public :
	GCAddMonsterCorpse() {};
    ~GCAddMonsterCorpse() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_MONSTER_CORPSE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterCorpsePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID + 
			szMonsterType + 
			szBYTE +
			m_MonsterName.size() +
			szCoord + 
			szCoord + 
			szDir + 
			szbool +
			szBYTE +
			szObjectID; 
	}

	// get packet's name
	string getPacketName() const  { return "GCAddMonsterCorpse"; }
	
	// get packet's debug string
	string toString() const ;

public :

	// get/set creature ID 
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get/set monster type
	MonsterType_t getMonsterType() const  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType)  { m_MonsterType = monsterType; }

	// get/set monster name
	string getMonsterName() const  { return m_MonsterName; }
	void setMonsterName(string name)  { m_MonsterName = name; }

	// get/set X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	// get/set Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	bool gethasHead() const  { return m_bhasHead; }
	void sethasHead(bool bhasHead)  { m_bhasHead = bhasHead; }

	// get/set Treasure Count
	BYTE getTreasureCount() const  { return m_TreasureCount; }
	void setTreasureCount(BYTE Count)  { m_TreasureCount = Count; }

	ObjectID_t getLastKiller() const { return m_LastKiller; }
	void setLastKiller(ObjectID_t id ) { m_LastKiller = id; }

private :
	
    ObjectID_t m_ObjectID;			// OID

	MonsterType_t m_MonsterType; 	// 몬스터 타입

	string m_MonsterName;

   	Coord_t m_X;					// X 좌표
	Coord_t m_Y;					// Y 좌표
	Dir_t m_Dir;					// 방향
	bool m_bhasHead;				// 머리가 있는가?
	
	BYTE m_TreasureCount;

	ObjectID_t m_LastKiller;

};


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpseFactory;
//
// Factory for GCAddMonsterCorpse
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCAddMonsterCorpse(); }

	// get packet name
	string getPacketName() const  { return "GCAddMonsterCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_MONSTER_CORPSE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterCorpsePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szObjectID + 
			szMonsterType + 
			szBYTE + 
			128 +
			szCoord + 
			szCoord + 
			szDir + 
			szbool +
 			szBYTE +
			szObjectID; 
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddMonsterCorpse* pPacket, Player* pPlayer) ;

};

#endif
