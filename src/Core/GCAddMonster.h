//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonster.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_MONSTER_H__
#define __GC_ADD_MONSTER_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddMonster;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonster : public Packet 
{
public:
	GCAddMonster() ;
	virtual ~GCAddMonster() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_MONSTER; }
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID +            // object id
			szMonsterType +            // monster type
			szBYTE +                   // monster name length
			m_MonsterName.size() +     // monster name
			szColor +                  // monster main color
			szColor +                  // sub color
			szCoord +                  // x coord.
			szCoord +                  // y coord.
			szDir +                    // monster direction
			m_pEffectInfo->getSize() + // effects info on monster
			szHP +                     // current hp
			szHP +                      // max hp
			szBYTE;						// from Flag
	}
	string getPacketName() const  { return "GCAddMonster"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	MonsterType_t getMonsterType() const  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType)  { m_MonsterType = monsterType; }

	string getMonsterName() const  { return m_MonsterName; }
	void setMonsterName(string name)  { m_MonsterName = name; }

	Color_t getMainColor() const  { return m_MainColor; }
	void setMainColor(Color_t color)  { m_MainColor = color; }

	Color_t getSubColor() const  { return m_SubColor; }
	void setSubColor(Color_t color)  { m_SubColor = color; }

	Coord_t getX() const  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	EffectInfo* getEffectInfo() const  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo)  { m_pEffectInfo = pEffectInfo; }

	HP_t getMaxHP() const  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP)  { m_MaxHP = MaxHP; }

	HP_t getCurrentHP() const  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

	BYTE getFromFlag(void) const { return m_FromFlag; }
	void setFromFlag(BYTE flag) { m_FromFlag = flag; }

private:
    ObjectID_t    m_ObjectID;     // object id
	MonsterType_t m_MonsterType;  // monster type
	string        m_MonsterName;  // monster name
	Color_t       m_MainColor;    // monster main color
	Color_t       m_SubColor;     // sub color
   	Coord_t       m_X;            // x coord.
	Coord_t       m_Y;            // y coord.
	Dir_t         m_Dir;          // monster direction
	EffectInfo*   m_pEffectInfo;  // effects info on monster
	HP_t          m_CurrentHP;    // current hp
	HP_t          m_MaxHP;        // max hp
	BYTE          m_FromFlag;     // 어디로부터인가? 정상일 경우에는 0, 포탈을 통했을 경우에는 1
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCAddMonster(); }

	// get packet name
	string getPacketName() const  { return "GCAddMonster"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_MONSTER; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szObjectID +            // object id
			szMonsterType +            // monster type
			szBYTE +                   // monster name length
			32 +                       // monster name max
			szColor +                  // monster main color
			szColor +                  // sub color
			szCoord +                  // x coord.
			szCoord +                  // y coord.
			szDir +                    // monster direction
			EffectInfo::getMaxSize() + // effects info on monster
			szHP +                     // current hp
			szHP +                      // max hp
			szBYTE;						// from Flag
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterHandler {

public :

	// execute packet's handler
	static void execute(GCAddMonster* pPacket, Player* pPlayer) ;

};

#endif
