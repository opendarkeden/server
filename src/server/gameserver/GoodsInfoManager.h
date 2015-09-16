//////////////////////////////////////////////////////////////////////////////
// Filename    : GoodsInfo.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GOODS_INFO_H__
#define __GOODS_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"

#include <list>
#include <map>

//////////////////////////////////////////////////////////////////////////////
// Class GoodsInfo
//////////////////////////////////////////////////////////////////////////////

class GoodsInfo 
{
public:
	GoodsInfo();
	~GoodsInfo();

public:
	DWORD getID() const { return m_ID; }
	void setID(DWORD id) { m_ID = id; }

	string getName() const { return m_Name ; }
	void setName(string name) { m_Name = name ; }

	Item::ItemClass getItemClass() const { return m_ItemClass; }
	void setItemClass(Item::ItemClass itemClass ) { m_ItemClass = itemClass; }

	ItemType_t getItemType() const { return m_ItemType; }
	void setItemType(ItemType_t itemType ) { m_ItemType = itemType; }

	Grade_t getGrade() const { return m_Grade; }
	void setGrade(Grade_t grade ) { m_Grade = grade; }

	const list<OptionType_t>& getOptionTypeList() const { return m_OptionTypes; }
	void setOptionTypeList(const list<OptionType_t>& optionTypes ) { m_OptionTypes = optionTypes; }

	int getNum() const { return m_Num; }
	void setNum(int num ) { m_Num = num; }

	bool isTimeLimit() const { return m_bTimeLimit; }
	void setTimeLimit(bool bTimeLimit = true ) { m_bTimeLimit = bTimeLimit; }

	int getHour() const { return m_Hour; }
	void setHour(int hour ) { m_Hour = hour; }

	// toString
	string toString() const ;

private:
	DWORD					m_ID;			// Type
	string					m_Name;			// Name
	Item::ItemClass			m_ItemClass;	// ItemClass
	ItemType_t				m_ItemType;		// ItemType
	Grade_t					m_Grade;		// Grade
	list<OptionType_t>		m_OptionTypes;	// OptionType list
	int 					m_Num;
	bool					m_bTimeLimit;	// 시간제한 아이템인가?
	int						m_Hour;			// 사용 제한 시간
};

//////////////////////////////////////////////////////////////////////////////
// Class GoodsInfoManager
//////////////////////////////////////////////////////////////////////////////

class GoodsInfoManager 
{
public:
	typedef map<DWORD, GoodsInfo*>			HashMapGoodsInfo;
	typedef HashMapGoodsInfo::iterator			HashMapGoodsInfoItr;
	typedef HashMapGoodsInfo::const_iterator	HashMapGoodsInfoConstItr;

public:
	GoodsInfoManager() throw();
	~GoodsInfoManager() throw();

public:

	// initialize Manager
	void init() throw(Error);

	// void load() throw();
	void load() throw(Error);
	
	// clear list
	void clear() throw();

	// add GoodsInfo
	void addGoodsInfo(GoodsInfo* pGoodsInfo) throw(DuplicatedException, Error);

	// get GoodsInfo
	GoodsInfo* getGoodsInfo(DWORD id ) const throw();

	// toString for Debug
	string toString() const throw();

private:
	HashMapGoodsInfo		m_GoodsInfos;

};

// Global Variable Definition
extern GoodsInfoManager* g_pGoodsInfoManager;

#endif	// __SKILL_INFO_MANAGER_H__
