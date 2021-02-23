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
	GCCreateItem() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize() const throw() 
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
	string getPacketName() const throw() { return "GCCreateItem"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	BYTE getItemClass() const throw() { return m_ItemClass; }
	void setItemClass(BYTE ItemClass) throw() { m_ItemClass = ItemClass; }

	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	Durability_t getDurability() const throw() { return m_Durability; }
	void setDurability(Durability_t Durability) throw() { m_Durability = Durability; }

	Silver_t getSilver() const throw() { return m_Silver; }
	void setSilver(Silver_t silver) throw() { m_Silver = silver; }

	Grade_t getGrade() const throw() { return m_Grade; }
	void setGrade(Grade_t silver) throw() { m_Grade = silver; }

	EnchantLevel_t getEnchantLevel() const throw() { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	ItemNum_t getItemNum() const throw() { return m_ItemNum; }
	void setItemNum(ItemNum_t num) throw() { m_ItemNum = num; }

	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

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
	Packet* createPacket() throw() { return new GCCreateItem(); }
	string getPacketName() const throw() { return "GCCreateItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(GCCreateItem* pPacket, Player* pPlayer) throw(Error);

};

#endif
