//----------------------------------------------------------------------
//
// Filename    : GSGuildMemberLogOnHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSGuildMemberLogOn.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"

	#include "Spackets/SGGuildMemberLogOnOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSGuildMemberLogOnHandler::execute()
// 
//----------------------------------------------------------------------
void GSGuildMemberLogOnHandler::execute ( GSGuildMemberLogOn* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 길드의 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	pGuildMember->setLogOn( pPacket->getLogOn() );

	// 게임 서버로 보낼 패킷을 만든다.
	SGGuildMemberLogOnOK sgGuildMemberLogOnOK;
	sgGuildMemberLogOnOK.setGuildID( pGuild->getID() );
	sgGuildMemberLogOnOK.setName( pPacket->getName() );
	sgGuildMemberLogOnOK.setLogOn( pPacket->getLogOn() );
	sgGuildMemberLogOnOK.setServerID( pPacket->getServerID() );


	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgGuildMemberLogOnOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
