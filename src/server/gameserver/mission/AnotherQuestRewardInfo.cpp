
#include "AnotherQuestRewardInfo.h"
#include "QuestManager.h"
#include "PlayerCreature.h"

AnotherQuestRewardInfo::AnotherQuestRewardInfo( RewardID_t rID, RewardClass_t rClass, QuestID_t qID )
	: RewardInfo( rID, rClass ), m_QuestID(qID)
{
}

AnotherQuestRewardInfo::~AnotherQuestRewardInfo()
{
}

QuestMessage AnotherQuestRewardInfo::canGiveReward( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	return COMPLETE_SUCCESS;

	__END_CATCH
}

QuestMessage AnotherQuestRewardInfo::giveReward( PlayerCreature *pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	QuestMessage result = canGiveReward( pPC );

	if ( result != COMPLETE_SUCCESS ) return result;

	Assert( false );
	return COMPLETE_SUCCESS;

	__END_CATCH
}

string AnotherQuestRewardInfo::toString() const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "AnotherQuestRewardInfo("
		<< "QuestID : " << (uint)m_QuestID
		<< ") : " << endl << RewardInfo::toString().c_str();

	return msg.toString();

	__END_CATCH
}
