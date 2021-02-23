//////////////////////////////////////////////////////////////////////////////
// Filename    : CGNPCTalkHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGNPCTalk.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "StringPool.h"

	#include "quest/TriggerManager.h"
	#include "quest/Trigger.h"
	#include "quest/Condition.h"
	#include "quest/Action.h"

	#include "Gpackets/GCNPCSayDynamic.h"
	#include "Gpackets/GCNPCResponse.h"

	#include "PlayerCreature.h"
	#include "GQuestManager.h"
#endif

const string DiffClanSpeech[] = 
{
	"경비병! 경비병! 여기 바토리의 종복들이 침입해왔다.",
	"으흠? 이것은.. 바토리의 혈족들의 피냄새! 드디어 네놈들이 블라드님의 안식처까지 더럽히려 왔구나!!",
	"네 놈은 누구야? 감히 여기가 어디라고.. Abscede Hinc!!"
};

//////////////////////////////////////////////////////////////////////////////
// 플레이어가 NPC를 클릭할 경우, 클라이언트가 CGNPCTalk 패킷을 서버로
// 전송한다. 서버는 이 패킷을 핸들링할 때, NPC에 CONDITION_TALKED_BY 
// 컨디션 플래그가 켜져 있으면, 트리거를 탐색하면서 적절한 트리거를 찾아서
// 연관된 액션을 실행한다.
//////////////////////////////////////////////////////////////////////////////
void CGNPCTalkHandler::execute (CGNPCTalk* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	try 
	{
		Assert(pPacket != NULL);
		Assert(pPlayer != NULL);

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		PlayerCreature*   pPC         = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		Assert( pPC != NULL );
		Zone*       pZone       = pPC->getZone();

		// 일단 말을 거는 PC가 현재 살아있는 상태여야 한다.
		// 이 검사를 하는 이유는 독에 중독되어 있는 슬레이어가, 시간 차로 인해서
		// NPC한테 HEAL을 요청한 직후에, 독에 의해서 죽어버리면,
		// 일단 바닥에 쓰러지게 되는데, 곧이어 NPC에 의해서 치료를 받게 된다.
		// 이 경우, HP는 풀인데 바닥에 쓰러져있게 된다.
		// 이 말은 PCManager::heartbeat()에서 killCreature로 들어가지 않게 된다는 말이다.
		// 음. 잘 설명이 되지 않는데, 하옇튼 NPC에게 말을 걸려면 플레이어는 살아있어야 한다.
		if (pPC->isDead())
		{
			return;
		}

		Creature* pNPCBase = NULL;

		/*
		try 
		{ 
			pNPCBase = pZone->getCreature(pPacket->getObjectID()); 
		} 
		catch (NoSuchElementException) 
		{ 
			// 그런 NPC가 없다면 리턴한다.
			return;
		}
		*/

		// NoSuch제거. by sigi. 2002.5.2
		pNPCBase = pZone->getCreature(pPacket->getObjectID()); 

		if (pNPCBase==NULL)
		{
			return;
		}

		NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);

		// ObjectID가 NPC가 아닐 수도 있었다. 뭘까.. 사기인가? 패킷 꼬인건가?
		// 어쨋든 무시하도록하자.
		// by sigi. 2002.11.25
		if (pNPC==NULL)
		{
			return;
		}

		// 퀘스트로 만난 넘일때 ^^;
		if ( pPC->getGQuestManager()->metNPC(pNPC) )
		{
			// 일단 클라이언트를 위해 OK패킷을 함 날린다.
			GCNPCResponse gcNPCAskAnswer;
			pPlayer->sendPacket(&gcNPCAskAnswer);

			return;
		}

		// 아담의 성지에서는 NPC와 NP의 종족을 무시한다.
		// 성에서는 종족별 NPC가 다르다.
		if ( !pZone->isHolyLand() 
			|| pZone->isCastle() )
		{
			// 뱀파이어가 슬레이어 NPC에게 말을 걸었을 경우에 무시한다.
			if (pNPC->getRace() == NPC_RACE_SLAYER && pPC->isVampire())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				// 뱀파이어가 슬레이어 NPC에게 말을 걸면...
				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				// Event 용 NPC 인 경우 다른 말을 한다 ;;
				if ( pNPC->getNPCID() == 639 )
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_EVENT_NPC_1 ) );
				}
				else
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_VAMPIRE ) );
				}
				pPlayer->sendPacket(&saypkt);
				return;
			}
			// 아우스터스가 슬레이어 NPC에게 말을 걸었을 경우에 무시한다.
			else if (pNPC->getRace() == NPC_RACE_SLAYER && pPC->isOusters())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				// 뱀파이어가 슬레이어 NPC에게 말을 걸면...
				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_OUSTERS_2 ) );
				pPlayer->sendPacket(&saypkt);
				return;
			}
			// 슬레이어가 뱀파이어 NPC에게 말을 걸어도 무시한다.
			else if (pNPC->getRace() == NPC_RACE_VAMPIRE && pPC->isSlayer())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				// 슬레이어가 뱀파이어 NPC에게 말을 걸면...
				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				// Event 용 NPC 인 경우 다른 말을 한다 ;;
				if ( pNPC->getNPCID() == 638 )
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_EVENT_NPC_2 ) );
				}
				else if ( pNPC->getNPCID() == 636 )
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_EVENT_NPC_3 ) );
				}
				else if ( pNPC->getNPCID() == 635 )
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_EVENT_NPC_4 ) );
				}
				else
				{
					saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_SLAYER ) );
				}
				pPlayer->sendPacket(&saypkt);
				return;
			}
			// 아우스터스가 뱀파이어 NPC에게 말을 걸어도 무시한다.
			else if (pNPC->getRace() == NPC_RACE_VAMPIRE && pPC->isOusters())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_OUSTERS ) );
				pPlayer->sendPacket(&saypkt);
				return;
			}
			// 슬레이어가 아우스터스 NPC에게 말을 걸어도 무시한다.
			else if (pNPC->getRace() == NPC_RACE_OUSTERS && pPC->isSlayer())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_SLAYER_2 ) );
				pPlayer->sendPacket(&saypkt);
				return;
			}
			// 뱀파이어가 아우스터스 NPC에게 말을 걸어도 무시한다.
			else if (pNPC->getRace() == NPC_RACE_OUSTERS && pPC->isVampire())
			{
				// 일단 클라이언트를 위해 OK패킷을 함 날린다.
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				saypkt.setMessage( g_pStringPool->c_str( STRID_ALERT_VAMPIRE_2 ) );
				pPlayer->sendPacket(&saypkt);
				return;
			}
		}

		// 같은 뱀파이어끼리도 클랜이 다른 NPC일 경우 무시한다.
		// 이 부분의 코드는 나중에 다른 방법으로 출력해야 할 것이다.
		// 현재는 클랜이 오직 두 가지 뿐이기 때문에...
		// .....
		// 클랜 한가지 밖에 엄써~~
