
////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStartEventQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionStartEventQuest.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "Player.h"

#include "mission/QuestManager.h"
#include "mission/QuestInfoManager.h"
#include "mission/EventQuestAdvance.h"
#include "mission/RewardClassInfoManager.h"
#include "Gpackets/GCNPCResponse.h"

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionStartEventQuest::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
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
void ActionStartEventQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert( pNPC != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	GCNPCResponse gcNPCResponse;

	gcNPCResponse.setCode( NPC_RESPONSE_QUEST );

	QuestInfoManager* pQIM = pNPC->getQuestInfoManager();
	if ( pQIM == NULL )
	{
		gcNPCResponse.setParameter( START_FAIL_CANNOT_APPLY_QUEST );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		gcNPCResponse.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		return;
	}

	vector<QuestID_t> qList;
	pQIM->getEventQuestIDs( m_QuestLevel, pPC, back_inserter(qList) );
	if ( qList.empty() )
	{
		gcNPCResponse.setParameter( START_FAIL_CANNOT_APPLY_QUEST );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		gcNPCResponse.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		return;
	}

	QuestID_t	qID = qList[0];
	//cout << "Start Event Quest : " << qID << "... " << pPC->getName() << endl;

	pPC->getQuestManager()->adjustQuestStatus();
	QuestMessage result = pQIM->startQuest( qID, pPC );
//	gcNPCResponse.setParameter( (uint)result );

//	pPC->getPlayer()->sendPacket( &gcNPCResponse );
	pPC->sendCurrentQuestInfo();

	gcNPCResponse.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPC->getPlayer()->sendPacket( &gcNPCResponse );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionStartEventQuest::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionStartEventQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
