//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGuildChatHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGGuildChat.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Properties.h"
	#include "GameServerInfoManager.h"
	#include "LoginServerManager.h"
	#include "Gpackets/GGGuildChat.h"
	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGGuildChatHandler::execute (CGGuildChat* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	if ( !pCreature->isPC() )
		return;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	GGGuildChat ggGuildChat;
	ggGuildChat.setType( pPacket->getType() );
	ggGuildChat.setGuildID( pPC->getGuildID() );
	ggGuildChat.setSender( pPC->getName() );
	ggGuildChat.setColor( pPacket->getColor() );
	ggGuildChat.setMessage( pPacket->getMessage() );

	// 각 서버로 보낸다.
	HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();

	static int myWorldID = g_pConfig->getPropertyInt( "WorldID" );
	static int myServerID = g_pConfig->getPropertyInt( "ServerID" );

	int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();

	for ( int groupID = 0 ; groupID < maxServerGroupID ; groupID ++ )
	{
		HashMapGameServerInfo& gameServerInfo = pGameServerInfos[myWorldID][groupID];

		if ( !gameServerInfo.empty() )
		{
			HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
			for ( ; itr != gameServerInfo.end() ; itr++ )
			{
				GameServerInfo* pGameServerInfo = itr->second;

				g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggGuildChat );
			}
		}
	}


#endif
		
	__END_DEBUG_EX __END_CATCH
}
