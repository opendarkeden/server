#ifndef __GQUEST_SAY_NPC_ELEMENT_H__
#define __GQUEST_SAY_NPC_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestSayNPCMission : public GQuestMission
{
public:
	GQuestSayNPCMission() : m_bMet(false) { }

	bool	isMet() const { return m_bMet; }
	void	meet() { m_bMet = true; }

	string	getMissionName() const { return "SayNPCMission"; }
private:
	bool	m_bMet;
};

class GQuestSayNPCElement : public GQuestElement
{
public:
	GQuestSayNPCElement() : m_Target(0) { }
	string 				getElementName() const { return "SayNPC"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::MEETNPC; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestSayNPCElement*	makeElement(XMLTree* pTree);

	NPCID_t getTarget() const { return m_Target; }

private:
	NPCID_t	m_Target;
};

extern GQuestSayNPCElement g_SayNPCElement;

#endif
