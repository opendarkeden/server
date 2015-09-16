//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMyStoreInfo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MY_STORE_INFO_H__
#define __GC_MY_STORE_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCMyStoreInfo;
//////////////////////////////////////////////////////////////////////////////

class GCMyStoreInfo : public Packet
{
public:
	GCMyStoreInfo() throw() : m_OpenUI(1) { }
	virtual ~GCMyStoreInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_MY_STORE_INFO; }
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_pInfo->getSize(false); }
	string getPacketName() const throw() { return "GCMyStoreInfo"; }
	string toString() const throw();

public:
	BYTE		getOpenUI() const { return m_OpenUI; }
	void		setOpenUI(BYTE ui) { m_OpenUI = ui; }

	StoreInfo*	getStoreInfo() const { return m_pInfo; }
	void		setStoreInfo(StoreInfo* pInfo ) { m_pInfo = pInfo; }

private:
	BYTE		m_OpenUI;
	StoreInfo*	m_pInfo;
};

//////////////////////////////////////////////////////////////////////////////
// class GCMyStoreInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCMyStoreInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCMyStoreInfo(); }
	string getPacketName() const throw() { return "GCMyStoreInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MY_STORE_INFO; }
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szBYTE + StoreInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCMyStoreInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCMyStoreInfoHandler 
{
public:
	static void execute(GCMyStoreInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
