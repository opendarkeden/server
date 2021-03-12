
//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRemoveStoreItem.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_STORE_ITEM_H__
#define __GC_REMOVE_STORE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItem;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItem : public Packet
{
public:
	GCRemoveStoreItem()  { }
	virtual ~GCRemoveStoreItem() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_REMOVE_STORE_ITEM; }
	PacketSize_t getPacketSize() const  { return szObjectID + szBYTE; }
	string getPacketName() const  { return "GCRemoveStoreItem"; }
	string toString() const ;

	ObjectID_t	getOwnerObjectID() const { return m_OwnerObjectID; }
	void		setOwnerObjectID(ObjectID_t oid) { m_OwnerObjectID = oid; }

	BYTE		getIndex() const { return m_Index; }
	void		setIndex(BYTE index) { m_Index = index; }

private:
	ObjectID_t	m_OwnerObjectID;
	BYTE		m_Index;
};

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCRemoveStoreItem(); }
	string getPacketName() const  { return "GCRemoveStoreItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_REMOVE_STORE_ITEM; }
	PacketSize_t getPacketMaxSize() const 
	{
		return szObjectID + szBYTE;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItemHandler 
{
public:
	static void execute(GCRemoveStoreItem* pPacket, Player* pPlayer) ;
};

#endif
