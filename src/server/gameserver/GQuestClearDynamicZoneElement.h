#ifndef __GQUEST_CLEAR_DYNAMIC_ZONE_ELEMENT_H__
#define __GQUEST_CLEAR_DYNAMIC_ZONE_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestClearDynamicZoneMission : public GQuestMission
{
public:
	GQuestClearDynamicZoneMission(ZoneID_t targetZoneID) : m_bClear(false), m_TargetZoneID(targetZoneID) { }

	bool	isClear() const { return m_bClear; }
	void	clear(ZoneID_t zoneID) { if ( m_TargetZoneID == zoneID ) m_bClear = true; }

	string	getMissionName() const { return "ClearDynamicZoneMission"; }
private:
	bool	m_bClear;
	ZoneID_t	m_TargetZoneID;
};

class GQuestClearDynamicZoneElement : public GQuestElement
{
public:
	GQuestClearDynamicZoneElement() { }
	string 				getElementName() const { return "ClearDynamicZone"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::CLEAR_DYNAMIC_ZONE; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestClearDynamicZoneElement*	makeElement(XMLTree* pTree);

private:
	ZoneID_t	m_TargetZoneID;
};

extern GQuestClearDynamicZoneElement g_ClearDynamicZoneElement;

#endif
