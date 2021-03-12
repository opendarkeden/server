////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionClearBloodBible.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionClearBloodBible.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "StringPool.h"
#include "BloodBibleBonus.h"
#include "BloodBibleBonusManager.h"

#include "Gpackets/GCBloodBibleSignInfo.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionClearBloodBible::read (PropertyBuffer & propertyBuffer)
    
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
void ActionClearBloodBible::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert( pNPC != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	BloodBibleSignInfo* pInfo = pPC->getBloodBibleSign();
	pInfo->getList().clear();
	GCBloodBibleSignInfo gcInfo;
	gcInfo.setSignInfo( pInfo );
	pPlayer->sendPacket( &gcInfo );

	pPC->initAllStatAndSend();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionClearBloodBible::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionClearBloodBible("
	    << ")";

	return msg.toString();

	__END_CATCH
}
