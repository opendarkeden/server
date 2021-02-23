////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRecallSiege.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRecallSiege.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "StringPool.h"
#include "Zone.h"
#include "WarScheduler.h"
#include "ZoneUtil.h"
#include "WarSchedule.h"
#include "SiegeWar.h"
#include "SiegeManager.h"
#include "Guild.h"
#include "GuildManager.h"
#include "EventTransport.h"
#include "CreatureUtil.h"
#include "WarSystem.h"

#include <stdio.h>

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCGuildMemberList.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionRecallSiege::read (PropertyBuffer & pb)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 咀记阑 角青茄促.
////////////////////////////////////////////////////////////////////////////////
void ActionRecallSiege::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

/*	if ( !g_pWarSystem->hasCastleActiveWar( m_ZoneID ) )
	{
		return;
	}*/

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert( pPC != NULL );

	Zone* pZone = getZoneByZoneID( m_ZoneID );
	Assert( pZone != NULL );

	WarScheduler* pWS = pZone->getWarScheduler();
	Assert( pWS != NULL );

	ZoneID_t siegeZoneID = SiegeManager::Instance().getSiegeZoneID( m_ZoneID );
	Assert(siegeZoneID != 0 );

/*	WarSchedule* pSchedule = dynamic_cast<WarSchedule*>(pWS->getRecentSchedule());
	if ( pSchedule == NULL )
	{
		return;
	}

	SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pSchedule->getWork());
	if ( pSiegeWar == NULL )
	{
		return;
	}

	int side = pSiegeWar->getGuildSide( pPC->getGuildID() );
	if ( side == 0 )
	{
		return;
	}*/
	
	if ( !g_pGuildManager->isGuildMaster( pPC->getGuildID(), pPC ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "只有行会会长,才可以进行申请.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

	// 急琶茄 辨靛甫 啊廉柯促.
	Guild* pGuild = g_pGuildManager->getGuild( pPC->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL)
		return;

	GCGuildMemberList gcGuildMemberList;

	pGuild->makeMemberInfo( gcGuildMemberList );
	gcGuildMemberList.setType(1);

	pGamePlayer->sendPacket( &gcGuildMemberList );

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRecallSiege::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRecallSiege("
	    << ")";
	return msg.toString();

	__END_CATCH
}

