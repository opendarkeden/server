
////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveFinalLottoScript.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveFinalLottoScript.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Inventory.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCAsk.h"
#include "Gpackets/GCDeleteInventoryItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveFinalLottoScript::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_SuccessScriptID = propertyBuffer.getPropertyInt( "SuccessScriptID" );
		m_FailScriptID = propertyBuffer.getPropertyInt( "FailScriptID" );
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
void ActionGiveFinalLottoScript::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	GCNPCAsk gcNPCAsk;
	gcNPCAsk.setObjectID( pCreature1->getObjectID() );
	gcNPCAsk.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

	QuestID_t	qID;

	if ( pPC->getQuestManager()->successEventQuest( 4, qID ) )
	{
		ItemType_t fitItem = rand()%10;

		if ( pPC->getInventory()->findItem( Item::ITEM_CLASS_EVENT_ITEM, fitItem ) != NULL )
		{
			pPC->getQuestManager()->getEventQuestAdvanceManager()->advanced(EventQuestAdvanceManager::EVENT_QUEST_LEVEL_MAX-1);
			gcNPCAsk.setScriptID( m_SuccessScriptID );
		}
		else
		{
			gcNPCAsk.setScriptID( m_FailScriptID );
		}

		list<Item*> iList;
		pPC->getInventory()->clearQuestItem(iList);

		list<Item*>::iterator itr = iList.begin();
		list<Item*>::iterator endItr = iList.end();

		for ( ; itr != endItr ; ++itr )
		{
			GCDeleteInventoryItem gcDII;
			gcDII.setObjectID( (*itr)->getObjectID() );
			pPC->getPlayer()->sendPacket( &gcDII );
			(*itr)->destroy();
			SAFE_DELETE( *itr );
		}

		iList.clear();

	}
	else
	{
		gcNPCAsk.setScriptID( m_CounterScriptID ); 
	}

	pPC->getPlayer()->sendPacket( &gcNPCAsk );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveFinalLottoScript::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveFinalLottoScript("
	    << ")";

	return msg.toString();

	__END_CATCH
}
