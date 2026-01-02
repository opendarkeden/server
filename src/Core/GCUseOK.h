//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_OK_H__
#define __GC_USE_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseOK : public ModifyInfo {

public :

	// Constructor
	GCUseOK() ;

	// Desctructor
	~GCUseOK() ;
	
	// Initialize from the incoming stream.
    void read(SocketInputStream & iStream) ;
		    
	// Write the packet payload to the outgoing stream.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_USE_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// Use the const static GCUseOKPacketSize for efficiency.
	PacketSize_t getPacketSize() const  { return ModifyInfo::getPacketSize(); }

	// get packet name
	string getPacketName() const  { return "GCUseOK"; }
	
	// get packet's debug string
	string toString() const ;

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKFactory;
//
// Factory for GCUseOK
//
//////////////////////////////////////////////////////////////////////

class GCUseOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCUseOK(); }

	// get packet name
	string getPacketName() const  { return "GCUseOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_USE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// Use the const static GCUseOKPacketSize for efficiency.
	PacketSize_t getPacketMaxSize() const  { return ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCUseOK* pPacket, Player* player) ;
};

#endif
