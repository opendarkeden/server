////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionJoinRaceWar.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionJoinRaceWar.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "RaceWarLimiter.h"
#include "VariableManager.h"
#include "WarSystem.h"
#include "Properties.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionJoinRaceWar::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
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
void ActionJoinRaceWar::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_RACE_WAR );

	GCNPCResponse gcNPCResponse;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );

	static int isJoinRaceWar = g_pConfig->getPropertyInt("JoinRaceWar");

	// 서버 자체에 종족 전쟁 참가 신청 기능이 꺼져있는 경우
	if ( !isJoinRaceWar )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_RACE_WAR_GO_FIRST_SERVER );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		return;
	}

	if ( !g_pVariableManager->isWarActive()
		|| g_pWarSystem->hasActiveRaceWar())
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_UNAVAILABLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	if ( pCreature2->isFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_ALREADY_REGISTERED );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	if ( !RaceWarLimiter::getInstance()->join( pPC ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_RACE_WAR_JOIN_FAILED );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	gcNPCResponse.setCode( NPC_RESPONSE_RACE_WAR_JOIN_OK );
	pPC->getPlayer()->sendPacket( &gcNPCResponse );
	return;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionJoinRaceWar::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionJoinRaceWar("
	    << ")";

	return msg.toString();

	__END_CATCH
}
