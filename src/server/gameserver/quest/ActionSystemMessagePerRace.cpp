////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSystemMessagePerRace.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSystemMessagePerRace.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "StringPool.h"
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionSystemMessagePerRace::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSystemMessagePerRace::execute (Creature * pCreature1, Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCSystemMessage gcSystemMessage;

	if ( pCreature2->isSlayer() )
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_CANNOT_ENTER_SUM_NEWBIE_ZONE));
	else
		gcSystemMessage.setMessage(g_pStringPool->getString(STRID_CANNOT_ENTER_LEVEL_NEWBIE_ZONE));

	pPlayer->sendPacket(&gcSystemMessage);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSystemMessagePerRace::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSystemMessagePerRace("
		<< ")";
	return msg.toString();

	__END_CATCH
}
