//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_MINE_INFO_H__
#define __ITEM_MINE_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class ItemMineInfo 
{
public:
	ItemMineInfo();
	~ItemMineInfo();

public:
	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	ItemClass_t getItemClass() const { return m_ItemClass; }
	void setItemClass( ItemClass_t itemClass ) { m_ItemClass = itemClass; }

	ItemType_t getItemType() const { return m_ItemType; }
	void setItemType( ItemType_t itemType ) { m_ItemType = itemType; }

	const list<OptionType_t>& getItemOptions() const { return m_ItemOptions; }
	void setItemOptions( const list<OptionType_t>& itemOptions ) { m_ItemOptions = itemOptions; }

	Item* getItem();

	string toString() const;

private:
	int					m_ID;			// ItemMineInfo ID
	ItemClass_t			m_ItemClass;	// Item Class
	ItemType_t			m_ItemType;		// Item Type
	list<OptionType_t>	m_ItemOptions;	// Item Options
};

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfoManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, ItemMineInfo*>			HashMapItemMineInfo;
typedef HashMapItemMineInfo::iterator			HashMapItemMineInfoItor;
typedef HashMapItemMineInfo::const_iterator		HashMapItemMineInfoConstItor;

class ItemMineInfoManager 
{
public:
	ItemMineInfoManager();
	~ItemMineInfoManager();

public:

	// void load() throw();
	void load() throw(Error);
	
	// get ItemMineInfo
	ItemMineInfo* getItemMineInfo(int id) const;

	// add ItemMineInfo
	void addItemMineInfo(ItemMineInfo* pItemMineInfo) throw(DuplicatedException, Error);

	Item* getRandomItem(int minID, int maxID);

	// toString for Debug
	string toString() const;

private:
	HashMapItemMineInfo m_ItemMineInfos;
};

// Global Variable Definition
extern ItemMineInfoManager* g_pItemMineInfoManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
