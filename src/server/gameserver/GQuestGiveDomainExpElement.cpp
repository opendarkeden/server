#include "GQuestGiveDomainExpElement.h"

#include "GCModifyInformation.h"
#include "GCSystemMessage.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "skill/SkillUtil.h"

GQuestElement::ResultType GQuestGiveDomainExpElement::checkCondition(PlayerCreature* pPC) const {
    if (!pPC->isSlayer())
        return FAIL;

    GCModifyInformation gcMI;
    Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
    increaseDomainExp(pSlayer, pSlayer->getHighestSkillDomain(), m_Amount, gcMI);
    pSlayer->getPlayer()->sendPacket(&gcMI);

    GCSystemMessage gcSM;
    gcSM.setMessage("삿돤맡혐堵돨쒔駱令.");
    pSlayer->getPlayer()->sendPacket(&gcSM);

    return OK;
}

GQuestGiveDomainExpElement* GQuestGiveDomainExpElement::makeElement(XMLTree* pTree) {
    GQuestGiveDomainExpElement* pRet = new GQuestGiveDomainExpElement;

    pTree->GetAttribute("amount", pRet->m_Amount);

    return pRet;
}

GQuestGiveDomainExpElement g_GiveDomainExpElement;
