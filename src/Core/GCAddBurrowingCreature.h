//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBurrowingCreature.h 
// Written By  : crazydog 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_BURROWING_CREATURE_H__
#define __GC_ADD_BURROWING_CREATURE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddBurrowingCreature;
// 시야 안에 BurrowingCreature 가 들어왔을 경우, 
// 이 패킷에 BurrowingCreature 정보를 담아서 전송받는다.
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreature : public Packet 
{
public:
    GCAddBurrowingCreature() {};
    ~GCAddBurrowingCreature() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_BURROWING_CREATURE; }
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID + szBYTE + m_Name.size() + szCoord + szCoord; 
	}
	string getPacketName() const  { return "GCAddBurrowingCreature"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	string getName() const  { return m_Name; }
	void setName(string name)  { m_Name = name; }

	Coord_t getX() const  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

private:
    ObjectID_t m_ObjectID;
    string     m_Name;
   	Coord_t    m_X;
	Coord_t    m_Y;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddBurrowingCreatureFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddBurrowingCreature(); }
	string getPacketName() const  { return "GCAddBurrowingCreature"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_BURROWING_CREATURE; }
	PacketSize_t getPacketMaxSize() const  
	{
		return szObjectID + szBYTE + 20 + szCoord + szCoord; 
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// class GCAddBurrowingCreatureHandler;
//
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureHandler 
{
public:
	static void execute(GCAddBurrowingCreature* pPacket, Player* pPlayer) ;
};

#endif
