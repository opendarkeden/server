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
	GCShopListMysterious() throw();
	virtual ~GCShopListMysterious() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCShopListMysterious"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(ShopVersion_t ver) throw() { m_Version = ver;}
	
	ShopRackType_t getShopType(void) const throw() { return m_RackType;}
	void setShopType(const ShopRackType_t type) { m_RackType = type;}
	
	SHOPLISTITEM_MYSTERIOUS getShopItem(BYTE index) const throw();
	void setShopItem(BYTE index, const Item* pItem) throw();

	MarketCond_t getMarketCondBuy(void) const throw() { return m_MarketCondBuy;}
	MarketCond_t getMarketCondSell(void) const throw() { return m_MarketCondSell;}
	void setMarketCondBuy(MarketCond_t cond) throw() { m_MarketCondBuy = cond;}
	void setMarketCondSell(MarketCond_t cond) throw() { m_MarketCondSell = cond;}
	
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
	Packet* createPacket() throw() { return new GCShopListMysterious(); }
	string getPacketName() const throw() { return "GCShopListMysterious"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(GCShopListMysterious* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
