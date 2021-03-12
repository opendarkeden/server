////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionQuestReward.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionQuestReward.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "Player.h"

#include "mission/QuestManager.h"
#include "mission/QuestStatus.h"
#include "mission/RewardClassInfoManager.h"
#include "Gpackets/GCNPCResponse.h"

#include "CreatureUtil.h"

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionQuestReward::read (PropertyBuffer & propertyBuffer)
    
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
void ActionQuestReward::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	QuestMessage result = COMPLETE_FAIL_INVALID_NPC;

	RewardClassInfoManager* pRIM = pNPC->getRewardClassInfoManager();
	Assert( pRIM != NULL );

	pPC->getQuestManager()->adjustQuestStatus();

	if ( !pPC->getQuestManager()->hasQuest() )
	{
		result = COMPLETE_FAIL_NOT_IN_QUEST;
		pPC->sendCurrentQuestInfo();
	}
	else
	{
		list<RewardClass_t> rList;
		list<QuestID_t> qList;
		pPC->getQuestManager()->getCompletedQuestRewards( back_inserter(qList), back_inserter(rList) );

		if ( !rList.empty() )
		{
			list<RewardClass_t>::iterator itr = rList.begin();
			list<QuestID_t>::iterator qitr = qList.begin();

			for ( ; itr != rList.end(); ++itr, ++qitr )
			{
				result = pRIM->canGiveReward(*itr, pPC);

				if ( result == COMPLETE_SUCCESS && !pRIM->getRewardClass(*itr)->anotherQuestReward() )
				{
					QuestStatus* pQS = pPC->getQuestManager()->getQuestStatus((*qitr));
					if ( pQS != NULL && pQS->getQuestClass() == QUEST_CLASS_MONSTER_KILL )
					{
						addOlympicStat( pPC, 10 );
					}

					pPC->getQuestManager()->questRewarded( *qitr );
					Assert ( pRIM->getRewardClass( *itr )->giveReward(pPC) == COMPLETE_SUCCESS );
					break;
				}
			}
		}
		else
		{
			result = COMPLETE_FAIL_NOT_COMPLETE;
		}
	}

	//cout << "ActionQuestReward : result " << (int)result << endl;

	GCNPCResponse gcNPCResponse;

	gcNPCResponse.setCode( NPC_RESPONSE_QUEST );
	gcNPCResponse.setParameter( (uint)result );

	pPC->getPlayer()->sendPacket( &gcNPCResponse );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionQuestReward::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionQuestReward("
	    << ")";

	return msg.toString();

	__END_CATCH
}
