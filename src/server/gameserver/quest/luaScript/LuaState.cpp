//--------------------------------------------------------------------------------
// LuaState.cpp
//--------------------------------------------------------------------------------
#include "LuaState.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


//--------------------------------------------------------------------------------
// constructor / destructor
//--------------------------------------------------------------------------------
LuaState::LuaState()
: m_pState(NULL)
{
}

LuaState::~LuaState()
{
	release();
}

//--------------------------------------------------------------------------------
// init
//--------------------------------------------------------------------------------
void
LuaState::init(int stackSize)
{
	open(stackSize);

	// 모든 lib를 load한다.. 
	baselibopen();
	mathlibopen();
	strlibopen();
	iolibopen();

	randomseed();
}


//--------------------------------------------------------------------------------
// release
//--------------------------------------------------------------------------------
void
LuaState::release()
{
	if (m_pState!=NULL)
	{
		lua_close(m_pState);
	}
	m_pState = NULL;
}

//--------------------------------------------------------------------------------
// dofile
//--------------------------------------------------------------------------------
int
LuaState::dofile(const string& filename)
	
{
	__BEGIN_TRY

	return lua_dofile(m_pState, filename.c_str());

	__END_CATCH
}

//--------------------------------------------------------------------------------
// randomseed
//--------------------------------------------------------------------------------
void
LuaState::randomseed()
{
	char str[80];
	srand((unsigned int)time(NULL));
	sprintf(str,"randomseed(%d)", rand()%10000);
	lua_dostring(m_pState, str);
}

//--------------------------------------------------------------------------------
// open
//--------------------------------------------------------------------------------
void
LuaState::open(int stackSize)
{
	release();
	m_pState = lua_open(stackSize);
}

//--------------------------------------------------------------------------------
// close
//--------------------------------------------------------------------------------
void
LuaState::close()
{
	if (m_pState!=NULL)
	{
		lua_close(m_pState);
	}
}

//--------------------------------------------------------------------------------
// baselibopen
//--------------------------------------------------------------------------------
void
LuaState::baselibopen()
{
	lua_baselibopen(m_pState);
}

//--------------------------------------------------------------------------------
// mathlibopen
//--------------------------------------------------------------------------------
void
LuaState::mathlibopen()
{
	lua_mathlibopen(m_pState);
}

//--------------------------------------------------------------------------------
// strlibopen
//--------------------------------------------------------------------------------
void
LuaState::strlibopen()
{
	lua_strlibopen(m_pState);
}

//--------------------------------------------------------------------------------
// iolibopen
//--------------------------------------------------------------------------------
void
LuaState::iolibopen()
{
	lua_iolibopen(m_pState);
}

//--------------------------------------------------------------------------------
// getError to String
//--------------------------------------------------------------------------------
const string& 
LuaState::getErrorToString(int result)
{
	switch (result)
	{
		case LUA_ERRRUN :
		{
			static string e =  "error while running the chunk";
			return e;
		}
		break;

		case LUA_ERRSYNTAX :
		{
			static string e = "syntax error during pre-compilation";
			return e;
		}
		break;

		case LUA_ERRMEM :
		{
			static string e = "memory allocation error";
			return e;
		}
		break;

		case LUA_ERRERR :
		{
			static string e = "error while running _ERRORMESSAGE.";
			return e;
		}
		break;

		case LUA_ERRFILE :
		{
			static string e = "error opening the file.";
			return e;
		}
		break;
	}

	static string e = "unknown error";
	return e;
}

//--------------------------------------------------------------------------------
// log Error
//--------------------------------------------------------------------------------
void
LuaState::logError(int result)
{
	if (isError(result))
	{
		filelog("luaError.log", "%s", getErrorToString(result).c_str());
	}
}

