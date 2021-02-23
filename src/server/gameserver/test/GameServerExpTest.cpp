#include "GameServerExpTest.h"
#include "skill/SkillUtil.h"
#include "VariableManager.h"

void
GameServerExpTest::testRankExp()
{
	__BEGIN_TEST_CASE

	int rankExpGain = 0;
	
	for (int myLevel=0; myLevel<=100; myLevel++)
	{
		for (int otherLevel=0; otherLevel<=100; otherLevel++)
		{
			// 100%
			g_pVariableManager->setVariable( RANK_EXP_GAIN_PERCENT, 100 );
			rankExpGain = g_pVariableManager->getVariable( RANK_EXP_GAIN_PERCENT );
			CPPUNIT_ASSERT( rankExpGain==100 );

			RankExp_t rankExp1 = computeRankExp( myLevel, otherLevel );
			RankExp_t rankExp1_2 = rankExp1*2;
			//CPPUNIT_ASSERT( rankExpGain==¾ó¸¶ ); -_-;

			if (myLevel==0 || otherLevel==0)
			{
				CPPUNIT_ASSERT( rankExp1==0 );
			}


			// 200%
			g_pVariableManager->setVariable( RANK_EXP_GAIN_PERCENT, 200 );
			rankExpGain = g_pVariableManager->getVariable( RANK_EXP_GAIN_PERCENT );
			CPPUNIT_ASSERT( rankExpGain==200 );

			RankExp_t rankExp2 = computeRankExp( myLevel, otherLevel );

			if (rankExp1_2 != rankExp2)
			{
				cout << myLevel << ":" << otherLevel << " --> " << rankExp1 << " * 2 = " << rankExp1_2 << " != " << rankExp2 << endl;
			}

			CPPUNIT_ASSERT( rankExp1_2==rankExp2 );

						// 300%
			g_pVariableManager->setVariable( RANK_EXP_GAIN_PERCENT, 300 );
			rankExpGain = g_pVariableManager->getVariable( RANK_EXP_GAIN_PERCENT );
			CPPUNIT_ASSERT( rankExpGain==300 );

			RankExp_t rankExp3 = computeRankExp( myLevel, otherLevel );
			CPPUNIT_ASSERT( rankExp1*3==rankExp3 );
		}
	}

	__END_TEST_CASE
}
