#ifndef __GQUEST_REMOVE_EFFECT_ELEMENT_H__
#define __GQUEST_REMOVE_EFFECT_ELEMENT_H__

#include "GQuestElement.h"
#include "Effect.h"

class GQuestRemoveEffectElement : public GQuestElement
{
public:
	GQuestRemoveEffectElement() : m_EffectClass(Effect::EFFECT_CLASS_MAX) { }
	string 				getElementName() const { return "RemoveEffect"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestRemoveEffectElement*	makeElement(XMLTree* pTree);

private:
	Effect::EffectClass	m_EffectClass;
};

extern GQuestRemoveEffectElement g_RemoveEffectElement;

#endif
