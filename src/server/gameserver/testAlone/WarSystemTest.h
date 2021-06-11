#ifndef __WAR_SYSTEM_TEST_H__
#define __WAR_SYSTEM_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include "Types.h"
#include "Exception.h"
#include "TestDef.h"

class WarSystemTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( WarSystemTest );
	CPPUNIT_TEST( testWarStart );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testWarStart();
};

#endif

