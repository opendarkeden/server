////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeExit.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionActivateMazeExit.h"
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
#include "EffectRefiniumTicket.h"
#include "PlayerCreature.h"

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionActivateMazeExit::read (PropertyBuffer & pb)
    
{
    __BEGIN_TRY

	try 
	{
		m_GoodZoneID = pb.getPropertyInt("GoodZoneID");
		m_GoodX      = pb.getPropertyInt("GoodX");
		m_GoodY      = pb.getPropertyInt("GoodY");
		m_BadZoneID = pb.getPropertyInt("BadZoneID");
		m_BadX      = pb.getPropertyInt("BadX");
		m_BadY      = pb.getPropertyInt("BadY");

		m_ExitID	= pb.getPropertyInt("ExitID");
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
void ActionActivateMazeExit::execute (Creature * pNPC , Creature * pCreature) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	// 미로 출구는 유료존 체크 안하고 보내준다. 젠장 -_-
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	bool isCorrect = false;

	if ( !pPC->isFlag( Effect::EFFECT_CLASS_REFINIUM_TICKET ) )
	{
		filelog("EventBug.log", "미로 안에 있는데 리피늄 티켓이 없어. 로그아웃하는수밖에.. : %s", pPC->getName().c_str());
	}
	else
	{
		EffectRefiniumTicket* pEffect = dynamic_cast<EffectRefiniumTicket*>(pPC->findEffect( Effect::EFFECT_CLASS_REFINIUM_TICKET ));
		if ( pEffect != NULL )
		{
			isCorrect = ((int)pEffect->getExit() == (int)m_ExitID);
			if ( isCorrect ) pEffect->setDeadline(0);
			else
			{
				pEffect->setPrevExitZoneID( pPC->getZoneID() );
				pEffect->setPrevExitX( pPC->getX() );
				pEffect->setPrevExitY( pPC->getY() );
			}
		}
	}

	if (isCorrect)
	{
		transportCreature(pCreature, m_GoodZoneID, m_GoodX, m_GoodY, true);
	}
	else
	{
		transportCreature(pCreature, m_BadZoneID, m_BadX, m_BadY, true);
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionActivateMazeExit::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionActivateMazeExit("
	    << "GoodZoneID:" << (int)m_GoodZoneID
	    << ",GoodX:"  << (int)m_GoodX
	    << ",GoodY:"  << (int)m_GoodY
	    << ",BadZoneID:" << (int)m_BadZoneID
	    << ",BadX:"  << (int)m_BadX
	    << ",BadY:"  << (int)m_BadY
		<< ",ExitID:" << (int)m_ExitID
	    << ")";
	return msg.toString();

	__END_CATCH
}

