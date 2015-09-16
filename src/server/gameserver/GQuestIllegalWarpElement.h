#ifndef __GQUEST_ILLEGAL_WARP_ELEMENT_H__
#define __GQUEST_ILLEGAL_WARP_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestIllegalWarpMission : public GQuestMission
{
public:
	GQuestIllegalWarpMission() : m_bRide(false) { }

	bool	isRide() const { return m_bRide; }
	void	ride() { m_bRide = true; }

	string	getMissionName() const { return "IllegalWarpMission"; }
private:
	bool	m_bRide;
};

class GQuestIllegalWarpElement : public GQuestElement
{
public:
	GQuestIllegalWarpElement() { }
	string 				getElementName() const { return "IllegalWarp"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::ILLEGAL_WARP; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestIllegalWarpElement*	makeElement(XMLTree* pTree);

private:
};

extern GQuestIllegalWarpElement g_IllegalWarpElement;

#endif
