#ifndef __LUA_SELECT_ITEM_H__
#define __LUA_SELECT_ITEM_H__

#include "LuaScript.h"
#include "Item.h"

class LuaSelectItem : public LuaScript {
public :
	LuaSelectItem(LuaState* pState);

	virtual int		executeFile(const string& filename) throw (Error);

	Item::ItemClass	getItemClass() const	{ return m_ItemClass; }
	ItemType_t		getItemType() const		{ return m_ItemType; }
	OptionType_t	getOptionType() const	{ return m_OptionType; }
	OptionType_t	getOptionType2() const	{ return m_OptionType2; }

protected :
	Item::ItemClass		m_ItemClass;
	ItemType_t			m_ItemType;
	OptionType_t		m_OptionType;
	OptionType_t		m_OptionType2;
};

#endif

