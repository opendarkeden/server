#include "GQuestRaceElement.h"
#include "PlayerCreature.h"

GQuestElement::ResultType GQuestRaceElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->getRace() == m_Race ) return OK;
	return FAIL;
}

GQuestRaceElement* GQuestRaceElement::makeElement(XMLTree* pTree)
{
	GQuestRaceElement* pRet = new GQuestRaceElement;

	string race;
	pTree->GetAttribute("race", race);

	if ( race == "SLAYER" ) pRet->m_Race = RACE_SLAYER;
	else if ( race == "VAMPIRE" ) pRet->m_Race = RACE_VAMPIRE;
	else if ( race == "OUSTERS" ) pRet->m_Race = RACE_OUSTERS;
	else Assert(false);

	return pRet;
}

GQuestRaceElement g_RaceElement;
