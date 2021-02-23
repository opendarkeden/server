
//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddStoreItem.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_STORE_ITEM_H__
#define __GC_ADD_STORE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddStoreItem;
//////////////////////////////////////////////////////////////////////////////

class GCAddStoreItem : public Packet
{
public:
	GCAddStoreItem() throw() { }
	virtual ~GCAddStoreItem() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_STORE_ITEM; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + m_Item.getSize(); }
	string getPacketName() const throw() { return "GCAddStoreItem"; }
	string toString() const throw();

	ObjectID_t	getOwnerObjectID() const { return m_OwnerObjectID; }
	void		setOwnerObjectID(ObjectID_t oid) { m_OwnerObjectID = oid; }

	BYTE		getIndex() const { return m_Index; }
	void		setIndex(BYTE index) { m_Index = index; }

	StoreItemInfo&	getItem() { return m_Item; }

private:
	ObjectID_t	m_OwnerObjectID;
	BYTE		m_Index;
	StoreItemInfo	m_Item;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddStoreItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddStoreItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddStoreItem(); }
	string getPacketName() const throw() { return "GCAddStoreItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_STORE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szObjectID + szBYTE + StoreItemInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddStoreItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddStoreItemHandler 
{
public:
	static void execute(GCAddStoreItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
