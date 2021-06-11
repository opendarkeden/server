//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonsterFromBurrowing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_MONSTER_FROM_BURROWING_H__
#define __GC_ADD_MONSTER_FROM_BURROWING_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowing;
////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowing : public Packet 
{
public:
	GCAddMonsterFromBurrowing() ;
	virtual ~GCAddMonsterFromBurrowing() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_MONSTER_FROM_BURROWING; }
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID + // object id
			szMonsterType + // monster type
			szBYTE + // monster name length
			m_MonsterName.size() + // monster name
			szColor + // monster main color
			szColor +  // monster sub color
			szCoord + // x coord
			szCoord + // y coord
			szDir +  // direction
			m_pEffectInfo->getSize() + // effects info on monster
			szHP* 2; // current & max hp
	}
	string getPacketName() const  { return "GCAddMonsterFromBurrowing"; }
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

private :
    ObjectID_t    m_ObjectID;    // object id
	MonsterType_t m_MonsterType; // monster type
	string        m_MonsterName; // monster name
	Color_t       m_MainColor;   // monster main color
	Color_t       m_SubColor;    // monster sub color
   	Coord_t       m_X;           // x coord.
	Coord_t       m_Y;           // y coord.
	Dir_t         m_Dir;         // monster direction
	EffectInfo*   m_pEffectInfo; // effects info on monster
	HP_t          m_CurrentHP;   // current hp
	HP_t          m_MaxHP;       // maximum hp

};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowingFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowingFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddMonsterFromBurrowing(); }
	string getPacketName() const  { return "GCAddMonsterFromBurrowing"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_MONSTER_FROM_BURROWING; }
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szObjectID               // object id
			+ szMonsterType             // monster type
			+ szBYTE                    // monster name length
			+ 32                        // monster namx max
			+ szColor + szColor         // monster main & sub color 
			+ szCoord + szCoord + szDir // monster x, y coord & direction
			+ EffectInfo::getMaxSize()  // effects info on monster
			+ szHP* 2;                 // current & max hp
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowingHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowingHandler 
{
public:
	static void execute(GCAddMonsterFromBurrowing* pPacket, Player* pPlayer) ;

};

#endif
