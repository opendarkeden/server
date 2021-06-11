#include "GQuestBloodDrainElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestBloodDrainElement::checkMission(GQuestMission* pMission) const
{
	GQuestBloodDrainMission* pBloodDrainMission = dynamic_cast<GQuestBloodDrainMission*>(pMission);
	if ( pBloodDrainMission == NULL ) return FAIL;

	if ( pBloodDrainMission->getCurrent() >= m_Goal ) return OK;

	return WAIT;
}

GQuestMission* GQuestBloodDrainElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestBloodDrainMission* pMission = new GQuestBloodDrainMission(m_Goal);
	
	return pMission;
}

GQuestBloodDrainElement* GQuestBloodDrainElement::makeElement(XMLTree* pTree)
{
	GQuestBloodDrainElement* pRet = new GQuestBloodDrainElement;

	Assert( pTree->GetAttribute("num", pRet->m_Goal) );

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestBloodDrainElement g_BloodDrainElement;
