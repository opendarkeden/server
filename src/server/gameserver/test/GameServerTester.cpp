#include "Types.h"
#include "Exception.h"
#include "Properties.h"
#include <stdio.h>
#include "GameServerTest.h"
#include "GameServerSkillTest.h"
//#include "GameServerUserGatewayTest.h"
#include "GameServerExpTest.h"
#include "GameServerItemTest.h"
#include "GameServerSpeedCheckTest.h"
#include "GameServerWarTest.h"

void testGameServer()
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_TEST
	
		//---------------------------------------------------------------
		//
		//                   Add ALL TestSuite
		//
		//---------------------------------------------------------------
		cout << "---------- Start Add TestSuite ----------" << endl;
		ADD_TEST(GameServerTest)
		ADD_TEST(GameServerSkillTest)
//		ADD_TEST(GameServerUserGatewayTest)
		ADD_TEST(GameServerWarTest)
		ADD_TEST(GameServerExpTest)
		ADD_TEST(GameServerItemTest)
		ADD_TEST(GameServerSpeedCheckTest)
		cout << "---------- End Add TestSuite ----------" << endl;

		//---------------------------------------------------------------
		//
		//                   Run Test
		//
		//---------------------------------------------------------------
		cout << "---------- Run Test ----------" << endl;

		if (g_pTestConfig==NULL)
		{
			RUN_TEST("");
		}
		else
		{
			try {
				int maxTest = g_pTestConfig->getPropertyInt("MaxTest");

				char testNumName[10];
				for (int i=1; i<=maxTest; i++)
				{
					sprintf(testNumName, "Test%d", maxTest);

					try {
						string testName = g_pTestConfig->getProperty( string(testNumName) );

						RUN_TEST(testName);
				
					} catch (NoSuchElementException& nsee) {
						// getProperty( testNumName )
					}
				}
			} catch (NoSuchElementException& nsee) {
				// getPropertyInt( "MaxTest" )	

				RUN_TEST("");
			}
		}

		cout << "---------- End Test ----------" << endl;

	__END_TEST
	__END_CATCH
}

