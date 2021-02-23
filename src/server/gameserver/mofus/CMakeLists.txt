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
ADD_LIBRARY(Mofus STATIC ${LIBMOFUS_SRC})