////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_REMOVE_ITEM_H__
#define __CG_TRADE_REMOVE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketSize() const throw() { return szObjectID*2; }
	string getPacketName() const throw() { return "CGTradeRemoveItem"; }
	string toString() const throw();
	
public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 ObjectID
	ObjectID_t m_ItemObjectID;   // 교환 리스트에 추가할 아이템의 OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTradeRemoveItem(); }
	string getPacketName() const throw() { return "CGTradeRemoveItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID*2; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItemHandler 
{
public:
	static void execute(CGTradeRemoveItem* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeSlayer(CGTradeRemoveItem* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeVampire(CGTradeRemoveItem* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOusters(CGTradeRemoveItem* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeError(CGTradeRemoveItem* pPacket, Player* player, BYTE ErrorCode) throw(ProtocolException, Error);
};

#endif
