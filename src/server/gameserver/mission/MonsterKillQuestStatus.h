#ifndef __MONSTER_KILL_QUEST_STATUS_H__
#define __MONSTER_KILL_QUEST_STATUS_H__

#include "QuestStatus.h"
#include "Gpackets/GCQuestStatus.h"

class MonsterKillQuestStatus : public QuestStatus
{
public:
	MonsterKillQuestStatus( QuestID_t qID, const VSDateTime& deadline, SpriteType_t targetSType, bool isChief, int goal ) : QuestStatus( qID, deadline, QUEST_CLASS_MONSTER_KILL )
	{ m_TargetMonsterSpriteType = targetSType; m_IsChief = isChief; m_GoalNum = goal; m_CurrentNum = 0; }
	virtual ~MonsterKillQuestStatus() { }

	//virtual bool	isSuccess() throw(Error) { return m_CurrentNum >= m_GoalNum; }
	// ( !m_IsChief || isChief ) 는 m_IsChief 이면 isChief 이어야 한다. 라는 말과 같다.
	bool			killed( SpriteType_t targetSType, bool isChief );
	bool			isTarget( SpriteType_t sType, bool isChief ) { return (!m_IsChief || isChief ) && m_TargetMonsterSpriteType == sType; }
	void			completeQuest() { m_CurrentNum = m_GoalNum; if ( !isSuccess() && !isRewarded() ) setSuccess(); }

	GCQuestStatus* makeStatusPacket() const;

	string			toString() const throw(Error);

private:
	SpriteType_t	m_TargetMonsterSpriteType;
	bool			m_IsChief;
	int				m_GoalNum;
	int				m_CurrentNum;
};

#endif// __MONSTER_KILL_QUEST_STATUS_H__

