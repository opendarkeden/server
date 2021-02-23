#ifndef __GQUEST_RACE_ELEMENT_H__
#define __GQUEST_RACE_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestRaceElement : public GQuestElement
{
public:
	GQuestRaceElement() : m_Race(RACE_SLAYER) { }
	string		 				getElementName() const { return "Race"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestRaceElement*	makeElement(XMLTree* pTree);

	Race_t getRace() const { return m_Race; }

private:
	Race_t	m_Race;
};

extern GQuestRaceElement g_RaceElement;

#endif
