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
    GCNPCSay() {};
    ~GCNPCSay() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_NPC_SAY; }
	PacketSize_t getPacketSize() const  { return szObjectID + szScriptID + szBYTE; }
	string getPacketName() const  { return "GCNPCSay"; }
	string toString() const ;

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
	Packet* createPacket()  { return new GCNPCSay(); }
	string getPacketName() const  { return "GCNPCSay"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NPC_SAY; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szScriptID + szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayHandler 
{
public:
	static void execute(GCNPCSay* pPacket, Player* pPlayer) ;
};

#endif
