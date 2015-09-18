////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterSiege.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterSiege.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "StringPool.h"
#include "Zone.h"
#include "WarScheduler.h"
#include "ZoneUtil.h"
#include "WarSchedule.h"
#include "WarSystem.h"
#include "SiegeWar.h"
#include "SiegeManager.h"
#include "GuildManager.h"
#include "EventTransport.h"
#include "CreatureUtil.h"
#include "WarSystem.h"

#include <stdio.h>

#include "GCUpdateInfo.h"
#include "GCMoveOK.h"
#include "GCSystemMessage.h"
#include "GCNPCResponse.h"
#include "GCModifyInformation.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterSiege::read (PropertyBuffer & pb)
    throw(Error)
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
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
void ActionEnterSiege::execute (Creature * pNPC , Creature * pCreature) 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	if (!g_pWarSystem->hasCastleActiveWar(m_ZoneID ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("공선전 중에만 입장하실 수 있습니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert(pPC != NULL);

	Zone* pZone = getZoneByZoneID(m_ZoneID);
	Assert(pZone != NULL);

	WarScheduler* pWS = pZone->getWarScheduler();
	Assert(pWS != NULL);

	ZoneID_t siegeZoneID = SiegeManager::Instance().getSiegeZoneID(m_ZoneID);
	Assert(siegeZoneID != 0);

/*	WarSchedule* pSchedule = dynamic_cast<WarSchedule*>(pWS->getRecentSchedule());
	if (pSchedule == NULL )
	{
		return;
	}*/

	SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(g_pWarSystem->getActiveWar(m_ZoneID ));
	if (pSiegeWar == NULL )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("타입 1 서버 오류입니다. 운영팀에 문의하세요.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}

	int side = pSiegeWar->getGuildSide(pPC->getGuildID());
	if (side == 0 )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("전쟁에 참가한 길드가 아닙니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}
	
	if (!g_pGuildManager->isGuildMaster(pPC->getGuildID(), pPC ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage("길드 마스터만 가능합니다.");
		pGamePlayer->sendPacket(&gcSM);
		return;
	}

	static TPOINT targetPos[7] =
	{
		{172, 38},
		{172, 38},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232}
	};

	// 소환자의 존과 좌표.
	ZoneID_t ZoneNum = siegeZoneID;
	Coord_t ZoneX = targetPos[side-1].x;
	Coord_t ZoneY = targetPos[side-1].y;

	for (int i=0; i<7; ++i )
	{
		deleteCreatureEffect(pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + i));
	}

	if (side < 8 && side > 0 )
	{
		//cout << "side : " << side << endl;
		addSimpleCreatureEffect(pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + side - 1));
	}

	EventTransport* pEvent = dynamic_cast<EventTransport*>(pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT));
	bool newEvent = false;
	if (pEvent==NULL)
	{
		pEvent = new EventTransport(pGamePlayer);
		newEvent = true;
	}

//		pEvent = new EventTransport(pGamePlayer);
	pEvent->setTargetZone(ZoneNum, ZoneX, ZoneY);
	pEvent->setDeadline(0);

	if (newEvent )
		pGamePlayer->addEvent(pEvent);

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterSiege::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterSiege("
	    << ")";
	return msg.toString();

	__END_CATCH
}

