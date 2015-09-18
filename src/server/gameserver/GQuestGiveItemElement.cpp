#include "GQuestGiveItemElement.h"
#include "PlayerCreature.h"
#include "GQuestInventory.h"
#include "Player.h"
#include "Treasure.h"
#include "ItemUtil.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "GCCreateItem.h"
#include "GCSystemMessage.h"
#include "PacketUtil.h"
#include "Zone.h"

GQuestElement::ResultType GQuestGiveItemElement::checkCondition(PlayerCreature* pPC ) const {
	Item* pItem = g_pItemFactoryManager->createItem(m_ItemClass, m_ItemType, m_Option);
	if (pItem == NULL ) return FAIL;
	
	pItem->setNum(m_Num);
	Inventory* pInventory = pPC->getInventory();
	TPOINT pt;
	pPC->getZone()->registerObject(pItem);
	setItemGender(pItem, (pPC->getSex()==FEMALE)?GENDER_FEMALE:GENDER_MALE);

	if (!pInventory->addItem(pItem, pt ) )
	{
		pt = pPC->getZone()->addItem(pItem, pPC->getX(), pPC->getY());
		if (pt.x == -1 )
		{
			SAFE_DELETE(pItem);
		}
		else
		{
            DWORD storageID = pPC->getZone()->getZoneID();
            pItem->create("", STORAGE_ZONE, storageID, pt.x, pt.y);
		}
	}
	else
	{
		pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
		GCCreateItem gcCreateItem;
		makeGCCreateItem(&gcCreateItem, pItem, pt.x, pt.y);
		pPC->getPlayer()->sendPacket(&gcCreateItem);

		// ItemTraceLog 를 남긴다
		if (pItem->isTraceItem() )
		{
			remainTraceLog(pItem, "GQuest", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
			remainTraceLogNew(pItem, pPC->getName(), ITL_GET, ITLD_EVENTNPC, pPC->getZone()->getZoneID());
		}
	}
	
	GCSystemMessage gcSM;
	gcSM.setMessage("아이템을 획득했습니다.");
	pPC->getPlayer()->sendPacket(&gcSM);

	return OK;
}

GQuestGiveItemElement* GQuestGiveItemElement::makeElement(XMLTree* pTree)
{
	GQuestGiveItemElement* pRet = new GQuestGiveItemElement;

	string iClass;
	Assert(pTree->GetAttribute("class", iClass ));

	pRet->m_ItemClass = TreasureItemClass::getItemClassFromString(iClass);

	DWORD itemType;
	Assert(pTree->GetAttribute("type", itemType ));

	pRet->m_ItemType = itemType;

	string option;
	if (pTree->GetAttribute("option", option) )
	{
		makeOptionList(option, pRet->m_Option);
	}

	if (!pTree->GetAttribute("num", (int&)pRet->m_Num) ) pRet->m_Num=1;

	return pRet;
}

GQuestGiveItemElement g_GiveItemElement;
