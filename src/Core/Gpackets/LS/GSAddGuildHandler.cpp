//----------------------------------------------------------------------
//
// Filename    : GSAddGuildHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSAddGuild.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"

	#include "Spackets/SGAddGuildOK.h"
	#include "Spackets/SGAddGuildMemberOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSAddGuildHandler::execute()
// 
//----------------------------------------------------------------------
void GSAddGuildHandler::execute ( GSAddGuild* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// 현재 길드의 맥스 ID + 1 을 길드 ID 로 하고 맥스 ID 를 증가 시킨다
	GuildID_t GuildID = Guild::getMaxGuildID() + 1;
	Guild::setMaxGuildID( GuildID );

	ZoneID_t zoneID;

	//cout << pPacket->toString().c_str() << endl;

	// 맥스 존 ID 를 구한다.
	if ( pPacket->getGuildRace() == Guild::GUILD_RACE_SLAYER )
	{
		zoneID = Guild::getMaxSlayerZoneID();
		Guild::setMaxSlayerZoneID( zoneID + 1 );
	}
	else if ( pPacket->getGuildRace() == Guild::GUILD_RACE_VAMPIRE )
	{
		zoneID = Guild::getMaxVampireZoneID();
		Guild::setMaxVampireZoneID( zoneID + 1 );
	}
	else if ( pPacket->getGuildRace() == Guild::GUILD_RACE_OUSTERS )
	{
		zoneID = Guild::getMaxOustersZoneID();
		Guild::setMaxOustersZoneID( zoneID + 1 );
	}
	else
	{
		return;
	}

	// Guild Object 를 만든다
	Guild* pGuild = new Guild();
	pGuild->setID( GuildID );
	pGuild->setName( pPacket->getGuildName() );
	pGuild->setRace( pPacket->getGuildRace() );
	pGuild->setState( pPacket->getGuildState() );
	pGuild->setServerGroupID( pPacket->getServerGroupID() );
	pGuild->setZoneID( zoneID );
	pGuild->setMaster( pPacket->getGuildMaster() );
	pGuild->setIntro( pPacket->getGuildIntro() );

	// 만든 길드를 디비에 넣는다
	pGuild->create();

	// 길드 매니저에 추가한다.
	g_pGuildManager->addGuild( pGuild );

	// 마스터를 길드 멤버로 추가한다.
	GuildMember* pGuildMember = new GuildMember();
	pGuildMember->setGuildID( pGuild->getID() );
	pGuildMember->setName( pGuild->getMaster() );
	pGuildMember->setRank( GuildMember::GUILDMEMBER_RANK_MASTER );

	// DB 에 Guild Member 를 저장한다.
	pGuildMember->create();

	// 길드에 추가한다.
	pGuild->addMember( pGuildMember );

	// 게임 서버로 보낼 패킷을 만든다.
	SGAddGuildOK sgAddGuildOK;
	sgAddGuildOK.setGuildID( pGuild->getID() );
	sgAddGuildOK.setGuildName( pGuild->getName() );
	sgAddGuildOK.setGuildRace( pGuild->getRace() );
	sgAddGuildOK.setGuildState( pGuild->getState() );
	sgAddGuildOK.setServerGroupID( pGuild->getServerGroupID() );
	sgAddGuildOK.setGuildZoneID( pGuild->getZoneID() );
	sgAddGuildOK.setGuildMaster( pGuild->getMaster() );
	sgAddGuildOK.setGuildIntro( pGuild->getIntro() );

	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgAddGuildOK );

	SGAddGuildMemberOK sgAddGuildMemberOK;
	sgAddGuildMemberOK.setGuildID( pGuildMember->getGuildID() );
	sgAddGuildMemberOK.setName( pGuildMember->getName() );
	sgAddGuildMemberOK.setGuildMemberRank( pGuildMember->getRank() );
	sgAddGuildMemberOK.setServerGroupID( pPacket->getServerGroupID() );

	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgAddGuildMemberOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
