#include "QuestInfoManager.h"

#include "QuestInfo.h"
#include "ItemRewardInfo.h"
#include "MonsterKillQuestInfo.h"
#include "GatherItemQuestInfo.h"
#include "QuestManager.h"
#include "EventQuestAdvance.h"

#include "PlayerCreature.h"
#include "NPC.h"
#include "VariableManager.h"

#include "Item.h"

#include "DB.h"

QuestInfoManager::~QuestInfoManager()
	throw(Error)
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void QuestInfoManager::clear() throw(Error)
{
	__BEGIN_TRY

	QuestInfoHashMap::iterator itr = m_QuestInfos.begin();
	QuestInfoHashMap::iterator endItr = m_QuestInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL ) SAFE_DELETE( itr->second );
	}

	m_QuestInfos.clear();

	__END_CATCH
}

bool QuestInfoManager::isEventQuest( QuestID_t qID ) const 
{
	QuestInfoHashMap::const_iterator itr = m_QuestInfos.find(qID);
	if ( itr != m_QuestInfos.end() )
	{
		return itr->second->isEventQuest();
	}
	return false;
}

/*void QuestInfoManager::load( const string& name )
	throw(Error)
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT QuestID, Race, MaxGrade, MinGrade, TimeLimitSec, RewardClass, TargetSType, IsChief, Goal FROM MonsterKillQuestInfo");

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

			cout << "Loading Quest Info : " << pMonsterKillQI->toString() << endl;
		}

		pResult = pStmt->executeQuery(
				"SELECT QuestID, Race, MaxGrade, MinGrade, TimeLimitSec, RewardClass, TargetIClass, TargetIType, Goal FROM GatherItemQuestInfo");

		while (pResult->next()) 
		{
			int index = 0;
			QuestID_t		qID			= (QuestID_t) 	pResult->getInt( ++index );
			Race_t			race		= (Race_t)		pResult->getInt( ++index );
			QuestGrade_t	MaxGrade	= (QuestGrade_t)pResult->getInt( ++index );
			QuestGrade_t	MinGrade	= (QuestGrade_t)pResult->getInt( ++index );
			DWORD			timeLimit	= (DWORD)		pResult->getInt( ++index );
			RewardClass_t	rewardClass	= (RewardClass_t)pResult->getInt(++index );
			Item::ItemClass iClass 		= (Item::ItemClass)pResult->getInt( ++index );
			ItemType_t		iType		= (ItemType_t)pResult->getInt( ++index );
			int				Count		= (int)			pResult->getInt( ++index );

//			RewardClass* pRC = g_pRewardClassInfoManager->getRewardClass( rewardClass );
//			Assert( pRC != NULL );

			GatherItemQuestInfo* pGatherItemQI = new GatherItemQuestInfo( qID, race, MaxGrade, MinGrade, timeLimit, rewardClass, iClass, iType, Count );
			addQuestInfo( pGatherItemQI );

			cout << "Loading Quest Info : " << pGatherItemQI->toString() << endl;
		}

//		나중에 하자
//		pResult = pStmt->executeQuery(
//				"SELECT QuestID, Race, MaxGrade, MinGrade, TimeLimitSec, RewardClass, TargetSType, IsChief, Goal FROM MonsterKillQuestInfo");
//
//		while (pResult->next()) 
//		{
//			int index = 0;
//			QuestID_t		qID			= (QuestID_t) 	pResult->getInt( ++index );
//			Race_t			race		= (Race_t)		pResult->getInt( ++index );
//			QuestGrade_t	MaxGrade	= (QuestGrade_t)pResult->getInt( ++index );
//			QuestGrade_t	MinGrade	= (QuestGrade_t)pResult->getInt( ++index );
//			DWORD			timeLimit	= (DWORD)		pResult->getInt( ++index );
//			RewardClass_t	rewardClass	= (RewardClass_t)pResult->getInt(++index );
//			SpriteType_t	monsterSType= (SpriteType_t)pResult->getInt( ++index );
//			bool			isChief		= ( pResult->getInt( ++index ) == 0 )?false:true;
//			int				killCount	= (int)			pResult->getInt( ++index );
//
//			RewardClass* pRC = g_pRewardClassInfoManager->getRewardClass( rewardClass );
//			Assert( pRC != NULL );
//
//			MonsterKillQuestInfo* pMonsterKillQI = new MonsterKillQuestInfo( qID, race, MaxGrade, MinGrade, timeLimit, pRC, monsterSType, isChief, killCount );
//			addQuestInfo( pMonsterKillQI );
//
//			cout << "Loading Quest Info : " << pMonsterKillQI->toString() << endl;
//		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	__END_CATCH
}
*/

