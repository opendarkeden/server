//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSilverCoating.h 
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SILVER_COATING_H__
#define __CG_SILVER_COATING_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoating
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoating : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t   getPacketID() const throw()   { return PACKET_CG_SILVER_COATING; }
	PacketSize_t getPacketSize() const throw() { return szObjectID; }
	string       getPacketName() const throw() { return "CGSilverCoating"; }
	string       toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private:
	ObjectID_t m_ObjectID; // Item Object ID

};


//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoatingFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoatingFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGSilverCoating(); }
	string getPacketName() const throw() { return "CGSilverCoating"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SILVER_COATING; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoatingHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoatingHandler 
{
public:
	static void execute(CGSilverCoating* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
