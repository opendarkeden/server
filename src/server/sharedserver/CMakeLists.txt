ADD_DEFINITIONS(-D__SHARED_SERVER__)
SET(SRC
	Guild.cpp
  GuildManager.cpp
  ResurrectLocationManager.cpp
  GameServerPlayer.cpp
	HeartbeatManager.cpp
  GameServerInfoManager.cpp
	GameServerGroupInfoManager.cpp
  GameServerManager.cpp
	SharedServer.cpp
  main.cpp
  StringPool.cpp)
ADD_EXECUTABLE(sharedserver ${SRC})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
TARGET_LINK_LIBRARIES(sharedserver Database SharedServerPackets ServerCore Core mysqlclient zlog pthread z)
