//////////////////////////////////////////////////////////////////////
//
// Filename    : GCReconnectHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCReconnect.h"
#include "Assert.h"

#ifdef __GAME_SERVER__
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCReconnectHandler::execute ( GCReconnect * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__


#endif
		
	__END_DEBUG_EX __END_CATCH
}

/*

	// 이 코드는 게임 서버에서 실행되어야 하는 코드이다. 즉 특정 사용자가
	// 존의 포탈위로 올라갔을 때, 이 포탈의 목적지가 다른 서버일 경우 
	// 
	try {

		// 일단 크리처를 데이타베이스에 저장하고, 존에서 삭제해야 한다.
		Creature * pCreature = pPlayer->getCreature();
		// g_pDatabaseManager->saveCreature(pCreature);
		Zone * pZone = pCreature->getZone();
		Tile & tile = pZone->getTile( pCreature->getX() , pCreature->getY() );
		tile.deleteCreature( pCreature->getMoveMode() );

		// 플레이어 객체를 존그룹의 플레이어매니저에서 삭제한다.
		ZoneGroup * pZoneGroup = pZone->getZoneGroup();
		ZonePlayerManager * pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		pZonePlayerManager->deletePlayer( pPlayer->getSocket()->getSOCKET() );

		// 플레이어에게 GCReconnect 패킷을 던진다.
		GCReconnect gcReconnect;
		gcReconnect.setServerIP( ... );
		gcReconnect.setKey( ... );
		pPlayer->sendPacket( &gcReconnect);

		// 흠.. 플러시가 되는가.. 최소한 버퍼는 플러시하고나서 접속을 끊어야 한다.
		pPlayer->flush();

		// 연결을 종료하고, 플레이어 객체를 삭제한다. 
		SAFE_DELETE(pPlayer);
	} 
	catch ( NoSuchElementException & nsee ) 
	{
		// 잘못된 패킷이라는 소리다. 즉 IncomingPlayer 상태가 아니라는 뜻.
		// 즉 해킹에 의해서 날아온 패킷이므로, Ban Manager 에 등록하고, 접속을 종료한다.
		// 일단은 서버를 종료한다.
		throw Error( nsee.toString() );

	}
*/	
