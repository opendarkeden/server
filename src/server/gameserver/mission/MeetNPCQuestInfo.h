//////////////////////////////////////////////////////////////////////////////
// Filename    : MeetNPCQuestInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MEET_NPC_QUEST_INFO_H__
#define __MEET_NPC_QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "QuestInfo.h"
#include "MeetNPCQuestStatus.h"

//////////////////////////////////////////////////////////////////////////////
// class MeetNPCQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class MeetNPCQuestInfo : public QuestInfo
{
public:
	MeetNPCQuestInfo(QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, NPCID_t npcID, NPCID_t npcID2);
	~MeetNPCQuestInfo();

public:

	virtual string					toString() const throw();

	MeetNPCQuestStatus*	makeQuestStatus( PlayerCreature* pPC ) const throw(Error);

private:
	NPCID_t		m_NPCID[2];
};

#endif
