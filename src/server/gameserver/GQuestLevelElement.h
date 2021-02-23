#ifndef __GQUEST_LEVEL_ELEMENT_H__
#define __GQUEST_LEVEL_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestLevelMission : public GQuestMission
{
public:
	GQuestLevelMission(Level_t goal) : m_bSuccess(false), m_Goal(goal) { }
	DWORD	getGoal() const { return m_Goal; }

	bool	isSuccess(PlayerCreature* pPC);
	bool	isSuccess() const { return m_bSuccess; }

	string	getMissionName() const { return "LevelMission"; }
private:
	bool	m_bSuccess;
	Level_t	m_Goal;
};

class GQuestLevelElement : public GQuestElement
{
public:
	GQuestLevelElement() : m_Min(0), m_Max(65535) { }
	string		 				getElementName() const { return "Level"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::LEVELUP; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestLevelElement*	makeElement(XMLTree* pTree);

	int getMin() const { return m_Min; }
	int getMax() const { return m_Max; }

private:
	int	m_Min, m_Max;
};

extern GQuestLevelElement g_LevelElement;

#endif
