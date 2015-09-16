//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToZone.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_ZONE_H__
#define __CG_ADD_MOUSE_TO_ZONE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToZone;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToZone : public Packet 
{
public:
	CGAddMouseToZone() throw();
	~CGAddMouseToZone() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_MOUSE_TO_ZONE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID; }
	string getPacketName() const throw() { return "CGAddMouseToZone"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	ObjectID_t m_ObjectID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToZoneFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddMouseToZone(); }
	string getPacketName() const throw() { return "CGAddMouseToZone"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_MOUSE_TO_ZONE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToZoneHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToZoneHandler 
{
public:
	static void execute(CGAddMouseToZone* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
