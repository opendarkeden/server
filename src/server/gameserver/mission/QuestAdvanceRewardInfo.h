//////////////////////////////////////////////////////////////////////////////
// Filename    : QuestAdvanceRewardInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __QUEST_ADVANCE_REWARD_INFO_H__
#define __QUEST_ADVANCE_REWARD_INFO_H__

#include <list>

#include "Exception.h"
#include "Item.h"
#include "RewardInfo.h"
#include "Types.h"

class RewardClass;

//////////////////////////////////////////////////////////////////////////////
// class QuestAdvanceRewardInfo;
//////////////////////////////////////////////////////////////////////////////

class QuestAdvanceRewardInfo : public RewardInfo {
public:
    QuestAdvanceRewardInfo(RewardID_t rID, RewardClass_t rClass, int thisQLevel, int nextQLevel);
    virtual ~QuestAdvanceRewardInfo();

public:
    virtual QuestMessage canGiveReward(PlayerCreature* pPC) const;
    virtual QuestMessage giveReward(PlayerCreature* pPC) const;

    virtual string toString() const;

private:
    int m_ThisQuestLevel;
    int m_NextQuestLevel;
};

#endif
