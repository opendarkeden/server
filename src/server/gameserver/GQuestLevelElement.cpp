#include "GQuestLevelElement.h"
#include "PlayerCreature.h"

bool GQuestLevelMission::isSuccess( PlayerCreature* pPC )
{
	if ( pPC->getLevel() >= m_Goal )
		m_bSuccess = true;
	else
		m_bSuccess = false;

	return m_bSuccess;
}

GQuestElement::ResultType GQuestLevelElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->getLevel() <= m_Max && pPC->getLevel() >= m_Min ) return OK;
	else if ( m_Index == 0 ) return FAIL;

	if ( pPC->getLevel() < m_Min ) return WAIT;
	return FAIL;
}

GQuestElement::ResultType GQuestLevelElement::checkMission(GQuestMission* pStatus) const
{
	GQuestLevelMission* pLevelMission = dynamic_cast<GQuestLevelMission*>(pStatus);
	if ( pLevelMission == NULL ) return FAIL;

	if ( pLevelMission->isSuccess() ) return OK;
	return WAIT;
}

GQuestMission* GQuestLevelElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestLevelMission* pRet = new GQuestLevelMission(m_Min);
	return pRet;
}

GQuestLevelElement* GQuestLevelElement::makeElement(XMLTree* pTree)
{
	GQuestLevelElement* pRet = new GQuestLevelElement;

	pTree->GetAttribute("min", pRet->m_Min);
	pTree->GetAttribute("max", pRet->m_Max);

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestLevelElement g_LevelElement;
