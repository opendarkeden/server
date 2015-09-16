#ifndef __GQUEST_FASTMOVE_ELEMENT_H__
#define __GQUEST_FASTMOVE_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestFastMoveMission : public GQuestMission
{
public:
	GQuestFastMoveMission() : m_bRide(false) { }

	bool	isRide() const { return m_bRide; }
	void	ride() { m_bRide = true; }

	string	getMissionName() const { return "FastMoveMission"; }
private:
	bool	m_bRide;
};

class GQuestFastMoveElement : public GQuestElement
{
public:
	GQuestFastMoveElement() { }
	string 				getElementName() const { return "FastMove"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::FASTMOVE; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestFastMoveElement*	makeElement(XMLTree* pTree);

private:
};

extern GQuestFastMoveElement g_FastMoveElement;

#endif
