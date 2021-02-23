//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCSayDynamic.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_SAY_DYNAMIC_H__
#define __GC_NPC_SAY_DYNAMIC_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayDynamic;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayDynamic : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NPC_SAY_DYNAMIC; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + m_Message.size(); }
	string getPacketName() const throw() { return "GCNPCSayDynamic"; }
	string toString() const throw();

	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID) throw() { m_ObjectID = creatureID; }

	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }

private:
	ObjectID_t m_ObjectID; // NPC's object id
	string     m_Message;  // chatting message
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayDynamicFactory;
//////////////////////////////////////////////////////////////////////////////


class GCNPCSayDynamicFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNPCSayDynamic(); }
	string getPacketName() const throw() { return "GCNPCSayDynamic"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NPC_SAY_DYNAMIC; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE + 2048 ; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayDynamicHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayDynamicHandler 
{
public:
	static void execute(GCNPCSayDynamic* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
