#ifndef __TEST_DEF__
#define __TEST_DEF__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include "Types.h"
#include "Exception.h"

#define __BEGIN_TEST  		{ CppUnit::TextUi::TestRunner runner;
#define ADD_TEST(test)    	  runner.addTest( test::suite() );
#define	RUN_TEST(testName)    runner.run( testName, true );
#define __END_TEST    }

#define __BEGIN_TEST_CASE	try {
#define __END_TEST_CASE 	} catch (Throwable& t) {										\
								cout << "---------------------------- TestCase Exception Handled" << endl;	\
								cout << "-" << endl;														\
								cout << "-     " << t.toString().c_str() << endl;							\
								cout << "-" << endl;														\
								cout << "---------------------------- TestCase Exception Handled" << endl;	\
								throw;														\
							}

//filelog("testException.log", "%s", t.toString().c_str());
#endif

