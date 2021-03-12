////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRewardEventQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRewardEventQuest.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "PacketUtil.h"
#include "ItemUtil.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCNPCAsk.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCCreateItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionRewardEventQuest::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ScriptID[0] = propertyBuffer.getPropertyInt("Level1");
		m_ScriptID[1] = propertyBuffer.getPropertyInt("Level2");
		m_ScriptID[2] = propertyBuffer.getPropertyInt("Level3");
		m_ScriptID[3] = propertyBuffer.getPropertyInt("Level4");
		m_ScriptID[4] = propertyBuffer.getPropertyInt("Level5");
		m_CounterScriptID = propertyBuffer.getPropertyInt("Counter");
		m_CancelScriptID = propertyBuffer.getPropertyInt("Cancel");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionRewardEventQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	if ( pPC->getQuestItem() != NULL )
	{
		TPOINT pt;

		Item* pItem = pPC->getQuestItem();
		if ( pItem == NULL || !pPC->getInventory()->getEmptySlot( pItem, pt ) )
		{
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
			gcNPCResponse.setParameter( COMPLETE_FAIL_NO_INVENTORY_SPACE );
			pPC->getPlayer()->sendPacket( &gcNPCResponse );

			return;
		}

		if ( pPC->getInventory()->addItem( pItem, pt ) )
		{
			pPC->setQuestItem( NULL );
			pPC->getZone()->registerObject( pItem );

			pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );
			if ( pItem->isUnique() || pItem->isTimeLimitItem() )
			{
				pPC->addTimeLimitItem( pItem, 604800 );
				pPC->sendTimeLimitItemInfo();
			}

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, pt.x, pt.y );
			pPC->getPlayer()->sendPacket( &gcCreateItem );
			
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
			gcNPCResponse.setParameter( COMPLETE_SUCCESS );
			pPC->getPlayer()->sendPacket( &gcNPCResponse );

			remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
			return;
		}
		else
		{
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
			gcNPCResponse.setParameter( COMPLETE_FAIL_NO_INVENTORY_SPACE );
			pPC->getPlayer()->sendPacket( &gcNPCResponse );
			return;
		}

	}

	int questLevel = pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel();
	ScriptID_t sID = m_ScriptID[ questLevel ];
	QuestID_t qID;

	if ( !pPC->getQuestManager()->successEventQuest( questLevel, qID ) ) sID = m_CounterScriptID;
	if ( pPC->getQuestManager()->getEventQuestAdvanceManager()->getStatus(questLevel) == EventQuestAdvance::EVENT_QUEST_INIT &&
			questLevel > 1 ) sID = m_CancelScriptID;

	GCNPCAsk gcNPCAsk;
	gcNPCAsk.setObjectID(pCreature1->getObjectID());
	gcNPCAsk.setScriptID(sID);
	gcNPCAsk.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAsk);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRewardEventQuest::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRewardEventQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
