#ifndef __GQUEST_BLOOD_DRAIN_ELEMENT_H__
#define __GQUEST_BLOOD_DRAIN_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestBloodDrainMission : public GQuestMission
{
public:
	GQuestBloodDrainMission(DWORD goal) : m_Goal(goal) { }
	DWORD	getGoal() const { return m_Goal; }
	DWORD	getCurrent() const { return m_NumArg; }
	void	increase() { m_NumArg++; }

	string	getMissionName() const { return "BloodDrainMission"; }
private:
//	DWORD	m_Current;
	DWORD	m_Goal;
};

class GQuestBloodDrainElement : public GQuestElement
{
public:
	GQuestBloodDrainElement() : m_Goal(0) { }
	string 						getElementName() const { return "BloodDrain"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::BLOODDRAIN; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestBloodDrainElement*	makeElement(XMLTree* pTree);

private:
	DWORD	m_Goal;
};

extern GQuestBloodDrainElement g_BloodDrainElement;

#endif
