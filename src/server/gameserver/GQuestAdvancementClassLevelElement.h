#ifndef __GQUEST_ADVANCEMENT_LEVEL_ELEMENT_H__
#define __GQUEST_ADVANCEMENT_LEVEL_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestAdvancementClassLevelMission : public GQuestMission
{
public:
	GQuestAdvancementClassLevelMission(Level_t goal) : m_bSuccess(false), m_Goal(goal) { }
	DWORD	getGoal() const { return m_Goal; }

	bool	isSuccess(PlayerCreature* pPC);
	bool	isSuccess() const { return m_bSuccess; }

	string	getMissionName() const { return "AdvancementClassLevelMission"; }
private:
	bool	m_bSuccess;
	Level_t	m_Goal;
};

class GQuestAdvancementClassLevelElement : public GQuestElement
{
public:
	GQuestAdvancementClassLevelElement() : m_Min(0), m_Max(65535) { }
	string		 				getElementName() const { return "AdvancementClassLevel"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::ADVANCEMENT_LEVELUP; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestAdvancementClassLevelElement*	makeElement(XMLTree* pTree);

	int getMin() const { return m_Min; }
	int getMax() const { return m_Max; }

private:
	int	m_Min, m_Max;
};

extern GQuestAdvancementClassLevelElement g_AdvancementClassLevelElement;

#endif
