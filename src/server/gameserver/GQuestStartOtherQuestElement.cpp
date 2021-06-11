#include "GQuestStartOtherQuestElement.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"

GQuestElement::ResultType GQuestStartOtherQuestElement::checkCondition( PlayerCreature* pPC ) const
{
	pPC->getGQuestManager()->accept( m_QuestID );
	return OK;
}

GQuestStartOtherQuestElement* GQuestStartOtherQuestElement::makeElement(XMLTree* pTree)
{
	GQuestStartOtherQuestElement* pRet = new GQuestStartOtherQuestElement;

	Assert(pTree->GetAttribute("id", pRet->m_QuestID));

	return pRet;
}

GQuestStartOtherQuestElement g_StartOtherQuestElement;
