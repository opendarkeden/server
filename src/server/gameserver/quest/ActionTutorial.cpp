////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTutorial.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionTutorial.h"
#include "Creature.h"
#include "Gpackets/GCNPCResponse.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTutorial::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_Interface = propertyBuffer.getProperty("Interface");

		if (m_Interface != "COMPUTER" && 
			m_Interface != "BRIEFING" && 
			m_Interface != "BOOKCASE") 
		{
			throw Error("ActionTutorial::read() : Unknown interface type");
		}
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
void ActionTutorial::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	GCNPCResponse pkt;

	if (m_Interface == "COMPUTER")
	{
		pkt.setCode(NPC_RESPONSE_INTERFACE_TUTORIAL_COMPUTER);
	}
	else if (m_Interface == "BRIEFING")
	{
		pkt.setCode(NPC_RESPONSE_INTERFACE_TUTORIAL_BRIEFING);
	}
	else if (m_Interface == "BOOKCASE")
	{
		pkt.setCode(NPC_RESPONSE_INTERFACE_TUTORIAL_BOOKCASE);
	}

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&pkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTutorial::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionTutorial("
		<< "Interface : " << m_Interface
	    << ")";

	return msg.toString();

	__END_CATCH
}
