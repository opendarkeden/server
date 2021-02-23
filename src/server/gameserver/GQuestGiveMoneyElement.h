#ifndef __GQUEST_GIVE_MONEY_ELEMENT_H__
#define __GQUEST_GIVE_MONEY_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveMoneyElement : public GQuestElement
{
public:
	GQuestGiveMoneyElement() : m_Amount(0) { }
	string 				getElementName() const { return "GiveMoney"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveMoneyElement*	makeElement(XMLTree* pTree);

private:
	Exp_t m_Amount;;
};

extern GQuestGiveMoneyElement g_GiveMoneyElement;

#endif
