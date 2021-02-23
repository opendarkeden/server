#include "GQuestClearDynamicZoneElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestClearDynamicZoneElement::checkMission(GQuestMission* pMission) const
{
	GQuestClearDynamicZoneMission* pClearDynamicZoneMission = dynamic_cast<GQuestClearDynamicZoneMission*>(pMission);
	if ( pClearDynamicZoneMission == NULL ) return WAIT;
	if ( pClearDynamicZoneMission->isClear() ) return OK;

	return WAIT;
}

GQuestMission* GQuestClearDynamicZoneElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestClearDynamicZoneMission* pMission = new GQuestClearDynamicZoneMission(m_TargetZoneID);
	
	return pMission;
}

GQuestClearDynamicZoneElement* GQuestClearDynamicZoneElement::makeElement(XMLTree* pTree)
{
	GQuestClearDynamicZoneElement* pRet = new GQuestClearDynamicZoneElement;

	Assert(pTree->GetAttribute("zoneid", (int&)pRet->m_TargetZoneID));

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestClearDynamicZoneElement g_ClearDynamicZoneElement;
