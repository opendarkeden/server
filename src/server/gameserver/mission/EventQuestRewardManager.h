#ifndef __EVENT_QUEST_REWARD_MANAGER_H__
#define __EVENT_QUEST_REWARD_MANAGER_H__

#include "RewardClassInfoManager.h"

class EventQuestRewardManager : public RewardClassInfoManager
{
public:
	EventQuestRewardManager(NPC* pNPC) : RewardClassInfoManager(pNPC) { }
	~EventQuestRewardManager() { }

public:
	void load(const string& name) throw(Error);
};

#endif// __EVENT_QUEST_REWARD_MANAGER_H__
