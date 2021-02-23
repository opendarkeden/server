////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveLotto.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveLotto.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Properties.h"
#include "Inventory.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCDeleteInventoryItem.h"

#include "Cpackets/CGLotterySelect.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveLotto::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_QuestLevel = propertyBuffer.getPropertyInt("QuestLevel")-1;
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
void ActionGiveLotto::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	QuestID_t	qID;
	int questLevel = m_QuestLevel;

	if ( questLevel < 0 ) questLevel = pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel() - 1;

	cout << "Activated : " << toString() << " ... " << pPC->getName() << " ...  " << questLevel << endl;

	EventQuestAdvance::Status status = pPC->getQuestManager()->getEventQuestAdvanceManager()->getStatus( questLevel );
	int ownerQuestLevel = pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel();

	if ( 
		( ownerQuestLevel > questLevel && status == EventQuestAdvance::EVENT_QUEST_ADVANCED )
	||	( ( questLevel == 4 && ownerQuestLevel == -1 ) || pPC->getQuestManager()->successEventQuest( questLevel, qID ) )
	)
	{
		GamePlayer* pGP = dynamic_cast<GamePlayer*>( pPC->getPlayer() );
		Assert ( pGP != NULL );

//		if ( g_pConfig->getPropertyInt( "IsNetMarble" ) || !pGP->isPayPlaying() )
		if ( true )
		{
			pPC->getQuestManager()->getEventQuestAdvanceManager()->rewarded( questLevel );
			pPC->getQuestManager()->getEventQuestAdvanceManager()->save();
			if ( questLevel != 4 )
				pPC->getQuestManager()->questRewarded( qID );
			else
				pPC->getQuestManager()->cancelQuest();

			pPC->setLottoQuestLevel( questLevel );

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

			CGLotterySelect	cgLS;
			cgLS.setType(TYPE_FINISH_SCRATCH);
			cgLS.setQuestLevel(0);
			cgLS.setGiftID(0);
			CGLotterySelectHandler::execute( &cgLS, pPC->getPlayer() );
//			cgLS.execute( pPC->getPlayer() );

		}
		else
		{
			Player* pPlayer = pCreature2->getPlayer();
	//		pPlayer->sendPacket(&gcSM);

			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_LOTTERY);
			gcNPCResponse.setParameter( (uint)questLevel );

			pPlayer->sendPacket( &gcNPCResponse );

			filelog("EventQuest.log","ActionGiveLotto : %d to %s", questLevel, pPC->getName().c_str() );
		}
	}

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPC->getPlayer()->sendPacket( &gcNPCResponse );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveLotto::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveLotto("
		<< "QuestLevel : " << m_QuestLevel
	    << ")";

	return msg.toString();

	__END_CATCH
}
