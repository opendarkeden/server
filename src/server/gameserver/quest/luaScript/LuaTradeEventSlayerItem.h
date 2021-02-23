#ifndef __LUA_TRADE_EVENT_SLAYER_ITEM_H__
#define __LUA_TRADE_EVENT_SLAYER_ITEM_H__

#include "LuaSelectItem.h"

class LuaTradeEventSlayerItem : public LuaSelectItem {
public :
	LuaTradeEventSlayerItem(LuaState* pState);

	virtual void	prepare() throw (Error);

	Attr_t	getSum() const		{ return m_SUM; }
	void	setSum(Attr_t sum) 	{ m_SUM = sum; }

protected :
	Attr_t	m_SUM;
};

#endif

