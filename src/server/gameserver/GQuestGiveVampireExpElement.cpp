#include "GQuestGiveVampireExpElement.h"
#include "PlayerCreature.h"
#include "Vampire.h"
#include "skill/SkillUtil.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

GQuestElement::ResultType GQuestGiveVampireExpElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( !pPC->isVampire() ) return FAIL;

	GCModifyInformation gcMI;
	Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
	increaseVampExp( pVampire, m_Amount, gcMI );
	pVampire->getPlayer()->sendPacket( &gcMI );

	GCSystemMessage gcSM;
	gcSM.setMessage("获得经验值.");
	pPC->getPlayer()->sendPacket( &gcSM );

	return OK;
}

GQuestGiveVampireExpElement* GQuestGiveVampireExpElement::makeElement(XMLTree* pTree)
{
	GQuestGiveVampireExpElement* pRet = new GQuestGiveVampireExpElement;

	pTree->GetAttribute("amount", pRet->m_Amount);

	return pRet;
}

GQuestGiveVampireExpElement g_GiveVampireExpElement;
