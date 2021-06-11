#include "GQuestIllegalWarpElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestIllegalWarpElement::checkMission(GQuestMission* pMission) const
{
	GQuestIllegalWarpMission* pIllegalWarpMission = dynamic_cast<GQuestIllegalWarpMission*>(pMission);
	if ( pIllegalWarpMission == NULL ) return FAIL;
	if ( pIllegalWarpMission->isRide() ) return OK;

	return WAIT;
}

GQuestMission* GQuestIllegalWarpElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestIllegalWarpMission* pMission = new GQuestIllegalWarpMission;
	
	return pMission;
}

GQuestIllegalWarpElement* GQuestIllegalWarpElement::makeElement(XMLTree* pTree)
{
	GQuestIllegalWarpElement* pRet = new GQuestIllegalWarpElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestIllegalWarpElement g_IllegalWarpElement;
