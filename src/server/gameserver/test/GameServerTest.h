#ifndef __GAME_SERVER_TEST_H__
#define __GAME_SERVER_TEST_H__

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Exception.h"
#include "TestDef.h"
#include "Types.h"

class GameServerTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(GameServerTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
};

#endif
