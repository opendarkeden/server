#include "GQuestAdvancementClassLevelElement.h"
#include "PlayerCreature.h"

bool GQuestAdvancementClassLevelMission::isSuccess( PlayerCreature* pPC )
{
	if ( pPC->getAdvancementClassLevel() >= m_Goal )
		m_bSuccess = true;
	else
		m_bSuccess = false;

	return m_bSuccess;
}

GQuestElement::ResultType GQuestAdvancementClassLevelElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->getAdvancementClassLevel() <= m_Max && pPC->getAdvancementClassLevel() >= m_Min ) return OK;
	else if ( m_Index == 0 ) return FAIL;

	if ( pPC->getAdvancementClassLevel() < m_Min ) return WAIT;
	return FAIL;
}

GQuestElement::ResultType GQuestAdvancementClassLevelElement::checkMission(GQuestMission* pStatus) const
{
	GQuestAdvancementClassLevelMission* pAdvancementClassLevelMission = dynamic_cast<GQuestAdvancementClassLevelMission*>(pStatus);
	if ( pAdvancementClassLevelMission == NULL ) return FAIL;

	if ( pAdvancementClassLevelMission->isSuccess() ) return OK;
	return WAIT;
}

GQuestMission* GQuestAdvancementClassLevelElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestAdvancementClassLevelMission* pRet = new GQuestAdvancementClassLevelMission(m_Min);
	return pRet;
}

GQuestAdvancementClassLevelElement* GQuestAdvancementClassLevelElement::makeElement(XMLTree* pTree)
{
	GQuestAdvancementClassLevelElement* pRet = new GQuestAdvancementClassLevelElement;

	pTree->GetAttribute("min", pRet->m_Min);
	pTree->GetAttribute("max", pRet->m_Max);

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestAdvancementClassLevelElement g_AdvancementClassLevelElement;
