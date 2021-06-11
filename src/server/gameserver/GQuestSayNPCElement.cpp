#include "GQuestSayNPCElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestSayNPCElement::checkMission(GQuestMission* pMission) const
{
	GQuestSayNPCMission* pSayNPCMission = dynamic_cast<GQuestSayNPCMission*>(pMission);
	if ( pSayNPCMission == NULL ) return FAIL;
	if ( pSayNPCMission->isMet() ) return OK;

	return WAIT;
}

GQuestMission* GQuestSayNPCElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestSayNPCMission* pMission = new GQuestSayNPCMission;
	
	return pMission;
}

GQuestSayNPCElement* GQuestSayNPCElement::makeElement(XMLTree* pTree)
{
	GQuestSayNPCElement* pRet = new GQuestSayNPCElement;

	int target;
	Assert( pTree->GetAttribute("target", target) );
	pRet->m_Target = target;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestSayNPCElement g_SayNPCElement;
