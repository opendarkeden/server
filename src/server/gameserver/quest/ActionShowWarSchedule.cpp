////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowWarSchedule.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionShowWarSchedule.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "WarScheduler.h"
#include "GuildManager.h"
#include "Guild.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "PacketUtil.h"
#include "PlayerCreature.h"
#include "VariableManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCWarScheduleList.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionShowWarSchedule::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
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
void ActionShowWarSchedule::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );

	GCWarScheduleList gcWarScheduleList;

	if ( g_pVariableManager->isWarActive()
		&& makeGCWarScheduleList( &gcWarScheduleList, m_ZoneID ) )
	{
		pPC->getPlayer()->sendPacket( &gcWarScheduleList );
	}
	else
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionShowWarSchedule::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionShowWarSchedule("
	    << ",ZoneID:"  << (int)m_ZoneID
	    << ")";

	return msg.toString();

	__END_CATCH
}
