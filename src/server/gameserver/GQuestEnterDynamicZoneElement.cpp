#include "GQuestEnterDynamicZoneElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestEnterDynamicZoneElement::checkMission(GQuestMission* pMission) const
{
	GQuestEnterDynamicZoneMission* pEnterDynamicZoneMission = dynamic_cast<GQuestEnterDynamicZoneMission*>(pMission);
	if ( pEnterDynamicZoneMission == NULL ) return WAIT;
	if ( pEnterDynamicZoneMission->isEnter() ) return OK;

	return WAIT;
}

GQuestMission* GQuestEnterDynamicZoneElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestEnterDynamicZoneMission* pMission = new GQuestEnterDynamicZoneMission(m_TargetZoneID);
	
	return pMission;
}

GQuestEnterDynamicZoneElement* GQuestEnterDynamicZoneElement::makeElement(XMLTree* pTree)
{
	GQuestEnterDynamicZoneElement* pRet = new GQuestEnterDynamicZoneElement;

	int temp;
	Assert(pTree->GetAttribute("zoneid", temp));
	pRet->m_TargetZoneID = temp;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestEnterDynamicZoneElement g_EnterDynamicZoneElement;
