//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddInstalledMineToZone.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_INSTALLED_MINE_TO_ZONE_H__
#define __GC_ADD_INSTALLED_MINE_TO_ZONE_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include "GCAddItemToZone.h"

//////////////////////////////////////////////////////////////////////////////
//
// class GCAddInstalledMineToZone;
//
//////////////////////////////////////////////////////////////////////////////

class GCAddInstalledMineToZone : public GCAddItemToZone 
{
public:
	GCAddInstalledMineToZone() ;
	~GCAddInstalledMineToZone() ;
public:
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE; }
	string getPacketName() const  { return "GCAddInstalledMineToZone"; }
	string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddInstalledMineToZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddInstalledMineToZoneFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddInstalledMineToZone(); }
	string getPacketName() const  { return "GCAddInstalledMineToZone"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + 255 + szDurability + szItemNum + szBYTE +(szObjectID + szBYTE + szItemType + szItemNum + szSlotID)* 12; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddInstalledMineToZoneHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddInstalledMineToZoneHandler 
{
public:
	static void execute(GCAddInstalledMineToZone* pPacket, Player* pPlayer) ;
};

#endif
