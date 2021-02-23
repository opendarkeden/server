#ifndef __MINI_GAME_QUEST_INFO_H__
#define __MINI_GAME_QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"

#include "QuestInfo.h"
#include "MiniGameQuestStatus.h"

//////////////////////////////////////////////////////////////////////////////
// class GatherItemQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class MiniGameQuestInfo : public QuestInfo
{
public:
	MiniGameQuestInfo( QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, uint gameType )
		: QuestInfo( questID, race, maxGrade, minGrade, timeLimitSec, rClass, QUEST_CLASS_MINI_GAME ), m_GameType(gameType)
		{ }

	virtual ~MiniGameQuestInfo() { }

public:
	int		getGameType() const { return m_GameType; }
	MiniGameQuestStatus*	makeQuestStatus( PlayerCreature *pPC ) const throw(Error);

private:
	int		m_GameType;
};

#endif // __MINI_GAME_QUEST_INFO_H__