/*		if (pPC->isVampire() && pNPC->getRace() == NPC_RACE_VAMPIRE)
		{
			if (pPC->getClanType() != pNPC->getClanType())
			{
				GCNPCResponse gcNPCAskAnswer;
				pPlayer->sendPacket(&gcNPCAskAnswer);

				GCNPCSayDynamic saypkt;
				saypkt.setObjectID(pNPC->getObjectID());
				saypkt.setMessage(DiffClanSpeech[rand()%3]);
				pPlayer->sendPacket(&saypkt);
				return;
			}
		}
*/
		// 플레이어가 말을 걸었을 경우에 반응하는 액션이 있다면...
		const TriggerManager & triggerManager = pNPC->getTriggerManager();
		if (triggerManager.hasCondition(Condition::CONDITION_TALKED_BY))
		{
			const list<Trigger*> & triggers = triggerManager.getTriggers();
			for (list<Trigger*>::const_iterator itr = triggers.begin() ; itr != triggers.end() ; itr ++)
			{
				Trigger* pTrigger = *itr;
				Assert(pTrigger != NULL);

				// check all condition after check main condition
				if (pTrigger->hasCondition(Condition::CONDITION_TALKED_BY) && pTrigger->isAllSatisfied(Trigger::PASSIVE_TRIGGER , pNPC , pPC))
				{
					// 최초로 발견된 트리거만 실행한 다음 break 한다.
					pTrigger->activate(pNPC , pPC);
					break;
				}
			}
		}
		// 클라이언트는 NPC를 클릭했을 경우, 무조건 서버의 응답을 기다리기 때문에, 
		// 그런 액션이 존재하지 않을 때 아무 것도 하지 않으면, 클라이언트가 일종의 데드락(?)
		// 상태에 빠지게 된다. 그것을 방지하기 위해서 대화창을 닫으라는 메세지를 보내준다.
		else
		{
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&gcNPCResponse);
		}
	} 
	catch (Throwable & t) 
	{
		//cerr << "누가 NPC 오브젝트 아이디를 이상하게 보내주네?" << endl;
		//cerr << t.toString() << endl;
	}
	
#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
