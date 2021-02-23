#include "GQuestFastMoveElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestFastMoveElement::checkMission(GQuestMission* pMission) const
{
	GQuestFastMoveMission* pFastMoveMission = dynamic_cast<GQuestFastMoveMission*>(pMission);
	if ( pFastMoveMission == NULL ) return FAIL;
	if ( pFastMoveMission->isRide() ) return OK;

	return WAIT;
}

GQuestMission* GQuestFastMoveElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestFastMoveMission* pMission = new GQuestFastMoveMission;
	
	return pMission;
}

GQuestFastMoveElement* GQuestFastMoveElement::makeElement(XMLTree* pTree)
{
	GQuestFastMoveElement* pRet = new GQuestFastMoveElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestFastMoveElement g_FastMoveElement;
