////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStartPetQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionStartPetQuest.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Gpackets/GCMonsterKillQuestInfo.h"
#include "Gpackets/GCSystemMessage.h"
#include "mission/QuestManager.h"
#include "mission/MonsterKillQuestStatus.h"
#include "VariableManager.h"
#include "StringPool.h"
#include "MonsterInfo.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionStartPetQuest::read (PropertyBuffer & propertyBuffer)
    
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
void ActionStartPetQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	if ( g_pVariableManager->getVariable(RACE_PET_QUEST) == 0 )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( g_pStringPool->getString( STRID_NOT_SUPPORT ) );

		pPC->getPlayer()->sendPacket( &gcSM );
	
		return;
	}

	if ( !pPC->getQuestManager()->canStartMoreQuest() )
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
		gcNPCResponse.setParameter( (uint)START_FAIL_QUEST_NUM_EXCEEDED );

		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	GCMonsterKillQuestInfo gcMKQI;
	GCMonsterKillQuestInfo::QuestInfo* pQI = pPC->getPetQuestInfo();
	gcMKQI.addQuestInfo( pQI );
	pPC->getPlayer()->sendPacket( &gcMKQI );

	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pQI->sType );
	Assert( pMonsterInfo != NULL );

	MonsterKillQuestStatus* pQS = new MonsterKillQuestStatus( pQI->questID, VSDateTime::currentDateTime().addSecs(pQI->timeLimit),
			pMonsterInfo->getSpriteType(), false, pQI->goal );
	pQS->setTimeLimit( true );

	if ( pPC->isSlayer() ) pQS->setRewardClass( 70 );
	else if ( pPC->isVampire() ) pQS->setRewardClass( 71 );
	else if ( pPC->isOusters() ) pQS->setRewardClass( 72 );

	pPC->getQuestManager()->addQuest( pQS );
	pPC->sendCurrentQuestInfo();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionStartPetQuest::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionStartPetQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
