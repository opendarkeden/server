//////////////////////////////////////////////////////////////////////////////
// Filename    : ShopTemplate.h
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOPTEMPLATE_H__
#define __SHOPTEMPLATE_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class ShopTemplate
// 상점에서 아이템을 자동으로 생성하기 위해서 DB에서 일정한
// 형식의 틀을 읽어오는데, 그 틀을 캡슐화한 클래스이다.
// 거의 구조체와 비슷한 클래스이며 자체적으로 특별히 하는 일은
// 없고, 그냥 데이터를 임시적으로 저장하는 역할만을 한다.
//////////////////////////////////////////////////////////////////////////////

class ShopTemplate
{

///// Member methods /////
	
public:
	ShopTemplate() throw();
	virtual ~ShopTemplate() throw();

public:
	ShopTemplateID_t getID(void) const throw() { return m_ID; }
	void setID(ShopTemplateID_t id) throw() { m_ID = id; }
	
	ShopRackType_t getShopType(void) const throw() { return m_RackType; }
	void setShopType(const ShopRackType_t type) throw() { m_RackType = type; }

	int getItemClass(void) const throw() { return m_ItemClass; }
	void setItemClass(int iclass) throw() { m_ItemClass = iclass; }
	
	ItemType_t getMinItemType(void) const throw() { return m_MinItemType; }
	void setMinItemType(ItemType_t t) { m_MinItemType = t; }

	ItemType_t getMaxItemType(void) const throw() { return m_MaxItemType; }
	void setMaxItemType(ItemType_t t) { m_MaxItemType = t; }

	uint getMinOptionLevel(void) const throw() { return m_MinOptionLevel; }
	void setMinOptionLevel(uint o) { m_MinOptionLevel = o; }

	uint getMaxOptionLevel(void) const throw() { return m_MaxOptionLevel;}
	void setMaxOptionLevel(uint o) { m_MaxOptionLevel = o; }

	string toString() const throw();


///// Member data /////

private:
	ShopTemplateID_t m_ID;            // DB entry id
	ShopRackType_t   m_RackType;      // rack type(normal, special, ...)
	int              m_ItemClass;     // item class(sword, armor, ...)
	ItemType_t       m_MinItemType;   // item type(1~5 now)
	ItemType_t       m_MaxItemType;   
	uint             m_MinOptionLevel;
	uint             m_MaxOptionLevel;

};

//////////////////////////////////////////////////////////////////////////////
// class ShopTemplateManager
// ShopTemplate 클래스의 해쉬맵을 가지고 있는 클래스이다.
// id를 주면 그에 해당하는 ShopTemplate을 되돌려주는 역할을 한다.
//////////////////////////////////////////////////////////////////////////////

class ShopTemplateManager
{

///// Member methods /////
	
public:
	ShopTemplateManager() throw();
	~ShopTemplateManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

public:
	ShopTemplate* getTemplate(ShopTemplateID_t id) const throw(NoSuchElementException, Error);
	void setTemplate(ShopTemplateID_t id, ShopTemplate* pEntry) throw();

	string toString() const throw();


///// Member data ///// 

private:
	hash_map<ShopTemplateID_t, ShopTemplate*> m_Entries; // hash map of script

};

// global variable declaration
extern ShopTemplateManager* g_pShopTemplateManager;

#endif
