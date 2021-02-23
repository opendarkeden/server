#ifndef __EVENT_QUEST_INFO_MANAGER_H__
#define __EVENT_QUEST_INFO_MANAGER_H__

#include "QuestInfoManager.h"

class EventQuestInfoManager : public QuestInfoManager
{
public:
	EventQuestInfoManager(NPC* pNPC) : QuestInfoManager(pNPC) { }
	virtual ~EventQuestInfoManager() { }

public:
	void	load(const string& name) throw(Error);

private:
};

#endif// __EVENT_QUEST_INFO_MANAGER_H__

