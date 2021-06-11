#ifndef __GQUEST_GIVE_DOMAIN_EXP_ELEMENT_H__
#define __GQUEST_GIVE_DOMAIN_EXP_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveDomainExpElement : public GQuestElement
{
public:
	GQuestGiveDomainExpElement() : m_Amount(0) { }
	string 				getElementName() const { return "GiveDomainExp"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveDomainExpElement*	makeElement(XMLTree* pTree);

private:
	Exp_t m_Amount;;
};

extern GQuestGiveDomainExpElement g_GiveDomainExpElement;

#endif
