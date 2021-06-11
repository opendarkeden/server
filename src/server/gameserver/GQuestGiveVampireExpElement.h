#ifndef __GQUEST_GIVE_VAMPIRE_EXP_ELEMENT_H__
#define __GQUEST_GIVE_VAMPIRE_EXP_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveVampireExpElement : public GQuestElement
{
public:
	GQuestGiveVampireExpElement() : m_Amount(0) { }
	string 				getElementName() const { return "GiveVampireExp"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveVampireExpElement*	makeElement(XMLTree* pTree);

private:
	Exp_t m_Amount;;
};

extern GQuestGiveVampireExpElement g_GiveVampireExpElement;

#endif
