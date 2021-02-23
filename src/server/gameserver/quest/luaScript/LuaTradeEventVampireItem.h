#ifndef __LUA_TRADE_EVENT_VAMPIRE_ITEM_H__
#define __LUA_TRADE_EVENT_VAMPIRE_ITEM_H__

#include "LuaSelectItem.h"

class LuaTradeEventVampireItem : public LuaSelectItem {
public :
	LuaTradeEventVampireItem(LuaState* pState);

	virtual void	prepare() throw (Error);

	int		getLevel() const	{ return m_Level; }
	void	setLevel(int sum) 	{ m_Level = sum; }

protected :
	int		m_Level;
};

#endif

