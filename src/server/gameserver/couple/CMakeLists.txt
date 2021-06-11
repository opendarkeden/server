ADD_DEFINITIONS(-D__GAME_SERVER__)
INCLUDE_DIRECTORIES(..)
SET(LIBCOUPLE_SRC
	PartnerWaitingManager.cpp
	CoupleManager.cpp
	WaitForMeet.cpp
	WaitForApart.cpp
)
ADD_LIBRARY(Couple STATIC ${LIBCOUPLE_SRC})