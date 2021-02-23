////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWaitForMeetCouple.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWaitForMeetCouple.h"
#include "SystemAvailabilitiesManager.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionWaitForMeetCouple::read (PropertyBuffer & propertyBuffer)
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
void ActionWaitForMeetCouple::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_COUPLE );

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert( pNPC != NULL );

//	cout << "ActionWaitForMeeCouple(" << pNPC->getObjectID() << ")" << endl;

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_WAIT_FOR_MEET_COUPLE );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCResponse);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWaitForMeetCouple::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionWaitForMeetCouple("
	    << ")";

	return msg.toString();

	__END_CATCH
}
