//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectGuildHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectGuild.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Creature.h"
	#include "GamePlayer.h"
	#include "GCShowGuildInfo.h"
	#include "GCShowWaitGuildInfo.h"
	#include "GuildManager.h"
	#include "Player.h"
	#include "Guild.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectGuildHandler::execute (CGSelectGuild* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature* pCreature = dynamic_cast<Creature*>(pGamePlayer->getCreature());

	// ������ ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );

	//try { Assert( pGuild != NULL ); } catch ( Throwable& t ) {
		//cout << "GuildID:" << (int)(pPacket->getGuildID()) << endl;
	//}
	//cout << "GuildCount:" << (int)(g_pGuildManager->getGuilds().size()) << endl;

	if (pGuild==NULL)
	{
		return;
	}

	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		GCShowGuildInfo gcShowGuildInfo;
		gcShowGuildInfo.setGuildID( pGuild->getID() );
		gcShowGuildInfo.setGuildName( pGuild->getName() );
		gcShowGuildInfo.setGuildState( pGuild->getState() );
		gcShowGuildInfo.setGuildMaster( pGuild->getMaster() );
		gcShowGuildInfo.setGuildMemberCount( pGuild->getActiveMemberCount() );
		gcShowGuildInfo.setGuildIntro( pGuild->getIntro() );
		gcShowGuildInfo.setJoinFee( 0 );

		pPlayer->sendPacket( &gcShowGuildInfo );

		//cout << gcShowGuildInfo.toString() << endl;
	}
	else if ( pGuild->getState() == Guild::GUILD_STATE_WAIT )
	{
		GCShowWaitGuildInfo gcShowWaitGuildInfo;
		gcShowWaitGuildInfo.setGuildID( pGuild->getID() );
		gcShowWaitGuildInfo.setGuildName( pGuild->getName() );
		gcShowWaitGuildInfo.setGuildState( pGuild->getState() );
		gcShowWaitGuildInfo.setGuildMaster( pGuild->getMaster() );
		gcShowWaitGuildInfo.setGuildMemberCount( pGuild->getActiveMemberCount() );
		gcShowWaitGuildInfo.setGuildIntro( pGuild->getIntro() );
		
		if (pCreature->isSlayer())
			gcShowWaitGuildInfo.setJoinFee( REQUIRE_SLAYER_SUBMASTER_GOLD );
		else if (pCreature->isVampire())
			gcShowWaitGuildInfo.setJoinFee( REQUIRE_VAMPIRE_SUBMASTER_GOLD );
		else if (pCreature->isOusters())
			gcShowWaitGuildInfo.setJoinFee( REQUIRE_OUSTERS_SUBMASTER_GOLD );

		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberConstItor itr = Members.begin();
		for ( ; itr != Members.end(); itr++ )
			gcShowWaitGuildInfo.addMember( itr->first );

		pPlayer->sendPacket( &gcShowWaitGuildInfo );

		//cout << gcShowWaitGuildInfo.toString() << endl;
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

