#include "AnotherQuestRewardClass.h"

#include "Assert.h"
#include "RewardInfo.h"

QuestMessage AnotherQuestRewardClass::giveReward(PlayerCreature* pPC) const

{
    __BEGIN_TRY

    Assert(pPC != NULL);

    vector<RewardInfo*>::size_type index = rand() % m_RewardInfos.size();
    return m_RewardInfos[index]->giveReward(pPC);

    __END_CATCH
}

string AnotherQuestRewardClass::toString() const {
    return "AnotherQuestRewardClass() : \n" + RewardClass::toString();
}
