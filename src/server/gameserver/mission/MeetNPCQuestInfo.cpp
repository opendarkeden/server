//////////////////////////////////////////////////////////////////////////////
// Filename    : MeetNPCQuestInfo.cpp
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MeetNPCQuestInfo.h"
#include "MeetNPCQuestStatus.h"
#include "DB.h"
#include "Assert.h"
#include "StringStream.h"

MeetNPCQuestInfo::MeetNPCQuestInfo(QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass,
									NPCID_t	npcID, NPCID_t npcID2)
: QuestInfo( questID, race, maxGrade, minGrade, timeLimitSec, rClass, QUEST_CLASS_MEET_NPC )
{
	m_NPCID[0] = npcID;
	m_NPCID[1] = npcID2;
}

MeetNPCQuestInfo::~MeetNPCQuestInfo()
{
}

string MeetNPCQuestInfo::toString () const throw ()
{
	StringStream msg;

	msg << "MeetNPCQuestInfo("
		<< m_NPCID[0] << ", " << m_NPCID[1]
		<< ") : " << endl << QuestInfo::toString().c_str();

	return msg.toString();
}

MeetNPCQuestStatus* MeetNPCQuestInfo::makeQuestStatus( PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	MeetNPCQuestStatus* newQS = new MeetNPCQuestStatus(
			m_QuestID, VSDateTime::currentDateTime().addSecs( m_TimeLimitSec ),
			m_NPCID[0], m_NPCID[1] );

	Assert( newQS != NULL );

	return newQS;

	__END_CATCH
}

