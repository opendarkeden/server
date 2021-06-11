#include "LuaScript.h"

void
LuaScript::clear()
{
	lua_settop(m_pState->getState(), 0);
}
