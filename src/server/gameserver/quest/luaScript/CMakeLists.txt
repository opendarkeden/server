
SET(LIBLUASCRIPT_SRC
	LuaState.cpp
	LuaScript.cpp
	LuaSelectItem.cpp
	LuaTradeEventSlayerItem.cpp
	LuaTradeEventVampireItem.cpp)
ADD_LIBRARY(LuaScript STATIC ${LIBLUASCRIPT_SRC})