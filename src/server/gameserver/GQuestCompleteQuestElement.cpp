#include "GQuestCompleteQuestElement.h"
#include "GQuestStatus.h"
#include "PlayerCreature.h"

GQuestElement::ResultType GQuestCompleteQuestElement::checkCondition( PlayerCreature* pPC ) const
{
	GQuestStatus* pStatus = pPC->getGQuestManager()->getGQuestStatus( m_QuestID );
	if ( pStatus == NULL ) return FAIL;

	if ( pStatus->getStatus() == QuestStatusInfo::COMPLETE ) return OK;
	return FAIL;
}

GQuestCompleteQuestElement* GQuestCompleteQuestElement::makeElement(XMLTree* pTree)
{
	GQuestCompleteQuestElement* pRet = new GQuestCompleteQuestElement;

	pTree->GetAttribute("id", pRet->m_QuestID);

	return pRet;
}

GQuestCompleteQuestElement g_CompleteQuestElement;
