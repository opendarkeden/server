#ifndef __GQUEST_OR_ELEMENT_H__
#define __GQUEST_OR_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include <vector>

class GQuestORElement : public GQuestElement
{
public:
	GQuestORElement() { }
	string		 				getElementName() const { return "OR"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestORElement*	makeElement(XMLTree* pTree);

private:
	vector<GQuestElement*>	m_Elements;
};

extern GQuestORElement g_ORElement;

#endif
