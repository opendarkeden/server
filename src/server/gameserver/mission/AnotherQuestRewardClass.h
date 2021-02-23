//////////////////////////////////////////////////////////////////////////////
// Filename    : AnotherQuestRewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANOTHER_QUEST_REWARD_CLASS_H__
#define __ANOTHER_QUEST_REWARD_CLASS_H__

#include "RewardClass.h"

//////////////////////////////////////////////////////////////////////////////
// class AnotherQuestRewardClass;
//////////////////////////////////////////////////////////////////////////////

class AnotherQuestRewardClass : public RewardClass
{
public:
	AnotherQuestRewardClass( RewardClass_t rClass ) : RewardClass(rClass) { }

public:
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) const throw(Error);
	bool	anotherQuestReward() const { return true; }

	virtual string	toString() const throw();

private:
};

#endif
