////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterGDRLair.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterGDRLair.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "PCOustersInfo2.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
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
#include "GDRLairManager.h"

#include <stdio.h>

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterGDRLair::read (PropertyBuffer & pb)
    
{
    __BEGIN_TRY

	try 
	{
		m_PortalID = pb.getPropertyInt("PortalID");
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
void ActionEnterGDRLair::execute (Creature * pNPC , Creature * pCreature) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert( pPC != NULL );

	ZoneID_t zoneID;
	ZoneCoord_t X, Y;

	if ( m_PortalID == GDRLairManager::Instance().getCorrectPortal() )
	{
		zoneID = 1412;
		X = 142;
		Y = 169;
	}
	else
	{
		zoneID = 1411;
		X = 125;
		Y = 58;
	}

	bool bTransport = true;
#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( zoneID );

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
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER_PAY_ZONE ) );
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
				}

				pGamePlayer->sendPacket (&gcSystemMessage);

				bTransport = false;

				return;
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if (bTransport)
	{
		if ( pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert( pSlayer != NULL );

			// 오토바이를 타고 있으면 오토바이에서 내린다.
			if ( pSlayer->hasRideMotorcycle() )
			{
				pSlayer->getOffMotorcycle();
			}
		}

		if ( pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			Assert( pOusters != NULL );

			// 실프 타고 있으면 내려준다
			if ( pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
			{
				Effect* pEffect = pOusters->findEffect(Effect::EFFECT_CLASS_SUMMON_SYLPH);
				if ( pEffect != NULL ) pEffect->setDeadline(0);
			}
		}

		if ( pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			Assert( pVampire != NULL );

			if ( pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT) )
			{
				addUntransformCreature( pVampire->getZone(), pVampire, true );
			}
		}

		Effect* pEffect = pPC->findEffect(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR);
		if ( pEffect != NULL ) pEffect->setDeadline(0);

		transportCreature(pCreature, zoneID, X, Y, true);
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
		pGamePlayer->sendPacket (&gcSystemMessage);
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterGDRLair::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterGDRLair("
	    << ")";
	return msg.toString();

	__END_CATCH
}

