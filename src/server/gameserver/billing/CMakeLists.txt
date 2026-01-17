set(BILLING_SOURCES
	CommonBillingPacket.cpp
	CommonBillingPacketHandler.cpp
	BillingPlayer.cpp
	BillingPlayerManager.cpp
	BillingPlayerInfo.cpp
)

# Game server build of billing
add_library(GameServerBilling STATIC ${BILLING_SOURCES})
target_compile_definitions(GameServerBilling PRIVATE __GAME_SERVER__)
target_include_directories(GameServerBilling PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/Core
	${CMAKE_SOURCE_DIR}/src/server
	${CMAKE_SOURCE_DIR}/src/server/database
	${CMAKE_SOURCE_DIR}/src/server/gameserver
)

# Login server build of billing
add_library(LoginServerBilling STATIC ${BILLING_SOURCES})
target_compile_definitions(LoginServerBilling PRIVATE __LOGIN_SERVER__)
target_include_directories(LoginServerBilling PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/Core
	${CMAKE_SOURCE_DIR}/src/server
	${CMAKE_SOURCE_DIR}/src/server/database
	${CMAKE_SOURCE_DIR}/src/server/loginserver
	${CMAKE_SOURCE_DIR}/src/server/gameserver
)
