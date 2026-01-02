//--------------------------------------------------------------------------------
// 
// Filename    : CGShopRequestList.h 
// Written By  : Rewster
// Description : Client requests the list of goods sold by a store
//               (type-specific rack) to browse and purchase items.
// 
//--------------------------------------------------------------------------------

#ifndef __CG_SHOP_REQUEST_LIST_H__
#define __CG_SHOP_REQUEST_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGShopRequestList;
//
//--------------------------------------------------------------------------------

class CGShopRequestList : public Packet {

public:
	CGShopRequestList() {};
    virtual ~CGShopRequestList() {};
	// Initialize from the incoming stream.
	void read(SocketInputStream & iStream) ;
		    
	// Write this packet to the outgoing stream.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SHOP_REQUEST_LIST; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// Use the const static CGShopRequestListPacketSize for efficiency.
	PacketSize_t getPacketSize() const  { return szObjectID+szShopRackType; }

	// get packet name
	string getPacketName() const  { return "CGShopRequestList"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	ShopRackType_t getRackType(void)  { return m_RackType; }
	void setRackType(ShopRackType_t type)  { m_RackType = type; }

private :
	
	// ObjectID
	ObjectID_t     m_ObjectID;
	ShopRackType_t m_RackType;

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListFactory;
//
// Factory for CGShopRequestList
//
//--------------------------------------------------------------------------------

class CGShopRequestListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGShopRequestList(); }

	// get packet name
	string getPacketName() const  { return "CGShopRequestList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SHOP_REQUEST_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szObjectID+szShopRackType; }

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListHandler;
//
//--------------------------------------------------------------------------------

class CGShopRequestListHandler {
	
public:

	// execute packet's handler
	static void execute(CGShopRequestList* pPacket, Player* player) ;
};

#endif
