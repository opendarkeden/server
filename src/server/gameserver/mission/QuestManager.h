#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "QuestInfo.h"
#include "QuestStatus.h"

#include "Gpackets/GCNPCResponse.h"

#include <hash_map>

const DWORD PET_QUEST_ID = 0xffff;

class QuestStatus;
class MonsterKillQuestStatus;
class PlayerCreature;
class EventQuestAdvanceManager;

class Monster;
class Item;
class NPC;

class QuestManager
{
public:
	QuestManager(PlayerCreature* pOwner);
	~QuestManager() throw(Error);

	void				load() throw(Error);

	bool				canStartMoreQuest() const { return m_Quests.size() < MAX_QUEST_NUM; }
	bool				hasQuest( QuestID_t qID ) const { return m_Quests.find(qID) != m_Quests.end(); }

	void				addQuest( QuestStatus* pQS ) throw(Error);
	void				questRewarded( QuestID_t qID ) { m_Quests.erase( qID ); }

	QuestMessage		isQuestComplete( QuestID_t qID ) const throw(Error);

	QuestStatus*		getQuestStatus( QuestID_t qID ) throw(Error);
	void				sendQuestInfo() throw(Error);
	void				adjustQuestStatus() throw(Error);

	template<class QOutItr, class ROutItr>
	void				getCompletedQuestRewards(QOutItr qitr, ROutItr oitr) const
	{
		for ( hash_map<QuestID_t, QuestStatus*>::const_iterator itr = m_Quests.begin() ;
				itr != m_Quests.end(); ++itr )
		{
			if ( itr->second->isSuccess() )
			{
				(*qitr++)=itr->second->getQuestID();
				(*oitr++)=itr->second->getRewardClass();
			}
		}
	}

	QuestMessage		cancelQuest() throw(Error);
	QuestMessage		failQuest() throw(Error);
	bool				hasQuest() const { return m_Quests.size() != 0; }
	bool				hasEventQuest( int questLevel, QuestID_t& qID ) const;
	bool				successEventQuest( int questLevel, QuestID_t& qID ) const;
	RewardClass_t		getEventQuestReward( int questLevel ) const;

	QuestStatus*		getQuestStatusByQuestClass( QuestClass qClass ) const throw(Error);
	EventQuestAdvanceManager*	getEventQuestAdvanceManager() const { return m_pEventQuestAdvanceManager; }

public:
	bool				killedMonster( Monster* pMonster ) throw(Error);
//	bool				gotItem( Item* pItem ) throw(Error);
	bool				metNPC( NPC* pNPC ) throw(Error);
	bool				isTargetNPC( NPC* pNPC ) throw(Error);
	bool				submitMiniGameScore( int GameType, uint GameScore );

	bool				completeMonsterKillQuest();

protected:
	PlayerCreature*		getOwner() const { return m_pOwner; }
	friend class		QuestStatus;

private:
	static const hash_map<QuestID_t, QuestStatus*>::size_type MAX_QUEST_NUM;
	PlayerCreature*		m_pOwner;
	EventQuestAdvanceManager*	m_pEventQuestAdvanceManager;
	hash_map<QuestID_t, QuestStatus*>	m_Quests;
};

#endif// __QUEST_MANAGER_H__

