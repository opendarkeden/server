//--------------------------------------------------------------------------------
// by sigi. 2002.12.12
//--------------------------------------------------------------------------------

#ifndef __LUA_STATE_H__
#define __LUA_STATE_H__

#include "Types.h"
#include "Exception.h"

extern "C"
{
#if defined(__APPLE__)
	#include <luajit-2.1/lua.h>
	#include <luajit-2.1/lualib.h>
	#include <luajit-2.1/lauxlib.h>
#else
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
#endif
}


class LuaState {
public :
	static const int defaultStateSize = 100;

public :
	LuaState();
	virtual ~LuaState();

	// LuaState�� ���ؼ� ���� �ѹ��� init���ָ� �ȴ�.
	virtual void	init(int stackSize=defaultStateSize);
	virtual void	release();

	lua_State* 		getState() const	{ return m_pState; }
	int				dofile(const string& filename);


	static bool		isError(int result)	{ return result!=0; }
	static const string& getErrorToString(int result);
	static void		logError(int result);

	void 			randomseed();

protected :
	void 	open(int stackSize=defaultStateSize);
	void 	baselibopen();
	void 	mathlibopen();
	void	strlibopen();
	void 	iolibopen();
	void 	close();


protected :
	lua_State* m_pState;
};

#endif

