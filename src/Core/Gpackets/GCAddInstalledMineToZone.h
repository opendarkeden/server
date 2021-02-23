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
	GCAddInstalledMineToZone() throw();
	~GCAddInstalledMineToZone() throw();
public:
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE; }
	string getPacketName() const throw() { return "GCAddInstalledMineToZone"; }
	string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddInstalledMineToZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddInstalledMineToZoneFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddInstalledMineToZone(); }
	string getPacketName() const throw() { return "GCAddInstalledMineToZone"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + 255 + szDurability + szItemNum + szBYTE +(szObjectID + szBYTE + szItemType + szItemNum + szSlotID)* 12; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddInstalledMineToZoneHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddInstalledMineToZoneHandler 
{
public:
	static void execute(GCAddInstalledMineToZone* pPacket, Player* pPlayer) throw(Error);
};

#endif
