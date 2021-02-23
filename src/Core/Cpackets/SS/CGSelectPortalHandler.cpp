//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectPortalHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectPortal.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Vampire.h"
	#include "Slayer.h"
	#include "Portal.h"
	#include "Zone.h"
	#include "ZoneUtil.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectPortalHandler::execute(CGSelectPortal* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		// 게임 플레이어의 상태가 정상이 아니라면 걍 리턴한다.
		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature* pCreature = pGamePlayer->getCreature();
		Zone*     pZone     = pCreature->getZone();

		// 현재 크리쳐의 좌표가 비정상적이라면 리턴한다.
		if (!isValidZoneCoord(pZone, pCreature->getX(), pCreature->getY()))
			return;

		Tile & rTile = pZone->getTile(pCreature->getX() , pCreature->getY());

		// 만약 포탈이 있으면서, 크리처가 PC인 경우.. (몬스터와 NPC는 포탈 이동을 하지 않는다.)
		if (rTile.hasPortal()) 
		{
			Portal* pPortal = rTile.getPortal();

			if (pPortal->getPortalClass() == PORTAL_CLASS_MULTI) 
			{
				if (pCreature->isSlayer()) 
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					if (!pSlayer->hasRideMotorcycle() && (pPortal->getObjectType() == PORTAL_SLAYER)) 
					{
						pPortal->activate(pCreature, pPacket->getZoneID());
					}
				} 
				else 
				{
					if (pPortal->getObjectType() == PORTAL_NORMAL || pPortal->getObjectType() == PORTAL_SLAYER) 
					{
						pPortal->activate(pCreature , pPacket->getZoneID());
					}
				}
			}
		}
	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
