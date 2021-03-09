//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCAsk.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_ASK_H__
#define __GC_NPC_ASK_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAsk;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class GCNPCAsk : public Packet 
{
public:
	GCNPCAsk() ;
	virtual ~GCNPCAsk() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_NPC_ASK; }
	PacketSize_t getPacketSize() const  { return szObjectID + szScriptID + szNPCID; }
	string getPacketName() const  { return "GCNPCAsk"; }
	string toString() const ;

public:
	ObjectID_t getObjectID(void) const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	ScriptID_t getScriptID(void) const  { return m_ScriptID; }
	void setScriptID(ScriptID_t id)  { m_ScriptID = id; }

	NPCID_t	getNPCID() const  { return m_NPCID; }
	void setNPCID(NPCID_t npcID )  { m_NPCID = npcID; }

private:
	ObjectID_t m_ObjectID; // NPC's object id
	ScriptID_t m_ScriptID; // script id
	NPCID_t		m_NPCID;
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCNPCAsk(); }
	string getPacketName() const  { return "GCNPCAsk"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NPC_ASK; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szScriptID + szNPCID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskHandler 
{
public:
	static void execute(GCNPCAsk* pPacket, Player* pPlayer) ;
};

#endif
