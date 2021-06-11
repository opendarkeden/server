//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePowerPoint.h 
// Written By  : bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_POWER_POINT_H__
#define __CG_USE_POWER_POINT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPoint;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPoint : public Packet
{
public:
	CGUsePowerPoint () ;
	~CGUsePowerPoint () ;
	
public:
    void read (SocketInputStream & iStream ) ;
    void write (SocketOutputStream & oStream ) const ;
	void execute (Player * pPlayer ) ;
    PacketID_t getPacketID () const  { return PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketSize () const  { return 0; }
	string getPacketName () const  { return "CGUsePowerPoint"; }
	string toString () const ;
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointFactory : public PacketFactory 
{
public:
	Packet * createPacket ()  { return new CGUsePowerPoint(); }
	string getPacketName () const  { return "CGUsePowerPoint"; }
	PacketID_t getPacketID () const  { return Packet::PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketMaxSize () const  { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointHandler 
{
public:
	static void execute (CGUsePowerPoint * pCGUsePowerPoint , Player * pPlayer ) ;
};


#endif

