////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSay.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSay.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCSay.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionSay::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");
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
void ActionSay::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC*    pNPC    = dynamic_cast<NPC*>(pCreature1);
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	GCNPCSay gcNPCSay;
	gcNPCSay.setObjectID(pNPC->getObjectID());
	gcNPCSay.setScriptID(m_ScriptID);
	gcNPCSay.setSubjectID(0);
	pPlayer->sendPacket(&gcNPCSay);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSay::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSay("
		<< ",ScriptID:"  << (int)m_ScriptID
		<< ")";
	return msg.toString();

	__END_CATCH
}
