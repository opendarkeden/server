#ifndef __GQUEST_EVENT_PARTY_CRASH_ELEMENT_H__
#define __GQUEST_EVENT_PARTY_CRASH_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestEventPartyCrashMission : public GQuestMission
{
public:
	GQuestEventPartyCrashMission() : m_bMet(false) { }

	bool	isMet() const { return m_bMet; }
	void	meet() { m_bMet = true; }

	string	getMissionName() const { return "EventPartyCrashMission"; }
private:
	bool	m_bMet;
};

class GQuestEventPartyCrashElement : public GQuestElement
{
public:
	GQuestEventPartyCrashElement() : m_Target(0) { }
	string 				getElementName() const { return "EventPartyCrash"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::EVENT_PARTY_CRASH; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestEventPartyCrashElement*	makeElement(XMLTree* pTree);

	NPCID_t getTarget() const { return m_Target; }

private:
	NPCID_t	m_Target;
};

extern GQuestEventPartyCrashElement g_EventPartyCrashElement;

#endif
