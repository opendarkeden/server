//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopList.h 
// Written By  : 김성민
// Description :
// 플레이어가 가진 상점 버전이 서버에 있는 것과 다를 경우,
// 플레이어는 서버에 상점에 있는 상품 목록을 요구하게 된다.
// 이 패킷은 그 때 플레이어에게 전달하게 되는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_LIST_H__
#define __GC_SHOP_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <list>

typedef struct _SHOPLISTITEM
{
	bool           		bExist;
	ObjectID_t     		objectID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	list<OptionType_t>  optionType;
	Durability_t   		durability;
	Silver_t       		silver;
	Grade_t       		grade;
	EnchantLevel_t 		enchantLevel;

} SHOPLISTITEM;

//////////////////////////////////////////////////////////////////////////////
// class GCShopList;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCShopList : public Packet 
{
public:
	GCShopList() throw();
	virtual ~GCShopList() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCShopList"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(ShopVersion_t ver) throw() { m_Version = ver;}
	
	ShopRackType_t getShopType(void) const throw() { return m_RackType; }
	void setShopType(const ShopRackType_t type) { m_RackType = type; }

	MarketCond_t getMarketCondBuy(void) const throw() { return m_MarketCondBuy;}
	void setMarketCondBuy(MarketCond_t cond) throw() { m_MarketCondBuy = cond;}

	MarketCond_t getMarketCondSell(void) const throw() { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond) throw() { m_MarketCondSell = cond;}
	
	SHOPLISTITEM getShopItem(BYTE index) const throw();

#ifndef __GAME_CLIENT__
	void setShopItem(BYTE index, const Item* pItem) throw();
#endif

	BYTE getNPCShopType(void) const { return m_ShopType; }
	void setNPCShopType(BYTE type) { m_ShopType = type; }

private:
	ObjectID_t     m_ObjectID;                      // NPC's object id
	ShopVersion_t  m_Version;                       // Shop version
	ShopRackType_t m_RackType;                      // rack type
	SHOPLISTITEM   m_pBuffer[SHOP_RACK_INDEX_MAX];  // actual item info
	MarketCond_t   m_MarketCondBuy;                 // 시장 시세
	MarketCond_t   m_MarketCondSell;                // 시장 시세
	BYTE           m_ShopType;                      // 상점의 종류 (일반 or 이벤트)
};


//////////////////////////////////////////////////////////////////////////////
// class GCShopListFactory;
//////////////////////////////////////////////////////////////////////////////
class GCShopListFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCShopList(); }
	string getPacketName() const throw() { return "GCShopList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t unit = 0;
		unit += szBYTE;         // shop rack index
		unit += szObjectID;     // item object id
		unit += szBYTE;         // item class
		unit += szItemType;     // item type
		unit += szBYTE + 255;   // item option type
		unit += szDurability;   // item durability
		unit += szSilver;       // silver coating amount
		unit += szGrade;
		unit += szEnchantLevel; // enchant level

		return szObjectID +               // NPC ID
		       szShopVersion +            // shop version
		       szShopRackType +           // shop rack type
		       szBYTE +                   // total number of item
		       unit*SHOP_RACK_INDEX_MAX + // all item info
			   szMarketCond*2 +           // market condition
			   szBYTE;                    // shop type
	}

};


//////////////////////////////////////////////////////////////////////////////
// class GCShopListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCShopListHandler 
{
public:
	static void execute(GCShopList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
