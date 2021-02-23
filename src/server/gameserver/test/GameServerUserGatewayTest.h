#ifndef __GAME_SERVER_USER_GATEWAY_TEST_H__
#define __GAME_SERVER_USER_GATEWAY_TEST_H__

#include "GameServerTest.h"


class GameServerUserGatewayTest : public GameServerTest {
	CPPUNIT_TEST_SUB_SUITE( GameServerUserGatewayTest, GameServerTest );
	CPPUNIT_TEST( testUserPass );
	CPPUNIT_TEST( testUserPassToString );
	CPPUNIT_TEST_SUITE_END();

public:
	void testUserPass();
	void testUserPassToString();
};

#endif

