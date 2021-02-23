//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherStoreInfo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_STORE_INFO_H__
#define __GC_OTHER_STORE_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCOtherStoreInfo;
//////////////////////////////////////////////////////////////////////////////

class GCOtherStoreInfo : public Packet
{
public:
	GCOtherStoreInfo() throw() { }
	virtual ~GCOtherStoreInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_OTHER_STORE_INFO; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + m_pInfo->getSize(true); }
	string getPacketName() const throw() { return "GCOtherStoreInfo"; }
	string toString() const throw();

public:
	ObjectID_t	getObjectID() const { return m_ObjectID; }
	void		setObjectID(ObjectID_t oid) { m_ObjectID = oid; }

	BYTE		isRequested() const { return m_IsRequested; }
	void		setRequested(BYTE flag) { m_IsRequested = flag; }

	StoreInfo*	getStoreInfo() const { return m_pInfo; }
	void		setStoreInfo(StoreInfo* pInfo ) { m_pInfo = pInfo; }

private:
	ObjectID_t	m_ObjectID;
	BYTE		m_IsRequested;
	StoreInfo*	m_pInfo;
};

//////////////////////////////////////////////////////////////////////////////
// class GCOtherStoreInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCOtherStoreInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCOtherStoreInfo(); }
	string getPacketName() const throw() { return "GCOtherStoreInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_OTHER_STORE_INFO; }
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szObjectID + szBYTE + StoreInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCOtherStoreInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCOtherStoreInfoHandler 
{
public:
	static void execute(GCOtherStoreInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
