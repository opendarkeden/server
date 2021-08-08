//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopList.h 
// Written By  : �輺��
// Description :
// �÷��̾ ���� ���� ������ ������ �ִ� �Ͱ� �ٸ� ���,
// �÷��̾�� ������ ������ �ִ� ��ǰ ����� �䱸�ϰ� �ȴ�.
// �� ��Ŷ�� �� �� �÷��̾�� �����ϰ� �Ǵ� ��Ŷ�̴�.
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
	GCShopList() ;
	virtual ~GCShopList() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCShopList"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void) const  { return m_Version;}
	void setShopVersion(ShopVersion_t ver)  { m_Version = ver;}
	
	ShopRackType_t getShopType(void) const  { return m_RackType; }
	void setShopType(const ShopRackType_t type);

	MarketCond_t getMarketCondBuy(void) const  { return m_MarketCondBuy;}
	void setMarketCondBuy(MarketCond_t cond)  { m_MarketCondBuy = cond;}

	MarketCond_t getMarketCondSell(void) const  { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond)  { m_MarketCondSell = cond;}
	
	SHOPLISTITEM getShopItem(BYTE index) const ;

#ifndef __GAME_CLIENT__
	void setShopItem(BYTE index, const Item* pItem) ;
#endif

	BYTE getNPCShopType(void) const { return m_ShopType; }
	void setNPCShopType(BYTE type) { m_ShopType = type; }

private:
	ObjectID_t     m_ObjectID;                      // NPC's object id
	ShopVersion_t  m_Version;                       // Shop version
	ShopRackType_t m_RackType;                      // rack type
	SHOPLISTITEM   m_pBuffer[SHOP_RACK_INDEX_MAX];  // actual item info
	MarketCond_t   m_MarketCondBuy;                 // ���� �ü�
	MarketCond_t   m_MarketCondSell;                // ���� �ü�
	BYTE           m_ShopType;                      // ������ ���� (�Ϲ� or �̺�Ʈ)
};


//////////////////////////////////////////////////////////////////////////////
// class GCShopListFactory;
//////////////////////////////////////////////////////////////////////////////
class GCShopListFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCShopList(); }
	string getPacketName() const  { return "GCShopList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
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
	static void execute(GCShopList* pPacket, Player* pPlayer) ;

};

#endif
