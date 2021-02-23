#include "GQuestSkillLevelElement.h"
#include "PlayerCreature.h"
#include "skill/SkillSlot.h"

bool GQuestSkillLevelMission::isSuccess( SkillSlot* pSkillSlot )
{
	if ( pSkillSlot->getExpLevel() >= m_Goal )
		m_bSuccess = true;
	else
		m_bSuccess = false;

	return m_bSuccess;
}

GQuestElement::ResultType GQuestSkillLevelElement::checkMission(GQuestMission* pStatus) const
{
	GQuestSkillLevelMission* pSkillLevelMission = dynamic_cast<GQuestSkillLevelMission*>(pStatus);
	if ( pSkillLevelMission == NULL ) return FAIL;

	if ( pSkillLevelMission->isSuccess() ) return OK;
	return WAIT;
}

GQuestMission* GQuestSkillLevelElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestSkillLevelMission* pRet = new GQuestSkillLevelMission(m_Min);
	return pRet;
}

GQuestSkillLevelElement* GQuestSkillLevelElement::makeElement(XMLTree* pTree)
{
	GQuestSkillLevelElement* pRet = new GQuestSkillLevelElement;

	pTree->GetAttribute("min", pRet->m_Min);

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestSkillLevelElement g_SkillLevelElement;
