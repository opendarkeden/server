#ifndef __GAME_SERVER_RANK_EXP_H__
#define __GAME_SERVER_RANK_EXP_H__

#include "GameServerTest.h"


class GameServerExpTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerExpTest, GameServerTest );
	CPPUNIT_TEST( testRankExp );
	CPPUNIT_TEST_SUITE_END();

public:
	void testRankExp();
};

#endif

