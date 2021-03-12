////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionForceApartCouple.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionForceApartCouple.h"
#include "SystemAvailabilitiesManager.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionForceApartCouple::read (PropertyBuffer & propertyBuffer)
    
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
void ActionForceApartCouple::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_COUPLE );

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_APART_COUPLE_FORCE );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCResponse);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionForceApartCouple::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionForceApartCouple("
	    << ")";

	return msg.toString();

	__END_CATCH
}
