////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCheckPartnerName.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCheckPartnerName.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCSystemMessage.h"
#include "StringPool.h"
#include "FlagSet.h"
#include "PlayerCreature.h"

#include "couple/CoupleManager.h"

#include <cstdio>

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCheckPartnerName::read (PropertyBuffer & propertyBuffer)
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
void ActionCheckPartnerName::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	char buffer[256];
	string partnerName;

	if ( !pPC->getFlagSet()->isOn(FLAGSET_IS_COUPLE) || !g_pCoupleManager->getPartnerName(pPC, partnerName) )
	{
		sprintf(buffer, "%s", g_pStringPool->getString(STRID_NOT_COUPLE).c_str() );
	}
	else
	{
		sprintf(buffer, g_pStringPool->getString(STRID_COUPLE_IS).c_str(), partnerName.c_str() );
	}

	GCSystemMessage gcSM;
	gcSM.setMessage( buffer );

	pPC->getPlayer()->sendPacket( &gcSM );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCheckPartnerName::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCheckPartnerName("
	    << ")";

	return msg.toString();

	__END_CATCH
}
