//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrect.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_RESURRECT_H__
#define __CG_RESURRECT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGResurrect;
//////////////////////////////////////////////////////////////////////////////

class CGResurrect : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_RESURRECT; }
	PacketSize_t getPacketSize() const throw() { return 0; }
	string getPacketName() const throw() { return "CGResurrect"; }
	string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectFactory;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGResurrect(); }
	string getPacketName() const throw() { return "CGResurrect"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_RESURRECT; }
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectHandler;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectHandler 
{
public:
	static void execute(CGResurrect* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
