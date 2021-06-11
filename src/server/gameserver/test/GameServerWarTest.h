#ifndef __GAME_SERVER_WAR_TEST_H__
#define __GAME_SERVER_WAR_TEST_H__

#include "GameServerTest.h"


class GameServerWarTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerWarTest, GameServerTest );
	CPPUNIT_TEST( testWarEndTime );
	CPPUNIT_TEST_SUITE_END();

public:
	void testWarEndTime();
};

#endif

