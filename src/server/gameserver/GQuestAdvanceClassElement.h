#ifndef __GQUEST_ADVANCE_CLASS_ELEMENT_H__
#define __GQUEST_ADVANCE_CLASS_ELEMENT_H__

#include "GQuestElement.h"

class GQuestAdvanceClassElement : public GQuestElement
{
public:
	GQuestAdvanceClassElement() { }
	string 				getElementName() const { return "AdvanceClass"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestAdvanceClassElement*	makeElement(XMLTree* pTree);
};

extern GQuestAdvanceClassElement g_AdvanceClassElement;

#endif
