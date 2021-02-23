//////////////////////////////////////////////////////////////////////////////
// Filename    : AnotherQuestRewardInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANOTHER_QUEST_REWARD_INFO_H__
#define __ANOTHER_QUEST_REWARD_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include "RewardInfo.h"

#include <list>

class RewardClass;

//////////////////////////////////////////////////////////////////////////////
// class AnotherQuestRewardInfo;
//////////////////////////////////////////////////////////////////////////////

class AnotherQuestRewardInfo : public RewardInfo
{
public:
	AnotherQuestRewardInfo( RewardID_t rID, RewardClass_t rClass, QuestID_t qID );
	virtual ~AnotherQuestRewardInfo();

public:
	virtual QuestMessage	canGiveReward(PlayerCreature* pPC) const throw(Error);
	// 쓰지 말 것.
	virtual QuestMessage	giveReward(PlayerCreature* pPC) const throw(Error);

	bool	isAnotherQuest() const { return true; }
	QuestID_t	getQuestID() const { return m_QuestID; }

	virtual string	toString() const throw();

private:
	QuestID_t		m_QuestID;
};

#endif
