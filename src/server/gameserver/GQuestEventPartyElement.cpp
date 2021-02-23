#include "GQuestEventPartyElement.h"
#include "Party.h"
#include "PlayerCreature.h"
#include "Assert.h"

GQuestElement::ResultType GQuestEventPartyElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->getPartyID() == 0 ) return WAIT;
	Party* pParty = g_pGlobalPartyManager->getParty( pPC->getPartyID() );
	if ( pParty == NULL ) return FAIL;
	if ( pParty->getSize() != 2 ) return FAIL;

	hash_map<string, Creature*> members = pParty->getMemberMap();
	hash_map<string, Creature*>::iterator itr = members.begin();

	for ( ; itr != members.end() ; ++itr )
	{
		if ( itr->second != pPC )
		{
			if ( itr->second->getLevel() < 25 ) return OK;
			return FAIL;
		}
	}

	return FAIL;
}

GQuestElement::ResultType GQuestEventPartyElement::checkMission(GQuestMission* pMission) const
{
	GQuestEventPartyMission* pEventPartyMission = dynamic_cast<GQuestEventPartyMission*>(pMission);
	if ( pEventPartyMission == NULL ) return FAIL;
	if ( pEventPartyMission->isMet() ) return OK;

	return WAIT;
}

GQuestMission* GQuestEventPartyElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestEventPartyMission* pMission = new GQuestEventPartyMission;
	
	return pMission;
}

GQuestEventPartyElement* GQuestEventPartyElement::makeElement(XMLTree* pTree)
{
	GQuestEventPartyElement* pRet = new GQuestEventPartyElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestEventPartyElement g_EventPartyElement;
