////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionInitPartnerWaitingManager.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionInitPartnerWaitingManager.h"
#include "SystemAvailabilitiesManager.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "couple/PartnerWaitingManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionInitPartnerWaitingManager::read (PropertyBuffer & propertyBuffer)
    
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
void ActionInitPartnerWaitingManager::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_COUPLE );

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert(pNPC != NULL);

	pNPC->setCoupleRegisterManager( new PartnerWaitingManager( WAIT_FOR_MEET ) );
	pNPC->setCoupleUnregisterManager( new PartnerWaitingManager( WAIT_FOR_APART ) );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionInitPartnerWaitingManager::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionInitPartnerWaitingManager("
	    << ")";

	return msg.toString();

	__END_CATCH
}
