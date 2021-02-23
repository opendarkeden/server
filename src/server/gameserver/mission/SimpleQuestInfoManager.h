#ifndef __SIMPLE_QUEST_INFO_MANAGER_H__
#define __SIMPLE_QUEST_INFO_MANAGER_H__

#include "QuestInfoManager.h"

class SimpleQuestInfoManager : public QuestInfoManager
{
public:
	SimpleQuestInfoManager(NPC* pNPC) : QuestInfoManager(pNPC) { }
	virtual ~SimpleQuestInfoManager() { }

public:
	void	load(const string& name) throw(Error);

private:
};

#endif// __SIMPLE_QUEST_INFO_MANAGER_H__

