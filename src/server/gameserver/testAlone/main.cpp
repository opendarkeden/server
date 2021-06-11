#include "Types.h"
#include "Exception.h"
#include <stdio.h>
#include <string>
#include "ScheduleTest.h"
//#include "WarSystemTest.h"

int main()
{
	string DateTime = "2003-02-08 14:00:00";
	int year  = atoi( DateTime.substr(0,4).c_str() );
	int month = atoi( DateTime.substr(5,2).c_str() );
	int day   = atoi( DateTime.substr(8,2).c_str() );
	int hour  = atoi( DateTime.substr(11,2).c_str() );
	int min   = atoi( DateTime.substr(14,2).c_str() );
	int sec   = atoi( DateTime.substr(17,2).c_str() );

	printf( "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec );
/*
	try {
	__BEGIN_TEST
	
		//---------------------------------------------------------------
		//
		//                   Add ALL TestSuite
		//
		//---------------------------------------------------------------
		cout << "---------- Start Add TestSuite ----------" << endl;
		ADD_TEST(ScheduleTest)
//		ADD_TEST(WarSystemTest)
		cout << "---------- End Add TestSuite ----------" << endl;

		//---------------------------------------------------------------
		//
		//                   Run Test
		//
		//---------------------------------------------------------------
		cout << "---------- Run Test ----------" << endl;

		RUN_TEST("");

		cout << "---------- End Test ----------" << endl;

	__END_TEST
	} catch (Throwable& t) {

		cout << t.toString().c_str() << endl;

		cout << "--------- UNHANDLED EXCEPTION!! ---------" << endl;
	}
*/
	return 0;
}

