#ifndef __SCHEDULE_TEST_H__
#define __SCHEDULE_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include "Types.h"
#include "Exception.h"
#include "TestDef.h"

class ScheduleTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( ScheduleTest );
	CPPUNIT_TEST( testSchedule );
	CPPUNIT_TEST( testScheduler );
	CPPUNIT_TEST( testPQ );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSchedule();
	void testScheduler();
	void testPQ();
};

#endif

