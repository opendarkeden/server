#ifndef __GAME_SERVER_SPEED_CHECK_TEST_H__
#define __GAME_SERVER_SPEED_CHECK_TEST_H__

#include "GameServerTest.h"


class GameServerSpeedCheckTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerSpeedCheckTest, GameServerTest );
	CPPUNIT_TEST( testSpeedHack );
	CPPUNIT_TEST_SUITE_END();

public:
	void testSpeedHack();
};

#endif

