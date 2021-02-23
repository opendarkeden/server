#include "GQuestGiveQuestItemElement.h"
#include "PlayerCreature.h"
#include "GQuestInventory.h"
#include "Player.h"
#include "Gpackets/GCSystemMessage.h"

#include "DB.h"

GQuestElement::ResultType GQuestGiveQuestItemElement::checkCondition( PlayerCreature* pPC ) const
{
	GQuestInventory& inventory = pPC->getGQuestManager()->getGQuestInventory();
	inventory.getItems().push_back(m_ItemType);
	pPC->getPlayer()->sendPacket(inventory.getInventoryPacket());

	GCSystemMessage gcSM;
	gcSM.setMessage("获得任务道具.");
	pPC->getPlayer()->sendPacket( &gcSM );

	if ( m_bSave )
	{
		Statement* pStmt = NULL;
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("INSERT INTO GQuestItemObject(ItemType, OwnerID) VALUES (%u, '%s')",
					m_ItemType, pPC->getName().c_str());
			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

	return OK;
}

GQuestGiveQuestItemElement* GQuestGiveQuestItemElement::makeElement(XMLTree* pTree)
{
	GQuestGiveQuestItemElement* pRet = new GQuestGiveQuestItemElement;

	DWORD itemType;
	if ( pTree->GetAttribute("id", itemType ) ) pRet->m_ItemType = itemType;
	pTree->GetAttribute("save", pRet->m_bSave);

	return pRet;
}

GQuestGiveQuestItemElement g_GiveQuestItemElement;
