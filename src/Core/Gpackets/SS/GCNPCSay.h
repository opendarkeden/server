//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCSay.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_SAY_H__
#define __GC_NPC_SAY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNPCSay;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class GCNPCSay : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NPC_SAY; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szScriptID + szBYTE; }
	string getPacketName() const throw() { return "GCNPCSay"; }
	string toString() const throw();

	ObjectID_t getObjectID(void) const { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID) { m_ObjectID = creatureID; }

	ScriptID_t getScriptID(void) const { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) { m_ScriptID = scriptID; }

	BYTE getSubjectID(void) const { return m_SubjectID; }
	void setSubjectID(BYTE subjectID) { m_SubjectID = subjectID; }

private:
	ObjectID_t m_ObjectID;  // creature object id
	ScriptID_t m_ScriptID;  // script id
	BYTE       m_SubjectID; // subject id
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayFactory;
// Factory for GCNPCSay
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNPCSay(); }
	string getPacketName() const throw() { return "GCNPCSay"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NPC_SAY; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szScriptID + szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayHandler 
{
public:
	static void execute(GCNPCSay* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
