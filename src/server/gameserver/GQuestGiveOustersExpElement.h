#ifndef __GQUEST_GIVE_OUSTERS_EXP_ELEMENT_H__
#define __GQUEST_GIVE_OUSTERS_EXP_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveOustersExpElement : public GQuestElement
{
public:
	GQuestGiveOustersExpElement() : m_Amount(0) { }
	string 				getElementName() const { return "GiveOustersExp"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveOustersExpElement*	makeElement(XMLTree* pTree);

private:
	Exp_t m_Amount;;
};

extern GQuestGiveOustersExpElement g_GiveOustersExpElement;

#endif
