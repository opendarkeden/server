#include "GQuestAddEffectElement.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "CreatureUtil.h"

GQuestElement::ResultType GQuestAddEffectElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( !pPC->isFlag( m_EffectClass ) )
	{
		addSimpleCreatureEffect( pPC, m_EffectClass );
	}

	return OK;
}

GQuestAddEffectElement* GQuestAddEffectElement::makeElement(XMLTree* pTree)
{
	GQuestAddEffectElement* pRet = new GQuestAddEffectElement;

	Assert(pTree->GetAttribute("effectclass", (int&)pRet->m_EffectClass));

	return pRet;
}

GQuestAddEffectElement g_AddEffectElement;
