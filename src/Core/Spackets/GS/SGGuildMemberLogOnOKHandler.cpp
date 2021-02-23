//----------------------------------------------------------------------
//
// Filename    : SGGuildMemberLogOnOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGGuildMemberLogOnOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"

#endif

//----------------------------------------------------------------------
// 
// SGGuildMemberLogOnOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGGuildMemberLogOnOKHandler::execute ( SGGuildMemberLogOnOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	// 길드 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }

	pGuildMember->setLogOn( pPacket->getLogOn() );
	pGuildMember->setServerID( pPacket->getServerID() );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
