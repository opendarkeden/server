////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeAddItem.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_ADD_ITEM_H__
#define __CG_TRADE_ADD_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeAddItem : public Packet 
{
public:
    CGTradeAddItem() {};
    virtual ~CGTradeAddItem() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_TRADE_ADD_ITEM; }
	PacketSize_t getPacketSize() const  { return szObjectID*2; }
	string getPacketName() const  { return "CGTradeAddItem"; }
	string toString() const ;
	
public:
	ObjectID_t getTargetObjectID() const  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id)  { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID() const  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id)  { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 ObjectID
	ObjectID_t m_ItemObjectID;   // 교환 리스트에 추가할 아이템의 OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeAddItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGTradeAddItem(); }
	string getPacketName() const  { return "CGTradeAddItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_TRADE_ADD_ITEM; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID*2; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeAddItem;
class Item;

class CGTradeAddItemHandler 
{
public:
	static void execute(CGTradeAddItem* pPacket, Player* player) ;
	static void executeSlayer(CGTradeAddItem* pPacket, Player* player) ;
	static void executeVampire(CGTradeAddItem* pPacket, Player* player) ;
	static void executeOusters(CGTradeAddItem* pPacket, Player* player) ;
	static void makeGCTradeAddItemPacket(GCTradeAddItem* pPacket, ObjectID_t Sender, Item* pItem, CoordInven_t X, CoordInven_t Y) ;
	static void executeError(CGTradeAddItem* pPacket, Player* player, BYTE ErrorCode) ;
};

#endif
