//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyOK.h 
// Written By  : 김성민
// Description : 
// 플레이어가 상점 NPC에게 물건 구입을 요청했을 때, 제대로
// 인증이 되면 이 패킷이 플레이어에게 날아간다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_BUY_OK_H__
#define __GC_SHOP_BUY_OK_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyOK;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyOK : public Packet 
{
public:
	GCShopBuyOK() throw();
	virtual ~GCShopBuyOK() throw();
	
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_BUY_OK; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID +  // NPC
			szShopVersion +  // shop Version
			szObjectID +     // item OID
			szBYTE +         // item class
			szItemType +     // item type
			szBYTE + m_OptionType.size() +   // item option type
			szDurability +   // item durability
			szItemNum +      // number of item
			szSilver +       // silver coating amount
			szGrade +
			szEnchantLevel + // enchant level
			szPrice;         // item price
	}
	string getPacketName() const throw() { return "GCShopBuyOK"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(const ShopVersion_t ver) throw() { m_Version = ver;}

	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID;}
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id;}

	BYTE getItemClass() const throw() { return m_ItemClass;}
	void setItemClass(BYTE IClass) throw() { m_ItemClass = IClass;}

	ItemType_t getItemType() const throw() { return m_ItemType;}
	void setItemType(ItemType_t type) throw() { m_ItemType = type;}
	
	int getOptionTypeSize() const throw() { return m_OptionType.size();}
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t type) throw() { m_OptionType.push_back( type ); }
	void setOptionType(const list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	Durability_t getDurability() const throw() { return m_Durability;}
	void setDurability(Durability_t dur) throw() { m_Durability = dur;}

	ItemNum_t getItemNum(void) const throw() { return m_ItemNum;}
	void setItemNum(ItemNum_t num) throw() { m_ItemNum = num;}

	Silver_t getSilver(void) const throw() { return m_Silver; }
	void setSilver(Silver_t silver) throw() { m_Silver = silver; }

	Grade_t getGrade(void) const throw() { return m_Grade; }
	void setGrade(Grade_t silver) throw() { m_Grade = silver; }

	EnchantLevel_t getEnchantLevel(void) const throw() { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }
	
	Price_t getPrice() const throw() { return m_Price;}
	void setPrice(Price_t price) { m_Price = price;}

private:
	ObjectID_t     		m_ObjectID;     // NPC's object id
	ShopVersion_t  		m_Version;      // 상점 버젼
	ObjectID_t     		m_ItemObjectID; // 플레이어가 산 아이템의 OID
	BYTE           		m_ItemClass;    // 플레이어가 산 아이템의 class
	ItemType_t     		m_ItemType;     // 플레이어가 산 아이템의 type
	list<OptionType_t>  m_OptionType;   // 플레이어가 산 아이템의 option type
	Durability_t   		m_Durability;   // 플레이어가 산 아이템의 durability
	ItemNum_t      		m_ItemNum;      // 플레이어가 산 아이템의 item num
	Silver_t       		m_Silver;       // 플레이어가 산 아이템의 silver coating amount
	Grade_t       		m_Grade;       // 플레이어가 산 아이템의 silver coating amount
	EnchantLevel_t 		m_EnchantLevel; // 플레이어가 산 아이템의 enchant level
	Price_t        		m_Price;        // 플레이어가 현재 돈

};


//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyOKFactory;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyOKFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCShopBuyOK(); }
	string getPacketName() const throw() { return "GCShopBuyOK"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_BUY_OK; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID +  // NPC OID
			szShopVersion +  // shop version
			szObjectID +     // item OID
			szBYTE +         // item class
			szItemType +     // item type
			szBYTE + 255 +   // item option type
			szDurability +   // item durablility
			szItemNum +      // number of item
			szSilver +       // silver coating amount
			szGrade +
			szEnchantLevel + // enchant level
			szPrice;         // item price
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyOKHandler;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyOKHandler 
{
public:
	static void execute(GCShopBuyOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
