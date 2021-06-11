#include "GQuestWarpElement.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ZoneUtil.h"
#include "EventTransport.h"

GQuestElement::ResultType GQuestWarpElement::checkCondition( PlayerCreature* pPC ) const
{
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());

	EventTransport* pEventTransport = new EventTransport(pGamePlayer);

	pEventTransport->setDeadline( 0 );
	pEventTransport->setTargetZone( m_ZoneID, m_X, m_Y );

	pGamePlayer->addEvent(pEventTransport);

	return OK;
}

GQuestWarpElement* GQuestWarpElement::makeElement(XMLTree* pTree)
{
	GQuestWarpElement* pRet = new GQuestWarpElement;

	Assert( pTree->GetAttribute("zoneid", pRet->m_ZoneID) );
	Assert( pTree->GetAttribute("x", pRet->m_X) );
	Assert( pTree->GetAttribute("y", pRet->m_Y) );

	return pRet;
}

GQuestWarpElement g_WarpElement;
