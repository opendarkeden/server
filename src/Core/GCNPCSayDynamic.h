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
    GCNPCSayDynamic() {};
    ~GCNPCSayDynamic() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_NPC_SAY_DYNAMIC; }
	PacketSize_t getPacketSize() const  { return szObjectID + szBYTE + m_Message.size(); }
	string getPacketName() const  { return "GCNPCSayDynamic"; }
	string toString() const ;

	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID)  { m_ObjectID = creatureID; }

	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }

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
	Packet* createPacket()  { return new GCNPCSayDynamic(); }
	string getPacketName() const  { return "GCNPCSayDynamic"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NPC_SAY_DYNAMIC; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szBYTE + 2048 ; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCSayDynamicHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCSayDynamicHandler 
{
public:
	static void execute(GCNPCSayDynamic* pPacket, Player* pPlayer) ;

};

#endif
