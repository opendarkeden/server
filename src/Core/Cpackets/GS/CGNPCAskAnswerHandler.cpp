//////////////////////////////////////////////////////////////////////////////
// Filename    : CGNPCAskAnswer.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGNPCAskAnswer.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include <fstream.h>

	#include "quest/TriggerManager.h"
	#include "quest/Trigger.h"
	#include "quest/Condition.h"
	#include "quest/Action.h"

	#include "Gpackets/GCNPCResponse.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 플레이어가 NPC를 클릭할 경우, 클라이언트가 CGNPCAskAnswer 패킷을
// 서버로 전송한다.  서버는 이 패킷을 핸들링할 때,
// NPC에 CONDITION_TALKED_BY 컨디션 플래그가 켜져 있으면,
// 트리거를 탐색하면서 적절한 트리거를 찾아서 연관된 액션을 실행한다.
//////////////////////////////////////////////////////////////////////////////
void CGNPCAskAnswerHandler::execute (CGNPCAskAnswer* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Creature*   pCreature   = NULL;

	if (pPC == NULL) return;

	Zone* pZone = pPC->getZone();

	if (pZone == NULL) return; 

	/*
	try 
	{
		pCreature = pZone->getCreature(pPacket->getObjectID());
	} 
	catch (NoSuchElementException) 
	{
		//cout << "여기 NPC 없다~" << endl;
		pCreature = NULL;
	}
	*/
	//cout << pPacket->toString().c_str() << endl;

	// NoSuch제거. by sigi. 2002.5.2
	pCreature = pZone->getCreature(pPacket->getObjectID());

	if (pCreature == NULL || !pCreature->isNPC())
	{
		GCNPCResponse okpkt;
		pPlayer->sendPacket(&okpkt);
//add by viva for test
		cout << okpkt.toString().c_str() << endl;
		cout<<"pCreature == NULL || !pCreature->isNPC()"<<endl;
		//end
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pCreature);

	COND_ANSWERED_BY cond;
	cond.ScriptID = pPacket->getScriptID();
	cond.AnswerID = pPacket->getAnswerID();

	// get NPC's trigger manager
	const TriggerManager & triggerManager = pNPC->getTriggerManager();

	// check main condition
	if (triggerManager.hasCondition(Condition::CONDITION_ANSWERED_BY))
	{
		const list<Trigger*> & triggers = triggerManager.getTriggers();
		for (list<Trigger*>::const_iterator itr = triggers.begin() ; itr != triggers.end() ; itr ++)
		{
			Trigger* pTrigger = *itr;
			if (pTrigger == NULL) 
			{ 
				//cout << "*** shit trigger is NULL ***"; 
				return; 
			}

			// check all condition after check main condition
			if (pTrigger->hasCondition(Condition::CONDITION_ANSWERED_BY) && 
			     pTrigger->isAllSatisfied(Trigger::PASSIVE_TRIGGER , pNPC , pPC, (void*)&cond)) 
			{
				// 최초로 발견된 트리거만 실행한 다음 break 한다.
				pTrigger->activate(pNPC , pPC);
				//add by viva for test
//				cout<<"PTrigger->activate(pNPC, pPC);"<<endl;
				//end
				break;
			}
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
