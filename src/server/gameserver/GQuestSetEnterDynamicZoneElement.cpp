#include "GQuestSetEnterDynamicZoneElement.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "CreatureUtil.h"

GQuestElement::ResultType GQuestSetEnterDynamicZoneElement::checkCondition( PlayerCreature* pPC ) const
{
	pPC->getGQuestManager()->setEnterDynamicZone( m_DynamicZoneID, m_CanEnter );

	return OK;
}

GQuestSetEnterDynamicZoneElement* GQuestSetEnterDynamicZoneElement::makeElement(XMLTree* pTree)
{
	GQuestSetEnterDynamicZoneElement* pRet = new GQuestSetEnterDynamicZoneElement;

	int temp = 0;
	Assert(pTree->GetAttribute("zoneid", temp));
	pRet->m_DynamicZoneID = temp;
	Assert(pTree->GetAttribute("canenter", temp));
	pRet->m_CanEnter = temp;

	cout << (int)pRet->m_DynamicZoneID << endl;
	cout << (int)pRet->m_CanEnter << endl;

	return pRet;
}

GQuestSetEnterDynamicZoneElement g_SetEnterDynamicZoneElement;
