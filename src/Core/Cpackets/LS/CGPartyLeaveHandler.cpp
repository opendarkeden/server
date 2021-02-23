//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeaveHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyLeave.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "Zone.h"
	#include "Party.h"
	#include "PCFinder.h"

	#include "Gpackets/GCPartyLeave.h"
	#include "Gpackets/GCPartyError.h"

	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyLeaveHandler::execute (CGPartyLeave* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT( SYSTEM_PARTY );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	string TargetName = pPacket->getTargetName();

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	int PartyID = pCreature->getPartyID();
	if (PartyID == 0)
	{
		//filelog("PARTY_EXCEPTION.log", "CGPartyLeaveHandler::execute() : 파티ID가 0입니다. [%s]", pCreature->toString().c_str());
		throw ProtocolException();
	}

	GCPartyError gcPartyError;

	// 타겟 이름이 NULL이라면 스스로 파티를 떠나고자 하는 것이다.
	if (TargetName == "")
	{
		// 글로벌 파티에서 삭제해 준다.
		// 2명인 상태에서 다른 하나를 추방했다면, 
		// 이 내부에서 글로벌 파티는 삭제된다.
		// 남은 파티원들의 ID는 0으로 바뀐다.
		//cout << "===== 파티를 떠나기 전의 글로벌 파티 매니저 상태" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "================================================" << endl;

		g_pGlobalPartyManager->deletePartyMember(PartyID, pCreature);

		//cout << "===== 파티를 떠난 후의 글로벌 파티 매니저 상태" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "================================================" << endl;

		// 로컬 파티에서 삭제해준다.
		LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
		Assert(pLocalPartyManager != NULL);
		pLocalPartyManager->deletePartyMember(PartyID, pCreature);
	}
	// 이름이 다르다면 파티 내에 존재하는 다른 파티원을 추방하고자 하는 것이다.
	else 
	{
		//cout << "===== 추방전의 글로벌 파티 매니저 상태" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		// 글로벌 파티에서 삭제해준다.
		// 2명인 상태에서 다른 하나를 추방했다면, 
		// 이 내부에서 글로벌 파티는 삭제된다.
		// 남은 파티원들의 ID는 0으로 바뀐다.
		g_pGlobalPartyManager->expelPartyMember(PartyID, pCreature, TargetName);

		//cout << "===== 추방후의 글로벌 파티 매니저 상태" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		// 차인 놈을 로컬 파티에서 삭제해준다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(TargetName);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2	
		if (pTargetCreature==NULL)
		{
			g_pPCFinder->unlock();
			return;
		}

		Zone* pTargetZone = pTargetCreature->getZone();
		Assert(pTargetZone != NULL);
		LocalPartyManager* pLocalPartyManager = pTargetZone->getLocalPartyManager();
		Assert(pLocalPartyManager != NULL);

		//cout << "===== 추방 전의 로컬 파티 매니저 상태" << endl;
		//cout << pLocalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		pLocalPartyManager->deletePartyMember(PartyID, pTargetCreature);
		//cout << "로컬 파티에서 추방당한 플레이어를 삭제했습니다." << endl;

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

