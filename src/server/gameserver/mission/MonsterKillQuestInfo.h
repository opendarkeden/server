//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterKillQuestInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_KILL_QUEST_INFO_H__
#define __MONSTER_KILL_QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "QuestInfo.h"
#include "MonsterKillQuestStatus.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterKillQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class MonsterKillQuestInfo : public QuestInfo
{
public:
	MonsterKillQuestInfo(QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, SpriteType_t monsterType, bool isChief, int killCount);
	~MonsterKillQuestInfo();

public:

	virtual string					toString() const throw();

	virtual MonsterKillQuestStatus*	makeQuestStatus( PlayerCreature* pPC ) const throw(Error);
	bool	isMonsterKillQuest() const { return true; }

	int		getGoalNum() const { return m_GoalNum; }
	SpriteType_t	getTargetMonsterSpriteType() const { return m_TargetMonsterSpriteType; }

private:
	SpriteType_t	m_TargetMonsterSpriteType;	// 퀘스트에서 잡을 몬스터의 스프라이트 타입
	bool			m_IsChief;				// 퀘스트에서 잡을 몬스터가 chief이어야 하는가?
	int				m_GoalNum;			// 퀘스트에서 잡을 몬스터 수
};

#endif
