#ifndef __GAME_SERVER_SKILL_TEST_H__
#define __GAME_SERVER_SKILL_TEST_H__

#include "GameServerTest.h"


class GameServerSkillTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerSkillTest, GameServerTest );
	CPPUNIT_TEST( testSharpShieldFormula );
	CPPUNIT_TEST_SUITE_END();

public:
	void testSharpShieldFormula();
	void testSharpShieldExecute();
};

#endif

