//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_INVENTORY_H__
#define __CG_ADD_MOUSE_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventory : public Packet 
{
public:
	CGAddMouseToInventory() throw();
	~CGAddMouseToInventory() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName() const throw() { return "CGAddMouseToInventory"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t m_ObjectID;
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddMouseToInventory(); }
	string getPacketName() const throw() { return "CGAddMouseToInventory"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryHandler 
{
public:
	static void execute(CGAddMouseToInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