void QuestInfoManager::addQuestInfo(QuestInfo* pQI)
	throw(Error)
{
	__BEGIN_TRY

	QuestInfoHashMap::iterator itr = m_QuestInfos.find( pQI->getQuestID() );

	if ( itr != m_QuestInfos.end() ) throw Error("QuestInfoManager::addQuestInfo : QuestID 가 중복됩니다.");

	m_QuestInfos[ pQI->getQuestID() ] = pQI;

	__END_CATCH
}

QuestMessage QuestInfoManager::canExecuteQuest( QuestID_t qID, PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	if ( !g_pVariableManager->canApplyQuest() ) return START_FAIL_CANNOT_APPLY_QUEST;
	if ( pPC->getQuestManager()->hasQuest(qID) ) return START_FAIL_DUPLICATED_QUEST_ID;
	if ( !pPC->getQuestManager()->canStartMoreQuest() ) return START_FAIL_QUEST_NUM_EXCEEDED;

	QuestInfoHashMap::const_iterator itr = m_QuestInfos.find( qID );
	if ( itr == m_QuestInfos.end() )
	{
		filelog("EventBug.txt","QuestInfoManager::canExcuteQuest : 클라이언트가 보내준 qID가 이 NPC한테 없다 ㅜ.ㅠ %s:%d", 
				m_pOwnerNPC->getName().c_str(), qID );
		return FAIL_BUG;
	}
	if ( !itr->second->canExecute( pPC ) ) return START_FAIL_PC;

	return START_SUCCESS;

	__END_CATCH
}

QuestMessage QuestInfoManager::startQuest( QuestID_t qID, PlayerCreature* pPC ) throw(Error)
{
	__BEGIN_TRY

	QuestMessage code = canExecuteQuest( qID, pPC );
	if ( code != START_SUCCESS ) return code;

	QuestStatus* pQuestStatus = makeQuestStatus( qID, pPC );

	if ( pQuestStatus->isEventQuest() ) 
	{
		if ( !pPC->getQuestManager()->getEventQuestAdvanceManager()->start( pQuestStatus->getQuestLevel() ) )
		{
			filelog("EventBug.txt","QuestInfoManager::startQuest : 퀘스트 시작해야 되는데 퀘스트 어드밴스 매니저가 INIT가 아니다. %s:%d (Level %d)",
					pPC->getName().c_str(), qID, pQuestStatus->getQuestLevel() );
		}
	}

	pPC->getQuestManager()->addQuest( pQuestStatus );

	return code;

	__END_CATCH
}

QuestStatus* QuestInfoManager::makeQuestStatus( QuestID_t qID, PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	QuestInfoHashMap::const_iterator itr = m_QuestInfos.find( qID );

	if ( itr == m_QuestInfos.end() ) return NULL;

	QuestStatus* pQuestStatus = itr->second->makeQuestStatus( pPC );

	pQuestStatus->setEventQuest( itr->second->isEventQuest() );
	pQuestStatus->setQuestLevel( itr->second->getQuestLevel() );
	pQuestStatus->setTimeLimit( itr->second->getTimeLimit() != 0 );

	pQuestStatus->setRewardClass( itr->second->getRewardClass() );

	return pQuestStatus;

	__END_CATCH
}

/*bool QuestInfoManager::canGiveReward( QuestID_t qID, PlayerCreature* pPC ) const throw(Error)
{ 
	__BEGIN_TRY

	QuestInfoHashMap::const_iterator itr = m_QuestInfos.find( qID );

	if ( itr == m_QuestInfos.end() ) return false;

	return itr->second->canGiveReward( pPC );

	__END_CATCH
}

bool QuestInfoManager::giveReward( QuestID_t qID, PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	QuestInfoHashMap::const_iterator itr = m_QuestInfos.find( qID );

	if ( itr == m_QuestInfos.end() ) return false;

	return itr->second->giveReward( pPC );

	__END_CATCH
}*/
