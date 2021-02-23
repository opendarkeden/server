//--------------------------------------------------------------------------------
// by sigi. 2002.12.12
//--------------------------------------------------------------------------------

#ifndef __LUA_STATE_H__
#define __LUA_STATE_H__

#include "Types.h"
#include "Exception.h"

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
}


class LuaState {
public :
	static const int defaultStateSize = 100;

public :
	LuaState();
	virtual ~LuaState();

	// LuaState에 대해서 최초 한번만 init해주면 된다.
	virtual void	init(int stackSize=defaultStateSize);
	virtual void	release();

	lua_State* 		getState() const	{ return m_pState; }
	int				dofile(const string& filename) throw (Error);


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

