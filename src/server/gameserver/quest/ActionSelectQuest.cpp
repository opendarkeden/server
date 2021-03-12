////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSelectQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSelectQuest.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "StringPool.h"

#include "VariableManager.h"
#include "mission/QuestManager.h"
#include "mission/QuestInfoManager.h"
#include "mission/MonsterKillQuestInfo.h"

#include "Gpackets/GCSelectQuestID.h"
#include "Gpackets/GCMonsterKillQuestInfo.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSelectQuest::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
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
void ActionSelectQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

#ifdef __CHINA_SERVER__
	// 중국에는 막아놓기다.
	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &gcNPCResponse );

	GCSystemMessage gcSM;
	gcSM.setMessage( g_pStringPool->getString( STRID_NOT_SUPPORT ) );
	pPlayer->sendPacket( &gcSM );

	return;
#endif

	if ( !pPC->getQuestManager()->canStartMoreQuest() )
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
		gcNPCResponse.setParameter( (uint)START_FAIL_QUEST_NUM_EXCEEDED );

		pPlayer->sendPacket( &gcNPCResponse );
		return;
	}

	list<QuestID_t> quests;
	pNPC->getQuestInfoManager()->getPossibleQuestIDs( pPC, back_inserter( quests ) );

	if ( g_pVariableManager->bSendQuestInfo() )
	{
		GCMonsterKillQuestInfo gcMKQInfo;
		list<QuestInfo*> QIs;
		pNPC->getQuestInfoManager()->getMonsterKillQuests( quests.begin(), quests.end(), back_inserter( QIs ) );

		list<QuestInfo*>::iterator itr = QIs.begin();
		list<QuestInfo*>::iterator endItr = QIs.end();

		for (; itr != endItr ; ++itr )
		{
			MonsterKillQuestInfo* pQI = dynamic_cast<MonsterKillQuestInfo*>(*itr);
			if ( pQI == NULL ) continue;

			GCMonsterKillQuestInfo::QuestInfo* pPacketQI = new GCMonsterKillQuestInfo::QuestInfo;

			pPacketQI->questID = pQI->getQuestID();
			pPacketQI->sType = pQI->getTargetMonsterSpriteType();
			pPacketQI->goal = pQI->getGoalNum();
			pPacketQI->timeLimit = pQI->getTimeLimit();

			//cout << pPacketQI->questID << ", " << pPacketQI->goal << ", " << pPacketQI->timeLimit << endl;

			gcMKQInfo.addQuestInfo( pPacketQI );
		}

		pPlayer->sendPacket( &gcMKQInfo );
	}

	GCSelectQuestID gcSelectQuestID( quests.begin(), quests.end() );

	pPlayer->sendPacket( &gcSelectQuestID );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSelectQuest::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSelectQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
