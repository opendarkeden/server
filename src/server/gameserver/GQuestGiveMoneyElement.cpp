#include "GQuestGiveMoneyElement.h"
#include "PlayerCreature.h"
#include "GCModifyInformation.h"
#include "GCSystemMessage.h"
#include "Player.h"
#include <cstdio>

GQuestElement::ResultType GQuestGiveMoneyElement::checkCondition(PlayerCreature* pPC ) const
{
	GCModifyInformation gcMI;
	pPC->increaseGoldEx(m_Amount);
	gcMI.addLongData(MODIFY_GOLD, pPC->getGold());
	pPC->getPlayer()->sendPacket(&gcMI);

	GCSystemMessage gcSM;
	char buffer[256];
	if (pPC->isSlayer() )
	{
		sprintf(buffer, "%ld·¹ÀÌ¸¦ È¹µæÇß½À´Ï´Ù.", m_Amount);
		gcSM.setMessage(buffer);
		pPC->getPlayer()->sendPacket(&gcSM);
	}
	else if (pPC->isVampire() )
	{
		sprintf(buffer, "%ld°Öµå¸¦ È¹µæÇß½À´Ï´Ù.", m_Amount);
		gcSM.setMessage(buffer);
		pPC->getPlayer()->sendPacket(&gcSM);
	}
	else if (pPC->isOusters() )
	{
		sprintf(buffer, "%ldÀÚµå¸¦ È¹µæÇß½À´Ï´Ù.", m_Amount);
		gcSM.setMessage(buffer);
		pPC->getPlayer()->sendPacket(&gcSM);
	}

	return OK;
}

GQuestGiveMoneyElement* GQuestGiveMoneyElement::makeElement(XMLTree* pTree)
{
	GQuestGiveMoneyElement* pRet = new GQuestGiveMoneyElement;

	pTree->GetAttribute("amount", pRet->m_Amount);

	return pRet;
}

GQuestGiveMoneyElement g_GiveMoneyElement;
