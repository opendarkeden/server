#ifndef __GAME_SERVER_LUCK_PERCENT_H__
#define __GAME_SERVER_LUCK_PERCENT_H__

#include "GameServerTest.h"


class GameServerItemTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerItemTest, GameServerTest );
	CPPUNIT_TEST( testLuckPercent );
	CPPUNIT_TEST( testRequireMaxVampire );
	CPPUNIT_TEST( testRequireMaxSlayer );
	CPPUNIT_TEST( testGiveNewbieItem );
	CPPUNIT_TEST_SUITE_END();

public:
	void testLuckPercent();
	void testRequireMaxVampire();
	void testRequireMaxSlayer();
	void testGiveNewbieItem();
	void testUpgradeItemType();
};

#endif

