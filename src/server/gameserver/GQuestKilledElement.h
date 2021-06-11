#ifndef __GQUEST_KILLED_ELEMENT_H__
#define __GQUEST_KILLED_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestKilledMission : public GQuestMission
{
public:
	GQuestKilledMission(DWORD goal) : m_Current(0), m_Goal(goal) { }
	DWORD	getGoal() const { return m_Goal; }
	DWORD	getCurrent() const { return m_Current; }
	void	increase() { m_Current++; }

	string	getMissionName() const { return "KilledMission"; }
private:
	DWORD	m_Current;
	DWORD	m_Goal;
};

class GQuestKilledElement : public GQuestElement
{
public:
	GQuestKilledElement() : m_Goal(0) { }
	string 						getElementName() const { return "Killed"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::KILLED; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestKilledElement*	makeElement(XMLTree* pTree);

private:
	DWORD	m_Goal;
};

extern GQuestKilledElement g_KilledElement;

#endif
