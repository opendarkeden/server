#ifndef __GQUEST_GIVE_ADVANCEMENT_CLASS_EXP_ELEMENT_H__
#define __GQUEST_GIVE_ADVANCEMENT_CLASS_EXP_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveAdvancementClassExpElement : public GQuestElement
{
public:
	GQuestGiveAdvancementClassExpElement() : m_Amount(0) { }
	string 				getElementName() const { return "GiveAdvancementClassExp"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveAdvancementClassExpElement*	makeElement(XMLTree* pTree);

private:
	Exp_t m_Amount;;
};

extern GQuestGiveAdvancementClassExpElement g_GiveAdvancementClassExpElement;

#endif
