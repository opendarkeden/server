////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDenyReinforce.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionDenyReinforce.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "GuildWar.h"
#include "SiegeWar.h"
#include "WarScheduler.h"
#include "WarSchedule.h"
#include "GuildManager.h"
#include "Guild.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "PlayerCreature.h"
#include "VariableManager.h"
#include "Properties.h"
#include "CastleInfoManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionDenyReinforce::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionDenyReinforce::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

#ifndef __OLD_GUILD_WAR__

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_GUILD_WAR );

	GCNPCResponse gcNPCResponse;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );
	GuildID_t guildID = pPC->getGuildID();

	if ( !g_pVariableManager->isWarActive() || !g_pVariableManager->isActiveGuildWar() )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_UNAVAILABLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	if ( !g_pGuildManager->isGuildMaster( guildID, pPC ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_GUILD_MASTER );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	Zone* pZone = getZoneByZoneID( m_ZoneID );
	Assert( pZone != NULL );
	Assert( pZone->isCastle() );

	WarScheduler* pWarScheduler = pZone->getWarScheduler();
	Assert( pWarScheduler != NULL );

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_ZoneID );
	GuildID_t ownerGuildID = pCastleInfo->getGuildID();

	if ( guildID != ownerGuildID )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_YOUR_CASTLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	Schedule* pNextSchedule = pWarScheduler->getRecentSchedule();

	Work* pNextWork = NULL;
	if ( pNextSchedule != NULL ) pNextWork = pNextSchedule->getWork();

	SiegeWar* pNextWar = dynamic_cast<SiegeWar*>(pNextWork);

	if ( pNextWar == NULL || pNextWar->recentReinforceCandidate() == 0 )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NO_WAR_REGISTERED );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		//SAFE_DELETE( pNextWar );
		return;
	}
	else if ( pNextWar->getReinforceGuildID() == 0 )
	{
		WarSchedule* pNextWarSchedule = dynamic_cast<WarSchedule*>(pNextSchedule);
		Assert( pNextWarSchedule != NULL );

		if ( !pNextWar->denyReinforce() )
		{
			gcNPCResponse.setCode( NPC_RESPONSE_CANNOT_ACCEPT );
			pPC->getPlayer()->sendPacket( &gcNPCResponse );

			//SAFE_DELETE( pNextWar );
			return;
		}
	}
	else
	{
		gcNPCResponse.setCode( NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		//SAFE_DELETE( pNextWar );
		return;
	}

	gcNPCResponse.setCode( NPC_RESPONSE_ACCEPT_OK );
	pPC->getPlayer()->sendPacket( &gcNPCResponse );

	gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPC->getPlayer()->sendPacket(&gcNPCResponse);

	return;

#endif

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionDenyReinforce::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionDenyReinforce("
	    << ",ZoneID:"  << (int)m_ZoneID
	    << ")";

	return msg.toString();

	__END_CATCH
}
