////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterCastleWithFee.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterCastleWithFee.h"
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
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "StringPool.h"

#include <stdio.h>

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterCastleWithFee::read (PropertyBuffer & pb)
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
void ActionEnterCastleWithFee::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert( pPC != NULL );

	bool bTransport = true;
#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_ZoneID );

		// 유료존인데 유료사용자가 아니면...
		if (pZoneInfo==NULL
			|| pZoneInfo->isPayPlay() && !(pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass()))
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
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER_PAY_ZONE ) );
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
				}

				pGamePlayer->sendPacket (&gcSystemMessage);

				bTransport = false;
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if ( bTransport )
	{
		if ( g_pCastleInfoManager->isPossibleEnter( m_ZoneID, pPC ) )
		{
			Gold_t fee = g_pCastleInfoManager->getEntranceFee( m_ZoneID, pPC );
			Gold_t remain = pPC->getGold();

			if ( remain < fee )
			{
				static char buf[200];
				sprintf( buf, g_pStringPool->c_str( STRID_NOT_ENOUGH_ENTRANCE_FEE ), (int)fee );
				// 돈이 모자란다.
				GCSystemMessage message;
				message.setType( SYSTEM_MESSAGE_HOLY_LAND );
				message.setMessage( buf );
				pGamePlayer->sendPacket( &message );

				bTransport = false;
			}
			else
			{
				if ( fee > 0 )
				{
					// 입장료를 낸다.
					pPC->decreaseGoldEx( fee );
					g_pCastleInfoManager->increaseTaxBalance( m_ZoneID, fee );

					GCModifyInformation gcMI;
					gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );
					pGamePlayer->sendPacket( &gcMI );
				}
			}
		}
		else
		{
			GCSystemMessage message;
			message.setType( SYSTEM_MESSAGE_HOLY_LAND );
			message.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
			pGamePlayer->sendPacket( &message );

			bTransport = false;
		}
	}

	if (bTransport)
	{
		transportCreature(pCreature, m_ZoneID, m_X, m_Y, true);
	}
	else
	{
	    GCNPCResponse response;
	    response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	    pGamePlayer->sendPacket(&response);
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterCastleWithFee::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterCastleWithFee("
	    << "ZoneID:" << (int)m_ZoneID
	    << ",X:"  << (int)m_X
	    << ",Y:"  << (int)m_Y
	    << ")";
	return msg.toString();

	__END_CATCH
}

