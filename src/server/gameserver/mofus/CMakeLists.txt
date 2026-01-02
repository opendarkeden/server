ADD_DEFINITIONS(-D__LINUX__ -D__GAME_SERVER__)
SET(LIBMOFUS_SRC
	Mofus.cpp
	MPacketManager.cpp
	MPlayer.cpp
	MPlayerManager.cpp
	PKTConnectAccept.cpp
	PKTConnectAcceptHandler.cpp
	PKTConnectAsk.cpp
	PKTError.cpp
	PKTErrorHandler.cpp
	PKTLogout.cpp
	PKTPowerPoint.cpp
	PKTPowerPointHandler.cpp
	PKTReceiveOK.cpp
	PKTResult.cpp
	PKTUserInfo.cpp
	PKTSError.cpp)

add_library(Mofus STATIC ${LIBMOFUS_SRC})

target_compile_definitions(Mofus PRIVATE __GAME_SERVER__)

target_include_directories(Mofus PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/Core
	${CMAKE_SOURCE_DIR}/src/server
	${CMAKE_SOURCE_DIR}/src/server/database
	${CMAKE_SOURCE_DIR}/src/server/gameserver
)
