# ============================================================================
# Database 库 - 同一份源码编译多个版本（关键：不同宏定义）
# ============================================================================

set(DATABASE_SOURCES
    Connection.cpp
    Statement.cpp
    Result.cpp
    DatabaseManager.cpp
)

# ============================================================================
# 通用 Database 库（无特定服务器宏）
# ============================================================================
add_library(Database STATIC ${DATABASE_SOURCES})
target_include_directories(Database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================================
# GameServer 专用 Database 库
# 使用 OBJECT 库避免重复编译，然后用不同宏重新编译
# ============================================================================
add_library(GameServerDatabase STATIC ${DATABASE_SOURCES})
target_compile_definitions(GameServerDatabase PRIVATE __GAME_SERVER__)
target_include_directories(GameServerDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================================
# LoginServer 专用 Database 库
# ============================================================================
add_library(LoginServerDatabase STATIC ${DATABASE_SOURCES})
target_compile_definitions(LoginServerDatabase PRIVATE __LOGIN_SERVER__)
target_include_directories(LoginServerDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================================
# SharedServer 专用 Database 库
# ============================================================================
add_library(SharedServerDatabase STATIC ${DATABASE_SOURCES})
target_compile_definitions(SharedServerDatabase PRIVATE __SHARED_SERVER__)
target_include_directories(SharedServerDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================================
# UpdateServer 专用 Database 库
# ============================================================================
add_library(UpdateServerDatabase STATIC ${DATABASE_SOURCES})
target_compile_definitions(UpdateServerDatabase PRIVATE __UPDATE_SERVER__)
target_include_directories(UpdateServerDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
