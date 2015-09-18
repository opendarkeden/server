#include "GQuestTouchWayPointElement.h"
#include "MonsterCorpse.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Assert1.h"

GQuestElement::ResultType GQuestTouchWayPointElement::checkMission(GQuestMission* pMission) const
{
	GQuestTouchWayPointMission* pTouchWayPointMission = dynamic_cast<GQuestTouchWayPointMission*>(pMission);
	if (pTouchWayPointMission == NULL ) return FAIL;
	if (pTouchWayPointMission->isTouch() ) return OK;

	return WAIT;
}

GQuestMission* GQuestTouchWayPointElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestTouchWayPointMission* pMission = new GQuestTouchWayPointMission;
	
	return pMission;
}

GQuestTouchWayPointElement* GQuestTouchWayPointElement::makeElement(XMLTree* pTree)
{
	GQuestTouchWayPointElement* pRet = new GQuestTouchWayPointElement;

	Assert(pTree->GetAttribute("zoneid", (DWORD&)pRet->m_ZoneID));
	Assert(pTree->GetAttribute("x", (DWORD&)pRet->m_X));
	Assert(pTree->GetAttribute("y", (DWORD&)pRet->m_Y));
	Assert(pTree->GetAttribute("type", (DWORD&)pRet->m_Type));
	Assert(pTree->GetAttribute("dir", (DWORD&)pRet->m_Dir));

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	MonsterCorpse* pMonsterCorpse = new MonsterCorpse(pRet->m_Type, " ", pRet->m_Dir);
	pMonsterCorpse->setTreasureCount(255);
	Zone* pZone = getZoneByZoneID(pRet->m_ZoneID);
	Assert(pZone != NULL);
	pZone->registerObject(pMonsterCorpse);
	pZone->addItem(pMonsterCorpse, pRet->m_X, pRet->m_Y, true, 0xffffffff);

	Assert(pMonsterCorpse->getX() == pRet->m_X);
	Assert(pMonsterCorpse->getY() == pRet->m_Y);

	return pRet;
}

GQuestTouchWayPointElement g_TouchWayPointElement;
