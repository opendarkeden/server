#ifndef __GQUEST_ADD_EFFECT_ELEMENT_H__
#define __GQUEST_ADD_EFFECT_ELEMENT_H__

#include "GQuestElement.h"
#include "Effect.h"

class GQuestAddEffectElement : public GQuestElement
{
public:
	GQuestAddEffectElement() : m_EffectClass(Effect::EFFECT_CLASS_MAX) { }
	string 				getElementName() const { return "AddEffect"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestAddEffectElement*	makeElement(XMLTree* pTree);

private:
	Effect::EffectClass	m_EffectClass;
};

extern GQuestAddEffectElement g_AddEffectElement;

#endif
