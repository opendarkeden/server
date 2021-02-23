////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeReturn.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionActivateMazeReturn.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "Slayer.h"
#include "Vampire.h"
#include "WeatherManager.h"
#include "PaySystem.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "LogClient.h"
#include "PacketUtil.h"
#include "ZoneUtil.h"
#include "Properties.h"
#include "StringPool.h"
#include "EffectRefiniumTicket.h"

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionActivateMazeReturn::read (PropertyBuffer & pb)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
		m_X      = pb.getPropertyInt("X");
		m_Y      = pb.getPropertyInt("Y");
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
void ActionActivateMazeReturn::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	if ( pCreature->isFlag( Effect::EFFECT_CLASS_REFINIUM_TICKET ) )
	{
		EffectRefiniumTicket* pEffect = dynamic_cast<EffectRefiniumTicket*>(pCreature->findEffect( Effect::EFFECT_CLASS_REFINIUM_TICKET ));

		if ( pEffect != NULL )
		{
			ZoneID_t ZoneID = pEffect->getPrevExitZoneID();
			ZoneCoord_t X = pEffect->getPrevExitX();
			ZoneCoord_t Y = pEffect->getPrevExitY();

			transportCreature(pCreature, ZoneID, X, Y, true);
			return;
		}
	}

	transportCreature(pCreature, m_ZoneID, m_X, m_Y, true);

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionActivateMazeReturn::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionActivateMazeReturn("
	    << "ZoneID:" << (int)m_ZoneID
	    << ",X:"  << (int)m_X
	    << ",Y:"  << (int)m_Y
	    << ")";
	return msg.toString();

	__END_CATCH
}

