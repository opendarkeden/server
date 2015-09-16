ADD_DEFINITIONS(-D__LINUX__ -D__GAME_SERVER__)
INCLUDE_DIRECTORIES(.. .)
SET(LIBBILLING_SRC
	CommonBillingPacket.cpp
	CommonBillingPacketHandler.cpp
	BillingPlayer.cpp
	BillingPlayerManager.cpp
	BillingPlayerInfo.cpp)
ADD_LIBRARY(GameServerBilling STATIC ${LIBBILLING_SRC})
