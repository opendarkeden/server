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
	CGAddMouseToInventory() ;
	~CGAddMouseToInventory() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketSize() const  { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName() const  { return "CGAddMouseToInventory"; }
	string toString() const ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	//ObjectID_t getInventoryItemObjectID()  { return m_InventoryItemObjectID; }
	//void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID)  { m_InventoryItemObjectID = InventoryItemObjectID; }

	CoordInven_t getInvenX() const  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t m_ObjectID;
	// 보조 인벤토리 아이템의 오브젝트 아이디. 0이면 메인 인벤토리에서 꺼냄
	//ObjectID_t m_InventoryItemObjectID;

	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddMouseToInventory(); }
	string getPacketName() const  { return "CGAddMouseToInventory"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryHandler 
{
public:
	static void execute(CGAddMouseToInventory* pPacket, Player* player) ;
};

#endif
