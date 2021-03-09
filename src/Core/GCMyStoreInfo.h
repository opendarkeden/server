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
	GCMyStoreInfo()  : m_OpenUI(1) { }
	virtual ~GCMyStoreInfo() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_MY_STORE_INFO; }
	PacketSize_t getPacketSize() const  { return szBYTE + m_pInfo->getSize(false); }
	string getPacketName() const  { return "GCMyStoreInfo"; }
	string toString() const ;

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
	Packet* createPacket()  { return new GCMyStoreInfo(); }
	string getPacketName() const  { return "GCMyStoreInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MY_STORE_INFO; }
	PacketSize_t getPacketMaxSize() const 
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
	static void execute(GCMyStoreInfo* pPacket, Player* pPlayer) ;
};

#endif
