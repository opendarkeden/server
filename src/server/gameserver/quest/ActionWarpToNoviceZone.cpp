////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpToNoviceZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWarpToNoviceZone.h"
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

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionWarpToNoviceZone::read (PropertyBuffer & pb)
    
{
    __BEGIN_TRY

	try 
	{
		m_NoviceZoneID = pb.getPropertyInt("NoviceZoneID");
		m_NoviceX      = pb.getPropertyInt("NoviceX");
		m_NoviceY      = pb.getPropertyInt("NoviceY");

		m_BeginnerZoneID = pb.getPropertyInt("BeginnerZoneID");
		m_BeginnerX      = pb.getPropertyInt("BeginnerX");
		m_BeginnerY      = pb.getPropertyInt("BeginnerY");
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
void ActionWarpToNoviceZone::execute (Creature * pNPC , Creature * pCreature) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	if ( !pCreature->isSlayer() ) return;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	ZoneID_t ZoneID = pSlayer->getZoneID();
	ZoneCoord_t	X = pSlayer->getX();
	ZoneCoord_t Y = pSlayer->getY();
	Attr_t totalAttr = pSlayer->getTotalAttr( ATTR_BASIC );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

	bool bTransport = true;

	if ( totalAttr <= 40 )
	{
		ZoneID = m_NoviceZoneID;
		X = m_NoviceX;
		Y = m_NoviceY;
	}
	else if ( totalAttr <= 60 )
	{
		ZoneID = m_BeginnerZoneID;
		X = m_BeginnerX;
		Y = m_BeginnerY;
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_BEGINNER ) );
		pGamePlayer->sendPacket (&gcSystemMessage);

		bTransport = false;
	}

	//Zone* pZone = pCreature->getZone();


#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( ZoneID );

		// 유료존인데 유료사용자가 아니면...
		if (pZoneInfo==NULL
			|| pZoneInfo->isPayPlay() && !pGamePlayer->isPayPlaying())
		{
			string connectIP = pGamePlayer->getSocket()->getHost();

			// 유료 서비스 사용이 가능한가?
			if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
			{
				sendPayInfo(pGamePlayer);
			}
			else
			{
				// 유료 서비스 사용 불가인 경우
				GCSystemMessage gcSystemMessage;

				if (g_pConfig->getPropertyInt("IsNetMarble")==0)
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER_PAY_ZONE) );
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER) );
				}

				pGamePlayer->sendPacket (&gcSystemMessage);

				bTransport = false;
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if (bTransport)
	{
		transportCreature(pCreature, ZoneID, X, Y, true);
	}
	else
	{
		if ( pNPC != NULL )
		{
			GCNPCResponse response;
			response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pGamePlayer->sendPacket(&response);
		}
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWarpToNoviceZone::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionWarpToNoviceZone("
	    << "NoviceZoneID:" << (int)m_NoviceZoneID
	    << ",NoviceX:"  << (int)m_NoviceX
	    << ",NoviceY:"  << (int)m_NoviceY
	    << "BeginnerZoneID:" << (int)m_BeginnerZoneID
	    << ",BeginnerX:"  << (int)m_BeginnerX
	    << ",BeginnerY:"  << (int)m_BeginnerY
	    << ")";
	return msg.toString();

	__END_CATCH
}

