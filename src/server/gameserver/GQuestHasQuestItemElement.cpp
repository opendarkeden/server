#include "GQuestHasQuestItemElement.h"
#include "GQuestInventory.h"
#include "GQuestManager.h"
#include "PlayerCreature.h"

GQuestElement::ResultType GQuestHasQuestItemElement::checkCondition( PlayerCreature* pPC ) const
{
	const list<ItemType_t>&	inventory = pPC->getGQuestManager()->getGQuestInventory().getItems();

	list<ItemType_t>::const_iterator itr = inventory.begin();
	list<ItemType_t>::const_iterator endItr = inventory.end();

	int count=0;

	for ( ; itr != endItr ; ++itr )
	{
		if ( (*itr) == m_Type )
		{
			++count;
			if ( count >= m_Num ) return OK;
		}
	}

	return FAIL;
}

GQuestHasQuestItemElement* GQuestHasQuestItemElement::makeElement(XMLTree* pTree)
{
	GQuestHasQuestItemElement* pRet = new GQuestHasQuestItemElement;

	DWORD type;
	Assert( pTree->GetAttribute("type", type) );
	pRet->m_Type = type;

	DWORD num;
	if ( pTree->GetAttribute("num", num) ) pRet->m_Num = num;

	return pRet;
}

GQuestHasQuestItemElement g_HasQuestItemElement;
