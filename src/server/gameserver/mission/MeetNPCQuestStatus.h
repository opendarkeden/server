#ifndef __MEET_NPC_QUEST_STATUS_H__
#define __MEET_NPC_QUEST_STATUS_H__

#include "QuestStatus.h"
#include "Gpackets/GCQuestStatus.h"

class MeetNPCQuestStatus : public QuestStatus
{
public:
	MeetNPCQuestStatus( QuestID_t qID, const VSDateTime& deadline, NPCID_t npcID, NPCID_t npcID2 ) : QuestStatus( qID, deadline, QUEST_CLASS_MEET_NPC )
	{ m_TargetNPCID[0] = npcID; m_TargetNPCID[1] = npcID2; m_bMet[0] = false; m_bMet[1] = false; }
	virtual ~MeetNPCQuestStatus() { }

	bool			isSuccess() const throw(Error) { return m_bMet[0] && m_bMet[1]; }

	bool			isTarget( NPCID_t npcID ) const;
	bool			met( NPCID_t npcID );
	NPCID_t			getTargetID() const;

	GCQuestStatus* makeStatusPacket() const;

	string			toString() const throw(Error);

private:
	NPCID_t			m_TargetNPCID[2];
	bool			m_bMet[2];
};

#endif// __MEET_NPC_QUEST_STATUS_H__

