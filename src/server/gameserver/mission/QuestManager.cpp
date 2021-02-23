
#include "QuestManager.h"
#include "QuestStatus.h"
#include "MonsterKillQuestStatus.h"
#include "GatherItemQuestStatus.h"
#include "MeetNPCQuestStatus.h"
#include "MiniGameQuestStatus.h"
#include "QuestInfoManager.h"
#include "EventQuestAdvance.h"
#include "PlayerCreature.h"
#include "Player.h"
#include "Monster.h"
#include "NPC.h"

#include "VariableManager.h"

#include "Packet.h"

#include "StringStream.h"


const hash_map<QuestID_t, QuestStatus*>::size_type QuestManager::MAX_QUEST_NUM = 1;

QuestManager::QuestManager(PlayerCreature* pOwner)
{
	m_pOwner = pOwner;
	m_Quests.clear(); 

	m_pEventQuestAdvanceManager = new EventQuestAdvanceManager( pOwner );
}

QuestManager::~QuestManager() throw (Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr;
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();

	for ( itr = m_Quests.begin() ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL ) SAFE_DELETE( itr->second );
	}

	m_Quests.clear();

	__END_CATCH
}

void QuestManager::load() throw(Error)
{
	__BEGIN_TRY

	// 아직 퀘스트 이어서 하기는 지원하지 않는다.
	m_pEventQuestAdvanceManager->load();

	__END_CATCH
}

void QuestManager::addQuest( QuestStatus* pQS ) throw(Error)
{
	__BEGIN_TRY

	Assert( pQS != NULL );
	Assert( !hasQuest( pQS->getQuestID() ) );
	pQS->setOwnerQM( this );

	m_Quests[pQS->getQuestID()] = pQS;
	
	pQS->executeWhenStart();
	
	__END_CATCH
}

QuestMessage QuestManager::isQuestComplete( QuestID_t qID ) const throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::const_iterator itr = m_Quests.find( qID );

	if ( itr == m_Quests.end() ) return COMPLETE_FAIL_NOT_IN_QUEST;

	if ( itr->second->isSuccess() )
	{
		return COMPLETE_SUCCESS;
	//	if ( g_pQuestInfoManager->canGiveReward( qID, m_pOwner ) ) return COMPLETE_SUCCESS;
	//	else return COMPLETE_FAIL_NO_INVENTORY_SPACE;
	}

	return COMPLETE_FAIL_NOT_COMPLETE;

	__END_CATCH
}


/*QuestMessage QuestManager::completeQuest( QuestID_t qID, bool checked ) throw(Error)
{
	__BEGIN_TRY

	QuestMessage code = COMPLETE_SUCCESS;
	if ( !checked )
	{
		QuestMessage code = isQuestComplete( qID );
		if ( code != COMPLETE_SUCCESS ) return code;
	}

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.find( qID );
	Assert( itr != m_Quests.end() );

	QuestStatus* pQuestStatus = itr->second;

	if ( pQuestStatus->timeExpired() )
	{
		return COMPLETE_FAIL_TIME_EXPIRED;
	}

	m_Quests.erase(itr);

	Assert( g_pQuestInfoManager->giveReward( qID, m_pOwner ) );
//	pQuestStatus->setRewarded();
	SAFE_DELETE( pQuestStatus );

	return code;

	__END_CATCH
}*/

QuestStatus* QuestManager::getQuestStatus( QuestID_t qID ) throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.find(qID);

	if ( itr == m_Quests.end() ) return NULL;
	return itr->second;

	__END_CATCH
}

void QuestManager::sendQuestInfo() throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second == NULL )
		{
			filelog("Quest.log", "QuestManager::sendQuestInfo : QuestStatus에 NULL 이 들어가있습니다.");
			continue;
		}

		Packet* pPacket = itr->second->makeStatusPacket();

		m_pOwner->getPlayer()->sendPacket( pPacket );

		SAFE_DELETE( pPacket );
	}

	__END_CATCH
}

/*MonsterKillQuestStatus*	QuestManager::getMonsterKillQuestStatus()
	throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && itr->second->isMonsterKillQuest() )
		{
			MonsterKillQuestStatus* pQS = dynamic_cast<MonsterKillQuestStatus*>( ( itr->second ) );
			return pQS;
		}
	}

	return NULL;

	__END_CATCH
}

MonsterKillQuestStatus*	QuestManager::getMonsterKillQuestStatus( SpriteType_t sType, bool isChief ) throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && itr->second->isMonsterKillQuest() )
		{
			MonsterKillQuestStatus* pQS = dynamic_cast<MonsterKillQuestStatus*>( ( itr->second ) );
			if ( pQS->isTarget( sType, isChief ) ) return pQS;
		}
	}

	return NULL;

	__END_CATCH
}
QuestMessage QuestManager::rewardCompleteQuest() throw(Error)
{
	__BEGIN_TRY

	if ( m_Quests.size() == 0 ) return COMPLETE_FAIL_NOT_IN_QUEST;

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();

	QuestMessage ret = COMPLETE_FAIL_NOT_COMPLETE;

	for ( ; itr != endItr ; ++itr )
	{
		ret = isQuestComplete( itr->second->getQuestID() );
		if ( ret == COMPLETE_SUCCESS )
		{
			return completeQuest( itr->second->getQuestID(), true );
		}
	}
	
	return ret;

	__END_CATCH
}
*/
void QuestManager::adjustQuestStatus() throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();

	while ( itr != m_Quests.end() )
	{
		if ( itr->second != NULL && ( itr->second->timeExpired() || itr->second->isRewarded() ) )
		{
			SAFE_DELETE( itr->second );
			hash_map<QuestID_t, QuestStatus*>::iterator prevItr = itr++;

			m_Quests.erase(prevItr);
		}
		else
		{
			++itr;
		}
	}

	__END_CATCH
}

