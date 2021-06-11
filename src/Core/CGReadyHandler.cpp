//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReadyHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReady.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "ZonePlayerManager.h"
	#include "Zone.h"
	#include "ZoneGroup.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 클라이언트가 데이터 로딩을 끝내면, 게임 서버에게 CGReady 패킷을 전송한다.
// 이 패킷을 받은 클라이언트는 Zone의 큐에 PC를 넣어주고, 마지막으로
// 플레이어를 IPM에서 ZPM으로 옮긴다.
//////////////////////////////////////////////////////////////////////////////
void CGReadyHandler::execute (CGReady* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : BEGIN");

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	// 주석처리 by sigi. 2002.5.11
	//Zone* pZone = pCreature->getZone();
	//Assert(pZone != NULL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : After pointer");
	
	//--------------------------------------------------------------------------------
	// 플레이어를 IPM에서 삭제하고 ZPM으로 옮긴다.
	//--------------------------------------------------------------------------------
	try 
	{
		// IncomingPlayer의 Process Commands 안에서 실행되는 것이므로 반드시 노 블락으로 지워야 할 것이다.
		//g_pIncomingPlayerManager->deletePlayer_NOBLOCKED(pGamePlayer->getSocket()->getSOCKET());
		g_pIncomingPlayerManager->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		// Core의 구조 변경에 따라 쓰레드 간의 간섭을 최대한 억제하기 위하여 heartbeat에서 일괄적으로 보낸다.
		g_pIncomingPlayerManager->pushOutPlayer(pGamePlayer);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After deletePlayer[Name:%s]", pCreature->getName().c_str());

		/*
		ZoneGroup* pZoneGroup = pZone->getZoneGroup();
		Assert(pZoneGroup != NULL);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After getZoneGroup[Name:%s]", pCreature->getName().c_str());

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		Assert(pZonePlayerManager != NULL);	

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After getZonePlayerManager[Name:%s]", pCreature->getName().c_str());

//		pZonePlayerManager->addPlayer(pGamePlayer);
//		pZonePlayerManager->pushPlayer(pGamePlayer);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After pushPlayer[Name:%s]", pCreature->getName().c_str());


		// PC를 존의 큐에 집어넣는다.
		//pGamePlayer->getCreature()->getZone()->pushPC(pGamePlayer->getCreature());

//		pZone->pushPC(pCreature);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After pushPC[Name:%s]", pCreature->getName().c_str());

		//pZone->addPC(pCreature, pCreature->getX(), pCreature->getY(), DOWN);
		*/
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;
		msg << "Critical Error : IPM에 플레이어가 없네용. 무슨 일이지..  - -;\n" << nsee.toString();
		throw Error(msg.toString());
	}

	// 잠시동안 적으로부터 공격을 받지 않는 상태이다.
	pGamePlayer->setPlayerStatus(GPS_NORMAL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : END");

#endif

	__END_DEBUG_EX 
	__END_CATCH
}
