INCLUDE_DIRECTORIES(.)
ADD_DEFINITIONS(-D__LOGIN_SERVER__)
SET(LOGINSERVER_SRC 
ClientManager.cpp              LoginServer.cpp
GameServerGroupInfoManager.cpp ReconnectLoginInfoManager.cpp
GameServerManager.cpp          UserInfoManager.cpp
ItemDestroyer.cpp              ZoneGroupInfoManager.cpp
LoginPlayer.cpp                ZoneInfoManager.cpp
LoginPlayerManager.cpp         main.cpp)

SET(LoginServerBilling_SRC 
../gameserver/billing/BillingPlayer.cpp              
../gameserver/billing/BillingPlayerInfo.cpp              
../gameserver/billing/BillingPlayerManager.cpp
../gameserver/billing/CommonBillingPacket.cpp
../gameserver/billing/CommonBillingPacketHandler.cpp
)

ADD_LIBRARY(LoginServerBilling ${LoginServerBilling_SRC})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)

ADD_EXECUTABLE(loginserver ${LOGINSERVER_SRC})
TARGET_LINK_LIBRARIES(loginserver LoginServerPackets Database ServerCore Core LoginServerBilling CBilling mysqlclient zlog pthread)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
