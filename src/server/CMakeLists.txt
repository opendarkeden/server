INCLUDE_DIRECTORIES(. ../Core ./database)
ADD_DEFINITIONS(-D__LINUX__)

ADD_SUBDIRECTORY(database)
ADD_SUBDIRECTORY(chinabilling)

SET(SERVER_CORE_SRC CondVar.cpp LogData.cpp LogClient.cpp Mutex.cpp PlayerManager.cpp GameWorldInfoManager.cpp SystemAPI.cpp Thread.cpp ThreadAttr.cpp Timeval.cpp pthreadAPI.cpp Profile.cpp PacketProfile.cpp GameServerInfoManager.cpp PaySystem.cpp)
ADD_LIBRARY(ServerCore STATIC ${SERVER_CORE_SRC})

ADD_SUBDIRECTORY(loginserver)
ADD_SUBDIRECTORY(gameserver)
ADD_SUBDIRECTORY(sharedserver)