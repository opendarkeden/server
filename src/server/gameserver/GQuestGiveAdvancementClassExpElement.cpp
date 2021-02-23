#include "GQuestGiveAdvancementClassExpElement.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "skill/SkillUtil.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

GQuestElement::ResultType GQuestGiveAdvancementClassExpElement::checkCondition( PlayerCreature* pPC ) const
{
	pPC->increaseAdvancementClassExp( m_Amount );

	return OK;
}

GQuestGiveAdvancementClassExpElement* GQuestGiveAdvancementClassExpElement::makeElement(XMLTree* pTree)
{
	GQuestGiveAdvancementClassExpElement* pRet = new GQuestGiveAdvancementClassExpElement;

	pTree->GetAttribute("amount", pRet->m_Amount);

	return pRet;
}

GQuestGiveAdvancementClassExpElement g_GiveAdvancementClassExpElement;
