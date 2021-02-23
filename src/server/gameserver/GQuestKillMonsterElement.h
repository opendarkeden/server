#ifndef __GQUEST_KILL_MONSTER_ELEMENT_H__
#define __GQUEST_KILL_MONSTER_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include <vector>
#include <algorithm>

class GQuestKillMonsterMission : public GQuestMission
{
public:
	GQuestKillMonsterMission() : m_Current(0) { }
	DWORD	getCurrent() const { return m_Current; }
	void	increase() { m_Current++; }

	bool	isTarget(SpriteType_t target) { return find(m_TargetList.begin(), m_TargetList.end(), target) != m_TargetList.end(); }

	string	getMissionName() const { return "KillMonsterMission"; }

	vector<SpriteType_t>&	getTargetList() { return m_TargetList; }
private:
	vector<SpriteType_t>	m_TargetList;
	DWORD	m_Current;
};

class GQuestKillMonsterElement : public GQuestElement
{
public:
	GQuestKillMonsterElement() : m_Goal(0) { }
	string 						getElementName() const { return "KillMonster"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::KILLMONSTER; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestKillMonsterElement*	makeElement(XMLTree* pTree);

	DWORD	getGoal() const { return m_Goal; }

private:
	vector<SpriteType_t>	m_TargetList;
	DWORD					m_TargetNum;
	DWORD					m_Goal;
};

extern GQuestKillMonsterElement g_KillMonsterElement;

#endif
