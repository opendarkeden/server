#ifndef __DUMMY_QUEST_STATUS_H__
#define __DUMMY_QUEST_STATUS_H__

#include "QuestStatus.h"
#include "Gpackets/GCQuestStatus.h"

class DummyQuestStatus : public QuestStatus
{
public:
	DummyQuestStatus( QuestID_t qID, const VSDateTime& deadline, const string& NPC ) : QuestStatus( qID, deadline, QUEST_CLASS_MEET_NPC ), m_Name(NPC) { }
	virtual ~DummyQuestStatus() { }

	bool			isSuccess() { if ( !isRewarded() ) setSuccess(); return QuestStatus::isSuccess(); }
	void			completeQuest() { if ( !isSuccess() && !isRewarded() ) setSuccess(); }

	GCQuestStatus* makeStatusPacket() const;

	string			toString() const throw(Error);

private:
	string			m_Name;
};

#endif// __DUMMY_QUEST_STATUS_H__

