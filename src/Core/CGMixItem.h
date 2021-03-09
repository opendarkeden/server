//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMixItem.h 
// Written By  : excel96
// Description : 
// 인벤토리 안의 아이템을 사용할 때, 클라이언트가 X, Y 및 ObjectID를
// 보내면 아이템 클래스에 따라서, 서버가 이에 맞는 코드를 처리한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MIX_ITEM_H__
#define __CG_MIX_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Assert1.h"

//////////////////////////////////////////////////////////////////////////////
// class CGMixItem;
//////////////////////////////////////////////////////////////////////////////

class CGMixItem : public Packet 
{
public:
    CGMixItem() {};
    ~CGMixItem() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_MIX_ITEM; }
	PacketSize_t getPacketSize() const  { return szObjectID + szCoordInven + szCoordInven + (szObjectID * 2); }
	string getPacketName() const  { return "CGMixItem"; }
	string toString() const ;
	
public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	CoordInven_t getX() const  { return m_InvenX; }
	void setX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	CoordInven_t getY() const  { return m_InvenY; }
	void setY(CoordInven_t InvenY)  { m_InvenY = InvenY; }

	ObjectID_t getTargetObjectID(uint index ) const  { Assert(index<2); return m_TargetObjectID[index]; }
	void setTargetObjectID(uint index, ObjectID_t oid )  { Assert(index<2); m_TargetObjectID[index] = oid; }

private:
	ObjectID_t   m_ObjectID; // 아이템의 object id 
	CoordInven_t m_InvenX;   // 아이템의 인벤토리 좌표 X
	CoordInven_t m_InvenY;   // 아이템의 인벤토리 좌표 Y

	ObjectID_t	m_TargetObjectID[2];	// 합칠 두 아이템의 오브젝트 ID
};


//////////////////////////////////////////////////////////////////////////////
// class CGMixItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGMixItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGMixItem(); }
	string getPacketName() const  { return "CGMixItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_MIX_ITEM; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoordInven + szCoordInven + (szObjectID * 2); }
};


//////////////////////////////////////////////////////////////////////////////
// class CGMixItemHandler;
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

class CGMixItemHandler 
{
public:
	static void execute(CGMixItem* pPacket, Player* pPlayer) ;

#ifdef __GAME_SERVER__
public:
	static void executeMix(CGMixItem* pPacket, Player* pPlayer, Item* pItem) ;
	static void executeDetach(CGMixItem* pPacket, Player* pPlayer, Item* pItem) ;
	static void executeClearOption(CGMixItem* pPacket, Player* pPlayer, Item* pItem) ;
#endif

};

#endif