QuestMessage QuestManager::cancelQuest() throw(Error)
{
	__BEGIN_TRY

	if ( m_Quests.empty() )
	{
		return CANCEL_NOT_IN_QUEST;
	}

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();
	QuestMessage result = CANCEL_NOT_IN_QUEST;

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && !itr->second->isRewarded())
		{
			itr->second->executeWhenCancel();
			SAFE_DELETE( itr->second );
			m_Quests.erase( itr );
			result = CANCEL_SUCCESS;
			break;
		}
	}

	return result;

	__END_CATCH
}

QuestMessage QuestManager::failQuest() throw(Error)
{
	__BEGIN_TRY

	if ( m_Quests.empty() )
	{
		return CANCEL_NOT_IN_QUEST;
	}

	hash_map<QuestID_t, QuestStatus*>::iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::iterator endItr = m_Quests.end();
	QuestMessage result = CANCEL_NOT_IN_QUEST;

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && !itr->second->isRewarded())
		{
			itr->second->executeWhenFail();
			SAFE_DELETE( itr->second );
			m_Quests.erase( itr );
			result = CANCEL_SUCCESS;
			break;
		}
	}

	return result;

	__END_CATCH
}

bool QuestManager::hasEventQuest( int questLevel, QuestID_t& qID ) const
{
	hash_map<QuestID_t, QuestStatus*>::const_iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::const_iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && itr->second->isEventQuest() && itr->second->getQuestLevel() == questLevel )
		{
			qID = itr->second->getQuestID();
			return true;
		}
	}

	return false;

}

bool QuestManager::successEventQuest( int questLevel, QuestID_t& qID ) const
{
	hash_map<QuestID_t, QuestStatus*>::const_iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::const_iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && itr->second->isEventQuest() && itr->second->getQuestLevel() == questLevel )
		{
			qID = itr->second->getQuestID();
			return itr->second->isSuccess();
		}
	}

	return false;
}

//RewardClass_t QuestManager::getEventQuestReward( int questLevel ) const

QuestStatus* QuestManager::getQuestStatusByQuestClass( QuestClass qClass ) const
	throw(Error)
{
	__BEGIN_TRY

	hash_map<QuestID_t, QuestStatus*>::const_iterator itr = m_Quests.begin();
	hash_map<QuestID_t, QuestStatus*>::const_iterator endItr = m_Quests.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL && itr->second->getQuestClass() == qClass )
		{
			return itr->second;
		}
	}

	return NULL;

	__END_CATCH
}

bool QuestManager::killedMonster( Monster* pMonster ) throw(Error)
{
	__BEGIN_TRY

	MonsterKillQuestStatus* pQS = dynamic_cast<MonsterKillQuestStatus*>(getQuestStatusByQuestClass( QUEST_CLASS_MONSTER_KILL ));
	if ( pQS != NULL )
	{
		return pQS->killed( pMonster->getSpriteType(), pMonster->isChief() );
	}

	return false;

	__END_CATCH
}

bool QuestManager::metNPC( NPC* pNPC ) throw(Error)
{
	__BEGIN_TRY

	MeetNPCQuestStatus* pQS = dynamic_cast<MeetNPCQuestStatus*>(getQuestStatusByQuestClass( QUEST_CLASS_MEET_NPC ));
	if ( pQS != NULL )
	{
		return pQS->met( pNPC->getNPCID() );
	}

	return false;

	__END_CATCH
}

bool QuestManager::isTargetNPC( NPC* pNPC ) throw(Error)
{
	__BEGIN_TRY
		
	MeetNPCQuestStatus* pQS = dynamic_cast<MeetNPCQuestStatus*>(getQuestStatusByQuestClass( QUEST_CLASS_MEET_NPC ));

	if ( pQS != NULL )
	{
		return pQS->isTarget( pNPC->getNPCID() );
	}

	return false;

	__END_CATCH
}

bool QuestManager::submitMiniGameScore( int GameType, uint GameScore )
{
	MiniGameQuestStatus* pQS = dynamic_cast<MiniGameQuestStatus*>(getQuestStatusByQuestClass( QUEST_CLASS_MINI_GAME ));

	if ( pQS != NULL && pQS->getGameType() == GameType )
	{
		return pQS->setScore( GameScore );
	}

	return false;
}

bool QuestManager::completeMonsterKillQuest()
{
	MonsterKillQuestStatus* pQS = dynamic_cast<MonsterKillQuestStatus*>(getQuestStatusByQuestClass( QUEST_CLASS_MONSTER_KILL ));
	if ( pQS != NULL )
	{
		pQS->completeQuest();
		return true;
	}

	return false;
}
