#include "GQuestTravelElement.h"
#include "GQuestCheckPoint.h"
#include "Assert.h"
#include "PlayerCreature.h"
#include "MonsterInfo.h"

void GQuestTravelMission::updateStr()
{
	m_StrArg="";
	vector<DWORD>::iterator itr = m_TargetList.begin();
	for ( ; itr != m_TargetList.end() ; ++itr )
	{
		if ( !isVisited(*itr) )
			m_StrArg += GQuestCheckPoint::Instance().getStringFromWayPoint(*itr) + ",";
	}
}

GQuestElement::ResultType GQuestTravelElement::checkMission(GQuestMission* pMission) const
{
	GQuestTravelMission* pTravelMission = dynamic_cast<GQuestTravelMission*>(pMission);
	if ( pTravelMission == NULL ) return FAIL;

	if ( pTravelMission->getTargetList().size() <= pTravelMission->getVisitedList().size() ) return OK;

	return WAIT;
}

GQuestMission* GQuestTravelElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestTravelMission* pMission = new GQuestTravelMission;
	pMission->m_StrArg = GQuestCheckPoint::Instance().getTargetList( pPC->getRace(), pPC->getLevel(), m_Grade, m_BaseNum, pMission->getTargetList() );
	
	return pMission;
}

GQuestTravelElement* GQuestTravelElement::makeElement(XMLTree* pTree)
{
	GQuestTravelElement* pRet = new GQuestTravelElement;

	Assert( pTree->GetAttribute("grade", pRet->m_Grade) );
	Assert( pTree->GetAttribute("basenum", pRet->m_BaseNum) );

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestTravelElement g_TravelElement;
