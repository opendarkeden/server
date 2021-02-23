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
	CGUsePowerPoint () throw ();
	~CGUsePowerPoint () throw ();
	
public:
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
    PacketID_t getPacketID () const throw () { return PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketSize () const throw () { return 0; }
	string getPacketName () const throw () { return "CGUsePowerPoint"; }
	string toString () const throw ();
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointFactory : public PacketFactory 
{
public:
	Packet * createPacket () throw () { return new CGUsePowerPoint(); }
	string getPacketName () const throw () { return "CGUsePowerPoint"; }
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketMaxSize () const throw () { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointHandler 
{
public:
	static void execute ( CGUsePowerPoint * pCGUsePowerPoint , Player * pPlayer ) throw (ProtocolException, Error);
};


#endif

