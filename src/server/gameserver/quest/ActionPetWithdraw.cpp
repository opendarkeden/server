////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPetWithdraw.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionPetWithdraw.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "PacketUtil.h"
#include "Gpackets/GCPetStashList.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionPetWithdraw::read (PropertyBuffer & propertyBuffer)
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
void ActionPetWithdraw::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	GCPetStashList gcPetStashList;
	makeGCPetStashList( &gcPetStashList, pPC );

	gcPetStashList.setCode(0);
	pPC->getPlayer()->sendPacket( &gcPetStashList );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPetWithdraw::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionPetWithdraw("
	    << ")";

	return msg.toString();

	__END_CATCH
}
