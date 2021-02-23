//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRangerSayHandler.cpp
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRangerSay.h"

#ifdef __GAME_SERVER__
	#include "ZoneGroupManager.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Creature.h"
	#include "GamePlayer.h"
	#include "StringStream.h"
	#include "BroadcastFilter.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRangerSayHandler::execute (CGRangerSay* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	// 크리쳐 이름과 메시지를 패킷에 넣는다.
	StringStream msg;
	msg << pCreature->getName() << " " << pPacket->getMessage();

	Race_t race = pCreature->getRace();

	// 패킷 생성
	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage( msg.toString() );
	gcSystemMessage.setType( SYSTEM_MESSAGE_RANGER_SAY );

	// 필터 생성
	BroadcastFilterRace filter( race );

	// 모든 사용자에게 뿌리기
	g_pZoneGroupManager->pushBroadcastPacket( &gcSystemMessage, &filter );

/*	hash_map<ZoneGroupID_t, ZoneGroup*>::const_iterator itr = g_pZoneGroupManager->getZoneGroups().begin();
	hash_map<ZoneGroupID_t, ZoneGroup*>::const_iterator endItr = g_pZoneGroupManager->getZoneGroups().end();

	for ( ; itr != endItr; ++itr )
	{
		GCSystemMessage* pSystemMessage = new GCSystemMessage();
		pSystemMessage->setMessage( msg.toString() );
		pSystemMessage->setType( SYSTEM_MESSAGE_RANGER_SAY );
		pSystemMessage->setRace( race );

		itr->second->getZonePlayerManager()->pushBroadcastPacket( pSystemMessage );
	}
*/
#endif

	__END_CATCH
}

