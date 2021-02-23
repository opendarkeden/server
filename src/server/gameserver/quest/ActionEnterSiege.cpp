////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterSiege.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterSiege.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "StringPool.h"
#include "Zone.h"
#include "WarScheduler.h"
#include "ZoneUtil.h"
#include "WarSchedule.h"
#include "WarSystem.h"
#include "SiegeWar.h"
#include "SiegeManager.h"
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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterSiege::read (PropertyBuffer & pb)
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
void ActionEnterSiege::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	if ( !g_pWarSystem->hasCastleActiveWar( m_ZoneID ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "只能在进行攻城战中进入.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

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
	}*/

	SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(g_pWarSystem->getActiveWar( m_ZoneID ));
	if ( pSiegeWar == NULL )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "第1个服务器发生故障，请与运营商联系.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

	int side = pSiegeWar->getGuildSide( pPC->getGuildID() );
	if ( side == 0 )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "不是申请战斗的行会.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}
	
	if ( !g_pGuildManager->isGuildMaster( pPC->getGuildID(), pPC ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "只有行会会长,才可以进行申请.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

	static TPOINT targetPos[7] =
	{
		{172, 38},
		{172, 38},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232}
	};

	// 家券磊狼 粮苞 谅钎.
	ZoneID_t ZoneNum = siegeZoneID;
	Coord_t ZoneX = targetPos[side-1].x;
	Coord_t ZoneY = targetPos[side-1].y;

	for ( int i=0; i<7; ++i )
	{
		deleteCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + i) );
	}

	if ( side < 8 && side > 0 )
	{
		cout << "side : " << side << endl;
		addSimpleCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + side - 1) );
	}

	EventTransport* pEvent = dynamic_cast<EventTransport*>(pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT));
	bool newEvent = false;
	if (pEvent==NULL)
	{
		pEvent = new EventTransport(pGamePlayer);
		newEvent = true;
	}

//		pEvent = new EventTransport(pGamePlayer);
	pEvent->setTargetZone( ZoneNum, ZoneX, ZoneY );
	pEvent->setDeadline(0);

	if ( newEvent )
		pGamePlayer->addEvent( pEvent );

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterSiege::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterSiege("
	    << ")";
	return msg.toString();

	__END_CATCH
}

