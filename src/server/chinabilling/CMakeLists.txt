# ============================================================================
# ChinaBilling 库 - 同一份源码编译多个版本
# ============================================================================

set(CBILLING_SOURCES
    CBillingPacketErrorBody.cpp
    CBillingPacketResponseLoginBody.cpp
    CBillingPacketHeader.cpp
    CBillingPacketResponseLogoutBody.cpp
    CBillingPacketRequestIntervalValidationBody.cpp
    CBillingPacketResponseMinusMinuteBody.cpp
    CBillingPacketRequestLoginBody.cpp
    CBillingPacketResponseMinusPointBody.cpp
    CBillingPacketRequestLogoutBody.cpp
    CBillingPlayer.cpp
    CBillingPacketRequestMinusMinuteBody.cpp
    CBillingPlayerInfo.cpp
    CBillingPacketRequestMinusPointBody.cpp
    CBillingPlayerManager.cpp
    CBillingPacketResponseIntervalValidationBody.cpp
)

# ============================================================================
# GameServer 专用 CBilling 库
# ============================================================================
add_library(GameServerCBilling STATIC ${CBILLING_SOURCES})
target_compile_definitions(GameServerCBilling PRIVATE __GAME_SERVER__)
target_include_directories(GameServerCBilling PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/billing
)

# ============================================================================
# LoginServer 专用 CBilling 库
# ============================================================================
add_library(LoginServerCBilling STATIC ${CBILLING_SOURCES})
target_compile_definitions(LoginServerCBilling PRIVATE __LOGIN_SERVER__)
target_include_directories(LoginServerCBilling PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/loginserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/billing
)
