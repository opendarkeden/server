#ifndef __GQUEST_PARTY_DISSECT_ELEMENT_H__
#define __GQUEST_PARTY_DISSECT_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include <vector>
#include <list>
#include <algorithm>

class GQuestPartyDissectMission : public GQuestMission
{
public:
	GQuestPartyDissectMission() { }
	DWORD	getCurrent() const { return m_NumArg; }
	void	increase() { m_NumArg++; }

	bool	isTarget(SpriteType_t target) { return find(m_TargetList.begin(), m_TargetList.end(), target) != m_TargetList.end(); }

	string	getMissionName() const { return "PartyDissectMission"; }

	vector<SpriteType_t>&	getTargetList() { return m_TargetList; }
private:
	vector<SpriteType_t>	m_TargetList;
//	DWORD	m_Current;
};

class GQuestPartyDissectElement : public GQuestElement
{
public:
	struct MonsterTemplate
	{
		int min, max;
		vector<SpriteType_t>	m_TargetList;
	};
	GQuestPartyDissectElement() : m_Goal(0) { }
	string 						getElementName() const { return "PartyDissect"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::PARTY_DISSECT; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestPartyDissectElement*	makeElement(XMLTree* pTree);

	DWORD	getGoal() const { return m_Goal; }
	vector<SpriteType_t>*	getTargetList(int Level) const;

private:
	list<MonsterTemplate*>	m_MonsterSelecter;
	DWORD					m_TargetNum;
	DWORD					m_Goal;
};

extern GQuestPartyDissectElement g_PartyDissectElement;

#endif
