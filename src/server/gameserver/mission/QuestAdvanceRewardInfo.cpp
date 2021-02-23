
#include "QuestAdvanceRewardInfo.h"
#include "QuestManager.h"
#include "EventQuestAdvance.h"
#include "PlayerCreature.h"

QuestAdvanceRewardInfo::QuestAdvanceRewardInfo( RewardID_t rID, RewardClass_t rClass, int thisQLevel, int nextQLevel )
	: RewardInfo( rID, rClass ), m_ThisQuestLevel(thisQLevel), m_NextQuestLevel(nextQLevel)
{
}

QuestAdvanceRewardInfo::~QuestAdvanceRewardInfo()
{
}

QuestMessage QuestAdvanceRewardInfo::canGiveReward( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	EventQuestAdvanceManager* pEAM = pPC->getQuestManager()->getEventQuestAdvanceManager();
	Assert( pEAM != NULL );

	if (	pEAM->getStatus( m_ThisQuestLevel ) == EventQuestAdvance::EVENT_QUEST_ADVANCED &&
			pEAM->getStatus( m_NextQuestLevel ) == EventQuestAdvance::EVENT_QUEST_INIT
	)
		return COMPLETE_SUCCESS;

	return FAIL_BUG;

	__END_CATCH
}

QuestMessage QuestAdvanceRewardInfo::giveReward( PlayerCreature *pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	QuestMessage result = canGiveReward( pPC );

	if ( result != COMPLETE_SUCCESS ) return result;

	EventQuestAdvanceManager* pEAM = pPC->getQuestManager()->getEventQuestAdvanceManager();
	Assert( pEAM != NULL );
	
	pEAM->advanced( m_ThisQuestLevel );
	return result;

	__END_CATCH
}

string QuestAdvanceRewardInfo::toString() const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "QuestAdvanceRewardInfo("
		<< "ThisQuestLevel : " << m_ThisQuestLevel
		<< " ,NextQuestLevel : " << m_NextQuestLevel
		<< ") : " << endl << RewardInfo::toString().c_str();

	return msg.toString();

	__END_CATCH
}
