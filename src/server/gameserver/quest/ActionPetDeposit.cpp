////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPetDeposit.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionQuitDialogue.h"
#include "ActionPetDeposit.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "PacketUtil.h"
#include "Gpackets/GCPetStashList.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionPetDeposit::read (PropertyBuffer & propertyBuffer)
    
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
void ActionPetDeposit::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	/* 팻보관함이 뜨기 전에 대화창을 닫아주어야 하기에 날린다.*/
	GCNPCResponse response;
    response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
    pPC->getPlayer()->sendPacket(&response);
	
	gcPetStashList.setCode(1);
	pPC->getPlayer()->sendPacket( &gcPetStashList );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPetDeposit::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionPetDeposit("
	    << ")";

	return msg.toString();

	__END_CATCH
}
