//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGetOffMotorCycleHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGGetOffMotorCycle.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"

	#include "item/Motorcycle.h"
	#include "ctf/FlagManager.h"

	#include "Gpackets/GCGetOffMotorCycle.h"
	#include "Gpackets/GCGetOffMotorCycleOK.h"
	#include "Gpackets/GCGetOffMotorCycleFailed.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGGetOffMotorCycleHandler::execute (CGGetOffMotorCycle* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	// 플레이어의 상태가 정상적인 상태인지를 검사한다.
	if (pGamePlayer->getPlayerStatus() != GPS_NORMAL)
	{
		GCGetOffMotorCycleFailed _GCGetOffMotorCycleFailed;
		pPlayer->sendPacket(&_GCGetOffMotorCycleFailed);
		return;
	}

	Creature* pCreature = pGamePlayer->getCreature();

	// 슬레이어이인지를 검사한다.
	if (!pCreature->isSlayer())
	{
		GCGetOffMotorCycleFailed _GCGetOffMotorCycleFailed;
		pPlayer->sendPacket(&_GCGetOffMotorCycleFailed);
		return;
	}

	Slayer*     pSlayer     = dynamic_cast<Slayer*>(pCreature);
	Motorcycle* pMotorcycle = pSlayer->getMotorcycle();
	bool        bSuccess    = false;
	Zone*       pZone       = pSlayer->getZone();

	// 오토바이를 타고 있다면...
	if (pMotorcycle != NULL)
	{
		ZoneCoord_t x     = pSlayer->getX();
		ZoneCoord_t y     = pSlayer->getY();

		// 일반 지역이 아니라면 (0이 일반 지역이다.), 운영자만이 내릴 수 있다.
		if (pZone->getZoneLevel(x, y) & SAFE_ZONE)
		{
			if (pSlayer->isGOD() || pSlayer->isDM()) bSuccess = true;
		}
		else if ( !g_pFlagManager->isInPoleField( ZONE_COORD( pZone->getZoneID(), x, y ) ) )
		{
			bSuccess = true;
		}
	}

	if (bSuccess) 
	{
		pSlayer->getOffMotorcycle();

		GCGetOffMotorCycle   _GCGetOffMotorCycle;
		GCGetOffMotorCycleOK _GCGetOffMotorCycleOK;

		_GCGetOffMotorCycle.setObjectID(pSlayer->getObjectID());

		pGamePlayer->sendPacket(&_GCGetOffMotorCycleOK);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCGetOffMotorCycle , pSlayer);
	}
	else
	{
		GCGetOffMotorCycleFailed _GCGetOffMotorCycleFailed;
		pPlayer->sendPacket(&_GCGetOffMotorCycleFailed);
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

