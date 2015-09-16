#ifndef __GQUEST_TOUCH_WAY_POINT_ELEMENT_H__
#define __GQUEST_TOUCH_WAY_POINT_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestTouchWayPointMission : public GQuestMission
{
public:
	GQuestTouchWayPointMission() : m_bTouch(false) { }

	bool	isTouch() const { return m_bTouch; }
	void	touch() { m_bTouch = true; }

	string	getMissionName() const { return "TouchWayPointMission"; }
private:
	bool	m_bTouch;
};

class GQuestTouchWayPointElement : public GQuestElement
{
public:
	GQuestTouchWayPointElement() { }
	string 				getElementName() const { return "TouchWayPoint"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::TOUCH_WAY_POINT; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestTouchWayPointElement*	makeElement(XMLTree* pTree);

	friend class GQuestManager;

private:
	ZoneID_t	m_ZoneID;
	ZoneCoord_t	m_X, m_Y;
	MonsterType_t	m_Type;
	Dir_t		m_Dir;
};

extern GQuestTouchWayPointElement g_TouchWayPointElement;

#endif
