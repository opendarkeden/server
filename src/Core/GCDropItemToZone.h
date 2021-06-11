//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDropItemToZone.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DROP_ITEM_TO_ZONE_H__
#define __GC_DROP_ITEM_TO_ZONE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include "GCAddItemToZone.h"


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZone;
//
////////////////////////////////////////////////////////////////////

class GCDropItemToZone : public GCAddItemToZone {

public :

	GCDropItemToZone() ;
	~GCDropItemToZone() ;
	
	PacketSize_t getPacketSize() const  { return GCAddItemToZone::getPacketSize() + szObjectID; }

    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DROP_ITEM_TO_ZONE; }
	
	// get packet's name
	string getPacketName() const  { return "GCDropItemToZone"; }

	// get packet's debug string
	string toString() const ;

public:
	ObjectID_t getDropPetOID() const { return m_DropPetOID; }
	void setDropPetOID(ObjectID_t PetOID ) { m_DropPetOID = PetOID; }

private:
	ObjectID_t	m_DropPetOID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZoneFactory;
//
// Factory for GCDropItemToZone
//
//////////////////////////////////////////////////////////////////////

class GCDropItemToZoneFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCDropItemToZone(); }

	// get packet name
	string getPacketName() const  { return "GCDropItemToZone"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DROP_ITEM_TO_ZONE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCDropItemToZonePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + 255 + szDurability + szItemNum + szBYTE +(szObjectID + szBYTE + szItemType + szItemNum + szSlotID)* 12 + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZoneHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDropItemToZoneHandler {

public :

	// execute packet's handler
	static void execute(GCDropItemToZone* pPacket, Player* pPlayer) ;

};

#endif
