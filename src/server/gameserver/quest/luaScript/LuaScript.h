// LuaScript.h

#ifndef __LUA_SCRIPT_H__
#define __LUA_SCRIPT_H__

#include "LuaState.h"

class LuaScript
{
public :
	LuaScript(LuaState* pState) : m_pState(pState) {}
	virtual ~LuaScript() { m_pState = NULL; }
	
	virtual void	prepare() throw (Error) = 0;
	virtual int		executeFile(const string& filename) throw (Error) = 0;

	virtual void 	clear();

protected :
	LuaState* m_pState;
};

#endif
