////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpToResurrectPosition.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWarpToResurrectPosition.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "ResurrectLocationManager.h"
#include "ZoneUtil.h"

#include "couple/PartnerWaitingManager.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionWarpToResurrectPosition::read (PropertyBuffer & propertyBuffer)
    throw (Error)
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
void ActionWarpToResurrectPosition::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	if ( pPC == NULL ) return;

	ZONE_COORD zoneCoord;
	g_pResurrectLocationManager->getPosition( pPC, zoneCoord );

	transportCreature( pCreature2, zoneCoord.id, zoneCoord.x, zoneCoord.y );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWarpToResurrectPosition::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionWarpToResurrectPosition("
	    << ")";

	return msg.toString();

	__END_CATCH
}
