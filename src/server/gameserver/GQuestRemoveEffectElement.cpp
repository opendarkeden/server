#include "GQuestRemoveEffectElement.h"
#include "PlayerCreature.h"
#include "Zone.h"

GQuestElement::ResultType GQuestRemoveEffectElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->isFlag( m_EffectClass ) )
	{
		Effect* pEffect = pPC->findEffect( m_EffectClass );
		if ( pEffect != NULL )
		{
			pEffect->setDeadline(0);
		}
	}

	return OK;
}

GQuestRemoveEffectElement* GQuestRemoveEffectElement::makeElement(XMLTree* pTree)
{
	GQuestRemoveEffectElement* pRet = new GQuestRemoveEffectElement;

	Assert(pTree->GetAttribute("effectclass", (int&)pRet->m_EffectClass));

	return pRet;
}

GQuestRemoveEffectElement g_RemoveEffectElement;
