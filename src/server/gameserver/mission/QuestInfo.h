//////////////////////////////////////////////////////////////////////////////
// Filename    : QuestInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __QUEST_INFO_H__
#define __QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Assert.h"
#include "RewardClass.h"

#include <vector>

class PlayerCreature;
class QuestStatus;

enum QuestClass
{
	QUEST_CLASS_MONSTER_KILL = 0,
	QUEST_CLASS_MEET_NPC,
	QUEST_CLASS_GATHER_ITEM,
	QUEST_CLASS_MINI_GAME,

	QUEST_CLASS_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class QuestInfo;
//////////////////////////////////////////////////////////////////////////////

class QuestInfo
{
public:
	QuestInfo( QuestID_t qID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, QuestClass questClass );
	virtual ~QuestInfo();

public:
	QuestClass		getQuestClass() const { return m_QuestClass; }

	QuestID_t		getQuestID() const { return m_QuestID; }
	virtual string	toString() const throw();

	virtual bool	canExecute( PlayerCreature* pPC ) const throw(Error);
	virtual QuestStatus*	makeQuestStatus( PlayerCreature* pPC ) const throw(Error) = 0;

	bool			isMonsterKillQuest() const { return m_QuestClass == QUEST_CLASS_MONSTER_KILL; }
	DWORD			getTimeLimit() const { return m_TimeLimitSec; }
	RewardClass_t	getRewardClass() const { return m_RewardClass; }

	bool			isEventQuest() const { return m_bEventQuest; }
	int				getQuestLevel() const { return m_QuestLevel; }

	void			setEventQuest( bool bEvent = true ) { m_bEventQuest = bEvent; }
	void			setQuestLevel( int qLevel ) { m_QuestLevel = qLevel; }

protected:
	const QuestClass	m_QuestClass;

	QuestID_t		m_QuestID;
	Race_t			m_Race;

	QuestGrade_t	m_MaxGrade;
	QuestGrade_t	m_MinGrade;

	DWORD			m_TimeLimitSec;

	RewardClass_t	m_RewardClass;

	bool			m_bEventQuest;
	int				m_QuestLevel;
};

#endif
