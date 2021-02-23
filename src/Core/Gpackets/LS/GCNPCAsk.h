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
	GCNPCAsk() throw();
	virtual ~GCNPCAsk() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NPC_ASK; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szScriptID + szNPCID; }
	string getPacketName() const throw() { return "GCNPCAsk"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID(void) const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ScriptID_t getScriptID(void) const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t id) throw() { m_ScriptID = id; }

	NPCID_t	getNPCID() const throw() { return m_NPCID; }
	void setNPCID( NPCID_t npcID ) throw() { m_NPCID = npcID; }

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
	Packet* createPacket() throw() { return new GCNPCAsk(); }
	string getPacketName() const throw() { return "GCNPCAsk"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NPC_ASK; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szScriptID + szNPCID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskHandler 
{
public:
	static void execute(GCNPCAsk* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
