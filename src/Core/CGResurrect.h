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
    CGResurrect() {};
    virtual ~CGResurrect() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_RESURRECT; }
	PacketSize_t getPacketSize() const  { return 0; }
	string getPacketName() const  { return "CGResurrect"; }
	string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectFactory;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGResurrect(); }
	string getPacketName() const  { return "CGResurrect"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_RESURRECT; }
	PacketSize_t getPacketMaxSize() const  { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectHandler;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectHandler 
{
public:
	static void execute(CGResurrect* pPacket, Player* player) ;
};

#endif
