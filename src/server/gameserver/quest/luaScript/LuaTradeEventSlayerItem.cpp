#include "LuaTradeEventSlayerItem.h"

LuaTradeEventSlayerItem::LuaTradeEventSlayerItem(LuaState* pState) 
: LuaSelectItem(pState) 
{
	m_SUM = 0;
}

void
LuaTradeEventSlayerItem::prepare()
	
{
	__BEGIN_TRY

	lua_pushnumber( m_pState->getState(), m_SUM );
	lua_setglobal( m_pState->getState(), "SUM" );

	__END_CATCH
}
