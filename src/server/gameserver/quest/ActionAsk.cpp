////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAsk.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionAsk.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCAsk.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionAsk::read (PropertyBuffer & propertyBuffer)
    
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
void ActionAsk::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	GCNPCAsk gcNPCAsk;
	gcNPCAsk.setObjectID(pCreature1->getObjectID());
	gcNPCAsk.setScriptID(m_ScriptID);
	gcNPCAsk.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAsk);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionAsk::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionAsk("
	    << ",ScriptID:"  << (int)m_ScriptID
	    << ")";

	return msg.toString();

	__END_CATCH
}
