cmake_minimum_required(VERSION 3.16)
project(DarkEden VERSION 1.0 LANGUAGES CXX)

# ============================================================================
# 全局设置
# ============================================================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ============================================================================
# 全局编译选项
# ============================================================================
# 基础宏定义 - 所有目标都需要
add_compile_definitions(__LINUX__ _REENTRANT)

# 警告设置
set(WARNING_FLAGS 
    -Wall
    -Wno-invalid-source-encoding 
    -Wno-c++11-compat-deprecated-writable-strings 
    -Wno-format 
    -Wno-format-security
)
add_compile_options(${WARNING_FLAGS})

# Debug 模式
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

# ============================================================================
# 查找依赖
# ============================================================================
find_package(Threads REQUIRED)

# MySQL
find_path(MYSQL_INCLUDE_DIR mysql.h
    PATHS /usr/include/mysql /usr/local/include/mysql
)
find_library(MYSQL_LIBRARY mysqlclient
    PATHS /usr/lib/mysql /usr/local/lib/mysql /usr/lib/x86_64-linux-gnu
)

# Lua 5.1
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(LUA51 lua5.1)
endif()
if(NOT LUA51_FOUND)
    find_path(LUA51_INCLUDE_DIRS lua.h PATHS /usr/include/lua5.1 /usr/local/include/lua5.1)
    find_library(LUA51_LIBRARIES lua5.1 PATHS /usr/lib /usr/local/lib)
endif()

# Xerces-C
find_library(XERCES_LIBRARY xerces-c)

# ============================================================================
# 包含目录（全局）
# ============================================================================
include_directories(
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${MYSQL_INCLUDE_DIR}
)

# ============================================================================
# 子目录
# ============================================================================
add_subdirectory(src/Core)
add_subdirectory(src/server)

# ============================================================================
# 安装规则
# ============================================================================
install(TARGETS gameserver loginserver sharedserver
    RUNTIME DESTINATION bin
)
