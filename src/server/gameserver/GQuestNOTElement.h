#ifndef __GQUEST_NOT_ELEMENT_H__
#define __GQUEST_NOT_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include <vector>

class GQuestNOTElement : public GQuestElement
{
public:
	GQuestNOTElement() { }
	string 				getElementName() const { return "NOT"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestNOTElement*	makeElement(XMLTree* pTree);

private:
	vector<GQuestElement*>	m_Elements;
};

extern GQuestNOTElement g_NOTElement;

#endif
