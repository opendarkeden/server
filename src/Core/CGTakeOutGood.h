//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTakeOutGood.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TAKE_OUT_GOOD_H__
#define __CG_TAKE_OUT_GOOD_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGTakeOutGood;
//////////////////////////////////////////////////////////////////////////////

class CGTakeOutGood : public Packet 
{
public:
	CGTakeOutGood() throw();
	~CGTakeOutGood() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_TAKE_OUT_GOOD; }
	PacketSize_t getPacketSize() const throw() { return szObjectID; }
	string getPacketName() const throw() { return "CGTakeOutGood"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	ObjectID_t m_ObjectID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGTakeOutGoodFactory;
//////////////////////////////////////////////////////////////////////////////

class CGTakeOutGoodFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTakeOutGood(); }
	string getPacketName() const throw() { return "CGTakeOutGood"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_TAKE_OUT_GOOD; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGTakeOutGoodHandler;
//////////////////////////////////////////////////////////////////////////////

class CGTakeOutGoodHandler 
{
public:
	static void execute(CGTakeOutGood* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
