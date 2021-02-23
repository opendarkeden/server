////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAcceptApartCouple.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionAcceptApartCouple.h"
#include "SystemAvailabilitiesManager.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"

#include "couple/PartnerWaitingManager.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionAcceptApartCouple::read (PropertyBuffer & propertyBuffer)
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
void ActionAcceptApartCouple::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_COUPLE );

	GCNPCResponse gcNPCResponse;

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	Assert( pNPC != NULL );
	Assert( pPC != NULL );

	PartnerWaitingManager *pPWM = pNPC->getCoupleUnregisterManager();
	Assert( pPWM != NULL );

	PlayerCreature* pWaitingPC = pPWM->getWaitingPartner( pPC );

	uint result = pPWM->acceptPartner( pPC );
	if ( result != 0 )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_COUPLE );
		gcNPCResponse.setParameter( result );
	}
	else
	{
		gcNPCResponse.setCode( NPC_RESPONSE_COUPLE_APART_SUCCESS );
	}

	pPC->getPlayer()->sendPacket( &gcNPCResponse );

	if ( pWaitingPC != NULL )
		pWaitingPC->getPlayer()->sendPacket( &gcNPCResponse );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionAcceptApartCouple::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionAcceptApartCouple("
	    << ")";

	return msg.toString();

	__END_CATCH
}
