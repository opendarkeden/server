# ============================================================================
# LuaScript library (quest scripting helpers)
# ============================================================================

set(LUASCRIPT_SOURCES
    LuaState.cpp
    LuaScript.cpp
    LuaSelectItem.cpp
    LuaTradeEventSlayerItem.cpp
    LuaTradeEventVampireItem.cpp
)

add_library(LuaScript STATIC ${LUASCRIPT_SOURCES})

# Keep same macro expectations as other game-server side code
target_compile_definitions(LuaScript PRIVATE __GAME_SERVER__)

target_include_directories(LuaScript PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/quest
)
