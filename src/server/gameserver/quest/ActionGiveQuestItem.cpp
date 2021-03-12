////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveQuestItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveQuestItem.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"

#include "Item.h"
#include "PacketUtil.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCNPCAsk.h"
#include "Gpackets/GCCreateItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveQuestItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_CounterScriptID = propertyBuffer.getPropertyInt( "CounterScriptID" );
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
void ActionGiveQuestItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	TPOINT pt;

	Item* pItem = pPC->getQuestItem();
	if ( pItem == NULL || !pPC->getInventory()->getEmptySlot( pItem, pt ) )
	{
		GCNPCAsk gcNPCAsk;
		gcNPCAsk.setObjectID( pCreature1->getObjectID() );
		gcNPCAsk.setScriptID( m_CounterScriptID );
		gcNPCAsk.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

		pPC->getPlayer()->sendPacket( &gcNPCAsk );
		return;
	}

	if ( pPC->getInventory()->addItem( pItem, pt ) )
	{
		pPC->setQuestItem( NULL );
		pPC->getZone()->registerObject( pItem );

		pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );
		if ( pItem->isUnique() || pItem->isTimeLimitItem() )
		{
			pPC->addTimeLimitItem( pItem, 43200 );
		}

		GCCreateItem gcCreateItem;
		makeGCCreateItem( &gcCreateItem, pItem, pt.x, pt.y );
		pPC->getPlayer()->sendPacket( &gcCreateItem );
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveQuestItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveQuestItem("
	    << ")";

	return msg.toString();

	__END_CATCH
}
