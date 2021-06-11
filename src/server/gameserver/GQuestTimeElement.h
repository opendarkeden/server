#ifndef __GQUEST_TIME_ELEMENT_H__
#define __GQUEST_TIME_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include "Timeval.h"

class GQuestTimeMission : public GQuestMission
{
public:
	GQuestTimeMission(Timeval end) : m_EndTime(end) { }
	Timeval	getEndTime() const { return m_EndTime; }

	void updateArg() { m_NumArg = timediff( gCurrentTime, m_EndTime ).tv_sec / 60; }

	string	getMissionName() const { return "TimeMission"; }
private:
	Timeval	m_EndTime;
};

class GQuestTimeElement : public GQuestElement
{
public:
	GQuestTimeElement() : m_LimitMinutes(0) { }
	string 						getElementName() const { return "Time"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::TIMER; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*	makeInitMission(PlayerCreature* pPC) const;

	GQuestTimeElement*	makeElement(XMLTree* pTree);

private:
	DWORD	m_LimitMinutes;
};

extern GQuestTimeElement g_TimeElement;

#endif
