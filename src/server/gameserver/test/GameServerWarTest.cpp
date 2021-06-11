#include "GameServerWarTest.h"
#include "VSDateTime.h"

void
GameServerWarTest::testWarEndTime()
{
	__BEGIN_TEST_CASE

	VSDateTime dt( VSDate(2003,2,2), VSTime(10,33));

	CPPUNIT_ASSERT( dt.date().year()==2003 );
	CPPUNIT_ASSERT( dt.date().month()==2 );
	CPPUNIT_ASSERT( dt.date().day()==2 );
	CPPUNIT_ASSERT( dt.time().hour()==10 );
	CPPUNIT_ASSERT( dt.time().minute()==33 );

	cout << "Before: " << dt.toString().c_str() << endl;

	VSDateTime after( dt.addSecs( 1*60*60 ) );

	cout << "After 60*60 Sec: " << after.toString().c_str() << endl;

	CPPUNIT_ASSERT( after.date().year()==2003 );
	CPPUNIT_ASSERT( after.date().month()==2 );
	CPPUNIT_ASSERT( after.date().day()==2 );
	CPPUNIT_ASSERT( after.time().hour()==11 );
	CPPUNIT_ASSERT( after.time().minute()==33 );

	__END_TEST_CASE
}
