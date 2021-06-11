//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGTameMonster 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_TAME_MONSTER_H__
#define __CG_TAME_MONSTER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGTameMonster;
//
//////////////////////////////////////////////////////////////////////

class CGTameMonster : public Packet {

public:
	CGTameMonster() ;
	~CGTameMonster() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_TAME_MONSTER; }
	PacketSize_t getPacketSize() const  { return szObjectID; }
	string getPacketName() const  { return "CGTameMonster"; }
	string toString() const ;
	
public:
	// get/set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	
private :
	
	ObjectID_t m_ObjectID;  // ObjectID
};


//////////////////////////////////////////////////////////////////////
//
// class CGTameMonsterFactory;
//
// Factory for CGTameMonster
//
//////////////////////////////////////////////////////////////////////

class CGTameMonsterFactory : public PacketFactory {

public:
	CGTameMonsterFactory()  {}
	virtual ~CGTameMonsterFactory()  {}

public:
	Packet* createPacket()  { return new CGTameMonster(); }
	string getPacketName() const  { return "CGTameMonster"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_TAME_MONSTER; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////
//
// class CGTameMonsterHandler;
//
//////////////////////////////////////////////////////////////////////

class CGTameMonsterHandler {
	
public:
	static void execute(CGTameMonster* pCGTameMonster, Player* player) ;
};

#endif
