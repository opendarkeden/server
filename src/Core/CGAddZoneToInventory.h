//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ZONE_TO_INVENTORY_H__
#define __CG_ADD_ZONE_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventory;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventory : public Packet 
{
public:
	CGAddZoneToInventory() throw();
	~CGAddZoneToInventory() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_ZONE_TO_INVENTORY; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }
	string getPacketName() const throw() { return "CGAddZoneToInventory"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	Coord_t getZoneX() const throw() { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) throw() { m_ZoneX = ZoneX; }

	Coord_t getZoneY() const throw() { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) throw() { m_ZoneY = ZoneY; }

	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t   m_ObjectID;
	Coord_t      m_ZoneX;
	Coord_t      m_ZoneY;
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddZoneToInventory(); }
	string getPacketName() const throw() { return "CGAddZoneToInventory"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_ZONE_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventoryHandler 
{
public:
	static void execute(CGAddZoneToInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
