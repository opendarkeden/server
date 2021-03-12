////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSystemMessage.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSystemMessage.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Gpackets/GCSystemMessage.h"

#include "StringPool.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionSystemMessage::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		m_Content = propertyBuffer.getPropertyInt("Content");
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
void ActionSystemMessage::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(g_pStringPool->getString(m_Content));
	pPlayer->sendPacket(&gcSystemMessage);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSystemMessage::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSystemMessage("
		<< "Content:" << m_Content
		<< ")";
	return msg.toString();

	__END_CATCH
}
