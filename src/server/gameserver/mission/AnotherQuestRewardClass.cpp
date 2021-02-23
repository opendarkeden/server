#include "AnotherQuestRewardClass.h"
#include "RewardInfo.h"
#include "Assert.h"

QuestMessage AnotherQuestRewardClass::giveReward( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	vector<RewardInfo*>::size_type index = rand() % m_RewardInfos.size();
	return m_RewardInfos[ index ]->giveReward(pPC);

	__END_CATCH
}

string AnotherQuestRewardClass::toString() const throw()
{
	return "AnotherQuestRewardClass() : \n" + RewardClass::toString();
}
