ADD_DEFINITIONS(-D__GAME_SERVER__)
INCLUDE_DIRECTORIES(.. .)
SET(LIBWAR_SRC
	Schedule.cpp
	Scheduler.cpp
	War.cpp
	RaceWar.cpp
	GuildWar.cpp
	SiegeWar.cpp
	WarSchedule.cpp
	WarScheduler.cpp
	WarSystem.cpp
	ZoneItemPosition.cpp
	InventoryItemPosition.cpp
	MouseItemPosition.cpp
	CorpseItemPosition.cpp
	RaceWarLimiter.cpp
	DragonEyeManager.cpp
#	SubInventoryItemPosition.cpp)
)


ADD_LIBRARY(War STATIC ${LIBWAR_SRC})

target_include_directories(War PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/Core
	${CMAKE_SOURCE_DIR}/src/server
	${CMAKE_SOURCE_DIR}/src/server/database
	${CMAKE_SOURCE_DIR}/src/server/gameserver
)
