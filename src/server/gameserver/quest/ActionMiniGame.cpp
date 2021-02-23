////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionMiniGame.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionMiniGame.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"

#include "Gpackets/GCNoticeEvent.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionMiniGame::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_GameType = propertyBuffer.getPropertyInt("GameType");
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
void ActionMiniGame::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode(NOTICE_EVENT_MINI_GAME);
	gcNoticeEvent.setParameter((uint)m_GameType);
//	gcNoticeEvent.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNoticeEvent);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionMiniGame::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionMiniGame("
	    << ",GameType:"  << (int)m_GameType
	    << ")";

	return msg.toString();

	__END_CATCH
}
