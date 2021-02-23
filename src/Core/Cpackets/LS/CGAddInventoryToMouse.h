//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddInventoryToMouse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_INVENTORY_TO_MOUSE_H__
#define __CG_ADD_INVENTORY_TO_MOUSE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddInventoryToMouse;
//////////////////////////////////////////////////////////////////////////////

class CGAddInventoryToMouse : public Packet 
{
public:
	CGAddInventoryToMouse() throw();
	~CGAddInventoryToMouse() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_INVENTORY_TO_MOUSE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName() const throw() { return "CGAddInventoryToMouse"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	CoordInven_t getX() const throw() { return m_InvenX; }
	void setX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getY() const throw() { return m_InvenY; }
	void setY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t m_ObjectID;

	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddInventoryToMouseFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddInventoryToMouseFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddInventoryToMouse(); }
	string getPacketName() const throw() { return "CGAddInventoryToMouse"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_INVENTORY_TO_MOUSE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddInventoryToMouseHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddInventoryToMouseHandler 
{
public:
	static void execute(CGAddInventoryToMouse* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
