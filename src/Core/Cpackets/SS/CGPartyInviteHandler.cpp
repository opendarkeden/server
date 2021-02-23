//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyInviteHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyInvite.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "Zone.h"
	#include "Party.h"
	#include "CreatureUtil.h"
	#include "GQuestManager.h"
	#include "PlayerCreature.h"

	#include "Gpackets/GCPartyInvite.h"
	#include "Gpackets/GCPartyError.h"
	#include "Gpackets/GCSystemMessage.h"

	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyInviteHandler::execute (CGPartyInvite* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT( SYSTEM_PARTY );

	ObjectID_t TargetOID = pPacket->getTargetObjectID();
	BYTE CODE = pPacket->getCode();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();

	// 파티 기능 버그 때문에 막아놓은 부분이다.
	// 김성민
	/*
	pPIIM->cancelInvite(pCreature);

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage("파티 기능은 버그로 인하여 현재 지원되지 않습니다.");
	pPlayer->sendPacket(&gcSystemMessage);

	executeError(pPacket, pPlayer, GC_PARTY_ERROR_UNKNOWN);
	return;
	*/
	/////

	Creature* pTargetCreature = NULL;
	/*
	try
	{
		pTargetCreature = pZone->getCreature(TargetOID);
	}
	catch (NoSuchElementException)
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pTargetCreature = pZone->getCreature(TargetOID);

	if (pTargetCreature==NULL)
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	// add by Coffee 2006.12.7
	if(pCreature->getObjectID() == pTargetCreature->getObjectID())
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	// end

	// 파티에 초대할 놈이 PC가 아니거나, 종족이 다르면 가입시킬 수가 없다.
	if (!pTargetCreature->isPC() || !isSameRace(pCreature, pTargetCreature))
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer,GC_PARTY_ERROR_RACE_DIFFER);
		return;
	}

	// 타겟의 플레이어를 받아온다. 
	//PartyInviteInfo* pInfo1 = pPIIM->getInviteInfo(pCreature->getName());
	PartyInviteInfo* pInfo2 = pPIIM->getInviteInfo(pTargetCreature->getName());
	Player* pTargetPlayer = pTargetCreature->getPlayer();

	GCPartyInvite gcPartyInvite;

	// 다른 사람을 파티에 가입시키고자 할 때
	if (CODE == CG_PARTY_INVITE_REQUEST)
	{
		//cout << "CODE:CG_PARTY_INVITE_REQUEST" << endl;

		// 초대한 놈이 이미 다른 놈을 초대 중이라면... 
		// A가 B를 초대한다. 그 다음, B가 A의 요구를
		// 전달받지 못한 상태에서 A를 초대한다. 
		// 이 경우 둘 다 CODE가 CG_PARTY_INVITE_REQUEST인데...
		// cancalInvite해버리면, A와 B의 정보가 날아가버리게 된다.
		// 그것을 방지하기 위해 주석처리해버린다.
		// 음, 무슨 말인지 내가 봐도 잘 모르겠네... -- excel96
		/*
		if (pInfo1 != NULL)
		{
			//pPIIM->cancelInvite(pCreature);
			return;
		}
		*/

		// 초대받은 놈이 이미 다른 놈과 초대 관계 중이라면...
		// 바쁘니가 초대에 응할 수 없다.
		if (pInfo2 != NULL)
		{
			//cout << "pInfo2 != NULL" << endl;

			gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_BUSY);
			pPlayer->sendPacket(&gcPartyInvite);
			return;
		}

		int PartyID       = pCreature->getPartyID();
		int TargetPartyID = pTargetCreature->getPartyID();

		//cout << "Creature" << pCreature->getName() << "] PartyID = " << PartyID << endl;
		//cout << "TargetCreature" << pTargetCreature->getName() << "] PartyID = " << PartyID << endl;

		// 초대한 놈과 초대받은 놈 둘 다가 파티에 가입되어있다면 가입할 수가 없다.
		if (PartyID != 0 && TargetPartyID != 0)
		{
			gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_ANOTHER_PARTY);
			pPlayer->sendPacket(&gcPartyInvite);
			return;
		}

		// 초대한 놈의 파티 숫자가 맥스라면 초대할 수 없다.
		if (PartyID != 0)
		{
			if (!g_pGlobalPartyManager->canAddMember(PartyID))
			{
				gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
				gcPartyInvite.setCode(GC_PARTY_INVITE_MEMBER_FULL);
				pPlayer->sendPacket(&gcPartyInvite);
				return;
			}
		}

		// 초대받은 놈의 파티 숫자가 맥스라면 초대할 수 없다.
		if (TargetPartyID != 0)
		{
			if (!g_pGlobalPartyManager->canAddMember(TargetPartyID))
			{
				gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
				gcPartyInvite.setCode(GC_PARTY_INVITE_MEMBER_FULL);
				pPlayer->sendPacket(&gcPartyInvite);
				return;
			}
		}

		//cout << "Sending Packet" << endl;

		// 패킷을 보내준다.
		gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
		gcPartyInvite.setCode(GC_PARTY_INVITE_REQUEST);
		pTargetPlayer->sendPacket(&gcPartyInvite);

		//cout << "Sent gcPartyInvite" << endl;

		// 둘 다 초대모드로 들어갔으므로, 초대 정보를 생성해 준다.
		pPIIM->initInviteInfo(pCreature, pTargetCreature);

		//cout << "initInviteInfo OK" << endl;
	}
	// 파티 가입 신청을 취소할 때
	else if (CODE == CG_PARTY_INVITE_CANCEL)
	{
		// 현재 초대 중인지를 체크한다.
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			// 패킷을 준비해 보내준다.
			gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_CANCEL);
			pTargetPlayer->sendPacket(&gcPartyInvite);

			// 초대를 취소시킨다.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	// 파티 가입 요청을 받아들였을 때
	else if (CODE == CG_PARTY_INVITE_ACCEPT)
	{
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			int PartyID       = pCreature->getPartyID();
			int TargetPartyID = pTargetCreature->getPartyID();

			// 파티에 속해 있는 놈이 파티에 속하지 않는 놈을 초대했을 때
			// (파티에 속해있지 않은 놈이, 파티에 속해 있는 놈의 초대에 응했을 때)
			if (TargetPartyID != 0 && PartyID == 0)
			{
				// 글로벌 파티 매니저에 멤버를 더한다.
				if (g_pGlobalPartyManager->addPartyMember(TargetPartyID, pCreature))
				{
					// 로컬 파티 매니저에 멤버를 더한다.
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->addPartyMember(TargetPartyID, pCreature);
				}
			}
			// 파티에 속해있지 않은 놈이 파티에 속해있는 놈을 초대했을 때
			// (파티에 속해있는 놈이, 파티에 속해있지 않은 놈의 초대에 응했을 때)
			// (파티에 속해있는 놈이, 외부인의 진입을 허가했을 때)
			else if (PartyID != 0 && TargetPartyID == 0)
			{
				// 글로벌 파티 매니저에 멤버를 더한다.
				if (g_pGlobalPartyManager->addPartyMember(PartyID, pTargetCreature))
				{
					// 로컬 파티 매니저에 멤버를 더한다.
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->addPartyMember(PartyID, pTargetCreature);
				}
			}
			// 두 놈 다 아무런 파티에 속해있지 않을 때
			// (새로운 파티를 생성할 때)
			else
			{
				// 새로운 파티를 만들어 등록한다.
				int NewPartyID = g_pGlobalPartyManager->registerParty();

				// 글로벌 파티 매니저에 글로벌 파티를 더하고, 멤버를 더한다.
				g_pGlobalPartyManager->createParty(NewPartyID, pTargetCreature->getCreatureClass());
				g_pGlobalPartyManager->addPartyMember(NewPartyID, pCreature);
				g_pGlobalPartyManager->addPartyMember(NewPartyID, pTargetCreature);

				// 로컬 파티 매니저에 로컬 파티를 더하고, 멤버를 더한다.
				LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
				pLocalPartyManager->createParty(NewPartyID, pTargetCreature->getCreatureClass());
				pLocalPartyManager->addPartyMember(NewPartyID, pCreature);
				pLocalPartyManager->addPartyMember(NewPartyID, pTargetCreature);

				if ( pCreature->getLevel() >= 25 && pTargetCreature->getLevel() < 25 )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
					pPC->getGQuestManager()->eventParty();
				}
				else if ( pTargetCreature->getLevel() >= 25 && pCreature->getLevel() < 25 )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);
					pPC->getGQuestManager()->eventParty();
				}
			}

			// 파티 초대가 끝났으므로, 파티 초대 정보를 삭제해준다.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	// 파티 가입 요청을 거부했을 때
	else if (CODE == CG_PARTY_INVITE_REJECT)
	{
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			// 패킷을 보낸다.
			gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_REJECT);
			pTargetPlayer->sendPacket(&gcPartyInvite);

			// 파티 초대를 거부했으므로 초대 정보를 삭제시켜준다.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	else if (CODE == CG_PARTY_INVITE_BUSY)
	{
		gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
		gcPartyInvite.setCode(GC_PARTY_INVITE_BUSY);
		pPlayer->sendPacket(&gcPartyInvite);
	}
	else
	{
		throw ProtocolException("CGPartyInvite::execute() : Unknown Code");
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyInviteHandler::executeError (CGPartyInvite* pPacket , Player* pPlayer, BYTE ErrorCode)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GCPartyError gcPartyError;
	gcPartyError.setTargetObjectID(pPacket->getTargetObjectID());
	gcPartyError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcPartyError);

#endif

	__END_DEBUG_EX __END_CATCH
}
