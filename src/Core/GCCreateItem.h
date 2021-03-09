//////////////////////////////////////////////////////////////////////////////
// Filename    : GCCreateItem.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_CREATE_ITEM_H__
#define __GC_CREATE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCCreateItem;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItem : public Packet 
{
public:
	GCCreateItem() ;
    ~GCCreateItem() {};

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + m_OptionType.size() +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +       // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven;    // 아이템 Y 좌표
	}
	string getPacketName() const  { return "GCCreateItem"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	BYTE getItemClass() const  { return m_ItemClass; }
	void setItemClass(BYTE ItemClass)  { m_ItemClass = ItemClass; }

	ItemType_t getItemType() const  { return m_ItemType; }
	void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	int getOptionTypeSize() const  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const  { return m_OptionType; }
	OptionType_t popOptionType() 
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back(OptionType); }
	void setOptionType(const list<OptionType_t>& OptionTypes)  { m_OptionType = OptionTypes; }

	Durability_t getDurability() const  { return m_Durability; }
	void setDurability(Durability_t Durability)  { m_Durability = Durability; }

	Silver_t getSilver() const  { return m_Silver; }
	void setSilver(Silver_t silver)  { m_Silver = silver; }

	Grade_t getGrade() const  { return m_Grade; }
	void setGrade(Grade_t silver)  { m_Grade = silver; }

	EnchantLevel_t getEnchantLevel() const  { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

	ItemNum_t getItemNum() const  { return m_ItemNum; }
	void setItemNum(ItemNum_t num)  { m_ItemNum = num; }

	CoordInven_t getInvenX() const  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY)  { m_InvenY = InvenY; }

private:
	ObjectID_t     		m_ObjectID;     // 오브젝트 ID
	BYTE           		m_ItemClass;    // 아이템 클래스
	ItemType_t     		m_ItemType;     // 아이템 타입
	list<OptionType_t>  m_OptionType;   // 옵션 타입
	Durability_t   		m_Durability;   // 내구성
	Silver_t       		m_Silver;       // 은 도금량
	Grade_t       		m_Grade;       // 아이템 등급
	EnchantLevel_t 		m_EnchantLevel; // 인챈트 레벨
	ItemNum_t      		m_ItemNum;      // 아이템의 숫자
	CoordInven_t   		m_InvenX;       // 인벤토리 X 좌표
	CoordInven_t   		m_InvenY;       // 인벤토리 Y 좌표
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCCreateItem(); }
	string getPacketName() const  { return "GCCreateItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + 255 +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +       // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven;    // 아이템 Y 좌표
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemHandler 
{
public:
	static void execute(GCCreateItem* pPacket, Player* pPlayer) ;

};

#endif
