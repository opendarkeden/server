//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToItem.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ITEM_TO_ITEM_H__
#define __CG_ADD_ITEM_TO_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItem;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItem : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_ITEM_TO_ITEM; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName() const throw() { return "CGAddItemToItem"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	CoordInven_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	CoordInven_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }

private :
	ObjectID_t   m_ObjectID;	// ObjectID
	CoordInven_t m_X;			// Coord X
	CoordInven_t m_Y;			// Coord Y
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddItemToItem(); }
	string getPacketName() const throw() { return "CGAddItemToItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_ITEM_TO_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItemHandler 
{
public:
	static void execute(CGAddItemToItem* pCGAddItemToItem, Player* pPlayer) throw(Error);

};

#endif
