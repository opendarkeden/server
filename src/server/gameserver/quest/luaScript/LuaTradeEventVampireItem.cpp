#include "LuaTradeEventVampireItem.h"

LuaTradeEventVampireItem::LuaTradeEventVampireItem(LuaState* pState) 
: LuaSelectItem(pState) 
{
	m_Level = 0;
}

void
LuaTradeEventVampireItem::prepare()
	
{
	__BEGIN_TRY

	lua_pushnumber( m_pState->getState(), m_Level );
	lua_setglobal( m_pState->getState(), "Level" );

	__END_CATCH
}
