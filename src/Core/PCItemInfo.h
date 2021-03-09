//////////////////////////////////////////////////////////////////////////////
// Filename    : PCItemInfo.h
// Written By  : elca
// Description :
// 아이템 하나에 대한 정보를 가지고 있는 패킷이다.
// 좌표라든지, 이펙트에 관한 정보는 가지고 있지 않다.
// 인벤토리와 관련된 여러 군데에서 상속되어 사용된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_ITEM_INFO_H__
#define __SLAYER_ITEM_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "SubItemInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class PCItemInfo
//////////////////////////////////////////////////////////////////////////////

class PCItemInfo 
{
public:
	PCItemInfo() ;
	virtual ~PCItemInfo() ;

public:
	void read (SocketInputStream & iStream) ;
	void write (SocketOutputStream & oStream) const ;

	string toString() const ;

public:
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID() const  { return m_ObjectID; }

	void setItemClass (BYTE IClass)  { m_IClass = IClass; }
	BYTE getItemClass () const  { return m_IClass; }

	void setItemType (ItemType_t ItemType)  { m_ItemType = ItemType; }
	ItemType_t getItemType() const  { return m_ItemType; }

	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionType)  { m_OptionType = OptionType; }
	int getOptionTypeSize() const  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const  { return m_OptionType; }
	OptionType_t popOptionType()  
	{ 
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front(); 
		m_OptionType.pop_front(); 
		return optionType; 
	}

	void setSilver(Silver_t amount)  { m_Silver = amount; }
	Silver_t getSilver() const  { return m_Silver; }

	void setGrade(Grade_t grade)  { m_Grade = grade; }
	Grade_t getGrade() const  { return m_Grade; }

	void setDurability(Durability_t Durability)  { m_Durability = Durability; }
	Durability_t getDurability() const  { return m_Durability; }

	void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }
	EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }

	void setItemNum(ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum() const  { return m_ItemNum; }

	void setMainColor(WORD MainColor)  { m_MainColor = MainColor; }
	WORD getMainColor() const  { return m_MainColor; }

	BYTE getListNum() const  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	void addListElement(SubItemInfo* pSubItemInfo)  
	{ 
		m_SubItemInfoList.push_back(pSubItemInfo); 
		m_ListNum++;
	}

	void clearList()  { m_SubItemInfoList.clear(); m_ListNum = 0; }

	SubItemInfo* popFrontListElement()  
	{ 
		SubItemInfo* TempSubItemInfo = m_SubItemInfoList.front(); 
		m_SubItemInfoList.pop_front(); 
		return TempSubItemInfo; 
	}

public:
	uint getSize() const 
	{
		return szObjectID +
			szBYTE +
			szItemType + 
			szBYTE + m_OptionType.size() +
			szDurability +
			szSilver + 
			szGrade +
			szEnchantLevel +
			szItemNum +
			szWORD +
			szBYTE +
			SubItemInfo::getMaxSize()*m_ListNum;
	}

	static uint getMaxSize() 
	{
		return szObjectID +
			szBYTE +
			szItemType + 
			szBYTE + 255 +
			szDurability +
			szSilver + 
			szGrade +
			szEnchantLevel +
			szItemNum +
			szWORD +
			szBYTE +
			SubItemInfo::getMaxSize()*8;
	}


protected:
	ObjectID_t         m_ObjectID;         // item object id
	BYTE               m_IClass;           // item class
	ItemType_t         m_ItemType;         // item type
	list<OptionType_t> m_OptionType;       // item option type
	Durability_t       m_Durability;       // item durability
	Silver_t           m_Silver;           // silver coating amount
	Grade_t				m_Grade;			// 아이템 등급
	EnchantLevel_t     m_EnchantLevel;     // item enchant level
	ItemNum_t          m_ItemNum;          // number of item
	WORD               m_MainColor;        // item color
	BYTE               m_ListNum;          // number of sub item
	list<SubItemInfo*> m_SubItemInfoList;  // actual sub item info

};

#endif
