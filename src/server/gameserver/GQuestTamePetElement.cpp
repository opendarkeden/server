#include "GQuestTamePetElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestTamePetElement::checkMission(GQuestMission* pMission) const
{
	GQuestTamePetMission* pTamePetMission = dynamic_cast<GQuestTamePetMission*>(pMission);
	if ( pTamePetMission == NULL ) return FAIL;
	if ( pTamePetMission->isTamed() ) return OK;

	return WAIT;
}

GQuestMission* GQuestTamePetElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestTamePetMission* pMission = new GQuestTamePetMission;
	
	return pMission;
}

GQuestTamePetElement* GQuestTamePetElement::makeElement(XMLTree* pTree)
{
	GQuestTamePetElement* pRet = new GQuestTamePetElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestTamePetElement g_TamePetElement;
