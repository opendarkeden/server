
#include "SimpleQuestInfoManager.h"
#include "RewardClass.h"
#include "RewardClassInfoManager.h"
#include "MonsterKillQuestInfo.h"
#include "Assert.h"
#include "DB.h"

void SimpleQuestInfoManager::load(const string& name) 
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT QuestID, Race, MaxGrade, MinGrade, TimeLimitSec, RewardClass, TargetSType, IsChief, Goal FROM MonsterKillQuestInfo WHERE NPC = '%s'"
				, name.c_str() );

		while (pResult->next()) 
		{
			int index = 0;
			QuestID_t		qID			= (QuestID_t) 	pResult->getInt( ++index );
			Race_t			race		= (Race_t)		pResult->getInt( ++index );
			QuestGrade_t	MaxGrade	= (QuestGrade_t)pResult->getInt( ++index );
			QuestGrade_t	MinGrade	= (QuestGrade_t)pResult->getInt( ++index );
			DWORD			timeLimit	= (DWORD)		pResult->getInt( ++index );
			RewardClass_t	rewardClass	= (RewardClass_t)pResult->getInt(++index );
			SpriteType_t	monsterSType= (SpriteType_t)pResult->getInt( ++index );
			bool			isChief		= ( pResult->getInt( ++index ) == 0 )?false:true;
			int				killCount	= (int)			pResult->getInt( ++index );

//			RewardClass* pRC = g_pRewardClassInfoManager->getRewardClass( rewardClass );
//			Assert( pRC != NULL );

			MonsterKillQuestInfo* pMonsterKillQI = new MonsterKillQuestInfo( qID, race, MaxGrade, MinGrade, timeLimit, rewardClass, monsterSType, isChief, killCount );
			addQuestInfo( pMonsterKillQI );

			//cout << "Loading Quest Info : " << pMonsterKillQI->toString() << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}
