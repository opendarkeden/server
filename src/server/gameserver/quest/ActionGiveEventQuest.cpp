////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveEventQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveEventQuest.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "VariableManager.h"
#include "mission/QuestManager.h"
#include "mission/QuestInfoManager.h"
#include "mission/MonsterKillQuestInfo.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCSelectQuestID.h"
#include "Gpackets/GCMonsterKillQuestInfo.h"
#include "Gpackets/GCNPCResponse.h"

#include <algorithm>
#include <iosfwd>

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveEventQuest::read (PropertyBuffer & propertyBuffer)
    
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
void ActionGiveEventQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert( pNPC != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	if ( !pPC->getQuestManager()->canStartMoreQuest() )
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
		gcNPCResponse.setParameter( (uint)START_FAIL_QUEST_NUM_EXCEEDED );

		pPlayer->sendPacket( &gcNPCResponse );
		return;
	}

	if ( pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel() != m_QuestLevel )
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
		gcNPCResponse.setParameter( (uint)START_FAIL_PC );

		pPlayer->sendPacket( &gcNPCResponse );
		return;
	}

	list<QuestID_t> quests;
	pNPC->getQuestInfoManager()->getEventQuestIDs( m_QuestLevel, pPC, back_inserter( quests ) );

	//cout << "Quest List : ";
	//copy( quests.begin(), quests.end(), ostream_iterator<DWORD>(cout, ",") );
	//cout << endl;

	GCSelectQuestID gcGiveEventQuestID( quests.begin(), quests.end() );

	pPlayer->sendPacket( &gcGiveEventQuestID );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveEventQuest::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveEventQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
