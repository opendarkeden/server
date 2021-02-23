#include "GQuestEventPartyCrashElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestEventPartyCrashElement::checkMission(GQuestMission* pMission) const
{
	GQuestEventPartyCrashMission* pEventPartyCrashMission = dynamic_cast<GQuestEventPartyCrashMission*>(pMission);
	if ( pEventPartyCrashMission == NULL ) return FAIL;
	if ( pEventPartyCrashMission->isMet() ) return OK;

	return WAIT;
}

GQuestMission* GQuestEventPartyCrashElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestEventPartyCrashMission* pMission = new GQuestEventPartyCrashMission;
	
	return pMission;
}

GQuestEventPartyCrashElement* GQuestEventPartyCrashElement::makeElement(XMLTree* pTree)
{
	GQuestEventPartyCrashElement* pRet = new GQuestEventPartyCrashElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestEventPartyCrashElement g_EventPartyCrashElement;
