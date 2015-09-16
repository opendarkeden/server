#ifndef __GQUEST_SKILL_LEVEL_ELEMENT_H__
#define __GQUEST_SKILL_LEVEL_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class SkillSlot;

class GQuestSkillLevelMission : public GQuestMission
{
public:
	GQuestSkillLevelMission(SkillLevel_t goal) : m_bSuccess(false), m_Goal(goal) { }
	DWORD	getGoal() const { return m_Goal; }

	bool	isSuccess(SkillSlot* pSkillSlot);
	bool	isSuccess() const { return m_bSuccess; }

	string	getMissionName() const { return "SkillLevelMission"; }
private:
	bool	m_bSuccess;
	SkillLevel_t	m_Goal;
};

class GQuestSkillLevelElement : public GQuestElement
{
public:
	GQuestSkillLevelElement() : m_Min(0) { }
	string		 				getElementName() const { return "SkillLevel"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::SKILL_LEVELUP; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestSkillLevelElement*	makeElement(XMLTree* pTree);

	int getMin() const { return m_Min; }

private:
	int	m_Min;
};

extern GQuestSkillLevelElement g_SkillLevelElement;

#endif
