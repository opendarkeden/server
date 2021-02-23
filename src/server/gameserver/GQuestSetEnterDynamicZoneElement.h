#ifndef __GQUEST_SET_ENTER_DYNAMIC_ZONE_ELEMENT_H__
#define __GQUEST_SET_ENTER_DYNAMIC_ZONE_ELEMENT_H__

#include "GQuestElement.h"
#include "Effect.h"

class GQuestSetEnterDynamicZoneElement : public GQuestElement
{
public:
	GQuestSetEnterDynamicZoneElement() : m_DynamicZoneID(0), m_CanEnter(0) { }
	string 				getElementName() const { return "SetDynamicZone"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestSetEnterDynamicZoneElement*	makeElement(XMLTree* pTree);

private:
	ZoneID_t	m_DynamicZoneID;
	BYTE		m_CanEnter;
};

extern GQuestSetEnterDynamicZoneElement g_SetEnterDynamicZoneElement;

#endif
