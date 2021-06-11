#ifndef __GQUEST_RANDOM_ELEMENT_H__
#define __GQUEST_RANDOM_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"
#include <vector>

class GQuestRandomElement : public GQuestElement
{
public:
	GQuestRandomElement() { }
	string		 				getElementName() const { return "Random"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestRandomElement*	makeElement(XMLTree* pTree);

private:
	vector<GQuestElement*>	m_Elements;
};

extern GQuestRandomElement g_RandomElement;

#endif
