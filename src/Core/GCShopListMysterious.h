//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopListMysterious.h 
// Written By  : 김성민
// Description : 
// 플레이어가 가진 상점 버전이 서버에 있는 것과 다를 경우,
// 플레이어는 서버에 상점에 있는 상품 목록을 요구하게 된다.
// 이 패킷은 그 때 플레이어에게 전달하게 되는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_LIST_MYSTERIOUS_H__
#define __GC_SHOP_LIST_MYSTERIOUS_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// buffer structure
//////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	bool       bExist;
	BYTE       itemClass;
	ItemType_t itemType;

} SHOPLISTITEM_MYSTERIOUS;


//////////////////////////////////////////////////////////////////////////////
// class GCShopListMysterious;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCShopListMysterious : public Packet 
{
public:
	GCShopListMysterious() ;
	virtual ~GCShopListMysterious() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCShopListMysterious"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void) const  { return m_Version;}
	void setShopVersion(ShopVersion_t ver)  { m_Version = ver;}
	
	ShopRackType_t getShopType(void) const  { return m_RackType;}
	void setShopType(const ShopRackType_t type) { m_RackType = type;}
	
	SHOPLISTITEM_MYSTERIOUS getShopItem(BYTE index) const ;
	void setShopItem(BYTE index, const Item* pItem) ;

	MarketCond_t getMarketCondBuy(void) const  { return m_MarketCondBuy;}
	MarketCond_t getMarketCondSell(void) const  { return m_MarketCondSell;}
	void setMarketCondBuy(MarketCond_t cond)  { m_MarketCondBuy = cond;}
	void setMarketCondSell(MarketCond_t cond)  { m_MarketCondSell = cond;}
	
private:
	ObjectID_t              m_ObjectID;                     // NPC's object id
	ShopVersion_t           m_Version;                      // Shop version
	ShopRackType_t          m_RackType;                     // rack type
	SHOPLISTITEM_MYSTERIOUS m_pBuffer[SHOP_RACK_INDEX_MAX]; // buffer for i/o
	MarketCond_t            m_MarketCondBuy;                // 시장 시세
	MarketCond_t            m_MarketCondSell;

};

//////////////////////////////////////////////////////////////////////////////
// class GCShopListMysteriousFactory;
//////////////////////////////////////////////////////////////////////////////

class GCShopListMysteriousFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCShopListMysterious(); }
	string getPacketName() const  { return "GCShopListMysterious"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketMaxSize() const  
	{ 
		PacketSize_t unit_size = szBYTE + szItemType;
		PacketSize_t rValue    = 0; 

		rValue += szObjectID;                    // NPC ID
		rValue += szShopVersion;                 // shop version
		rValue += szShopRackType;                // shop rack type
		rValue += szBYTE;                        // total number of item
		rValue += unit_size*SHOP_RACK_INDEX_MAX; // actual item info
		rValue += szMarketCond*2;                // market condition

		return rValue;
	}
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopListMysteriousHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopListMysteriousHandler 
{
public:
	static void execute(GCShopListMysterious* pPacket, Player* pPlayer) ;
};

#endif
