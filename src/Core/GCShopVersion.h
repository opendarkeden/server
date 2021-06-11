//--------------------------------------------------------------------------------
// 
// Filename    : GCShopVersion.h 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_VERSION_H__
#define __GC_SHOP_VERSION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopVersion;
//
//--------------------------------------------------------------------------------

class GCShopVersion : public Packet 
{

public :

	GCShopVersion() ;
	virtual ~GCShopVersion() ;
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_VERSION; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szShopVersion*3 + szMarketCond; }

	// get packet name
	string getPacketName() const  { return "GCShopVersion"; }
	
	// get packet's debug string
	string toString() const ;


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get/set shop version
	ShopVersion_t getVersion(ShopRackType_t type) const 
	{
		if(type >= SHOP_RACK_TYPE_MAX) throw("GCShopVersion::getVersion() : Out of Bound!");
		return m_Version[type];
	}
	
	void setVersion(ShopRackType_t type, ShopVersion_t ver) 
	{
		if(type >= SHOP_RACK_TYPE_MAX) throw("GCShopVersion::setVersion() : Out of Bound!");
		m_Version[type] = ver;
	}

	// get/set market condition sell
	MarketCond_t getMarketCondSell(void) const  { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond)  { m_MarketCondSell = cond;}

private :

	// NPC's object id
	ObjectID_t m_ObjectID;

	// shop version
	ShopVersion_t m_Version[SHOP_RACK_TYPE_MAX];

	MarketCond_t m_MarketCondSell;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionFactory;
//
// Factory for GCShopVersion
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCShopVersion(); }

	// get packet name
	string getPacketName() const  { return "GCShopVersion"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_VERSION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopVersionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szShopVersion*3 + szMarketCond; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopVersion* pPacket, Player* pPlayer) ;

};

#endif
