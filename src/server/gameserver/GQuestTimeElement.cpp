#include "GQuestTimeElement.h"
#include "GQuestManager.h"
#include "Assert.h"

GQuestElement::ResultType GQuestTimeElement::checkMission(GQuestMission* pMission) const
{
	GQuestTimeMission* pTimeMission = dynamic_cast<GQuestTimeMission*>(pMission);
	if ( pTimeMission == NULL ) return FAIL;

	Timeval endTime = pTimeMission->getEndTime();
	if ( gCurrentTime > endTime ) return OK;

	return WAIT;
}

GQuestMission* GQuestTimeElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestTimeMission* pMission = NULL;
	
	Timeval endTime;
	getCurrentTime(endTime);
	endTime.tv_sec += 60*(int)m_LimitMinutes;
	pMission = new GQuestTimeMission(endTime);
	pMission->updateArg();

	return pMission;
}

GQuestTimeElement* GQuestTimeElement::makeElement(XMLTree* pTree)
{
	GQuestTimeElement* pRet = new GQuestTimeElement;

	Assert( pTree->GetAttribute("limit", pRet->m_LimitMinutes) );

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestTimeElement g_TimeElement;
