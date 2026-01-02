//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDeleteandPickUpOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DELETE_AND_PICKUP_OK_H__
#define __GC_DELETE_AND_PICKUP_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOK;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOK : public Packet {

public :
	GCDeleteandPickUpOK() {};
    ~GCDeleteandPickUpOK() {};
	// Initialize the packet by reading data from the input stream.
    void read(SocketInputStream & iStream) ;
		    
	// Serialize the packet into the output stream.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DELETE_AND_PICKUP_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// Use GCDeleteandPickUpOKPacketSize if that constant is defined.
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "GCDeleteandPickUpOK"; }
	
	// get packet's debug string
	string toString() const ;
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOKFactory;
//
// Factory for GCDeleteandPickUpOK
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCDeleteandPickUpOK(); }

	// get packet name
	string getPacketName() const  { return "GCDeleteandPickUpOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DELETE_AND_PICKUP_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// Use GCDeleteandPickUpOKPacketSize if that constant is defined.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCDeleteandPickUpOK* pPacket, Player* player) ;
};

#endif
