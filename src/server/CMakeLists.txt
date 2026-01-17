# ============================================================================
# Server 模块
# ============================================================================

# ============================================================================
# ServerCore 库 - 服务器公共代码
# ============================================================================
set(SERVER_CORE_SOURCES
    CondVar.cpp
    LogData.cpp
    LogClient.cpp
    Mutex.cpp
    PlayerManager.cpp
    GameWorldInfoManager.cpp
    SystemAPI.cpp
    Thread.cpp
    ThreadAttr.cpp
    Timeval.cpp
    pthreadAPI.cpp
    Profile.cpp
    PacketProfile.cpp
    GameServerInfoManager.cpp
    PaySystem.cpp
)

add_library(ServerCore STATIC ${SERVER_CORE_SOURCES})
target_include_directories(ServerCore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
)

# ============================================================================
# 子目录
# ============================================================================
add_subdirectory(database)
add_subdirectory(chinabilling)
add_subdirectory(gameserver)
add_subdirectory(loginserver)
add_subdirectory(sharedserver)
