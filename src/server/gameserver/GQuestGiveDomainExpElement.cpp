#include "GQuestGiveDomainExpElement.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "skill/SkillUtil.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

GQuestElement::ResultType GQuestGiveDomainExpElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( !pPC->isSlayer() ) return FAIL;

	GCModifyInformation gcMI;
	Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
	increaseDomainExp(pSlayer, pSlayer->getHighestSkillDomain(), m_Amount, gcMI );
	pSlayer->getPlayer()->sendPacket( &gcMI );

	GCSystemMessage gcSM;
	gcSM.setMessage("获得该区域的经验值.");
	pSlayer->getPlayer()->sendPacket( &gcSM );

	return OK;
}

GQuestGiveDomainExpElement* GQuestGiveDomainExpElement::makeElement(XMLTree* pTree)
{
	GQuestGiveDomainExpElement* pRet = new GQuestGiveDomainExpElement;

	pTree->GetAttribute("amount", pRet->m_Amount);

	return pRet;
}

GQuestGiveDomainExpElement g_GiveDomainExpElement;
