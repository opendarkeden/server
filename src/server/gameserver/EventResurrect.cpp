//////////////////////////////////////////////////////////////////////////////
// Filename    : EventResurrect.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventResurrect.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "IncomingPlayerManager.h"
#include "ZonePlayerManager.h"
#include "Slayer.h"
#include "PCSlayerInfo2.h"
#include "Vampire.h"
#include "PCVampireInfo2.h"
#include "Ousters.h"
#include "TimeManager.h"
#include "PlayerStatus.h"

#include "PacketUtil.h"

#include "Gpackets/GCUpdateInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class EventResurrect member methods
//////////////////////////////////////////////////////////////////////////////

EventResurrect::EventResurrect(GamePlayer* pGamePlayer) 
	
: Event(pGamePlayer)
{
//	m_pResurrectZone = NULL;
//	m_X = m_Y = 0;
}

EventResurrect::~EventResurrect() 
	
{
}

void EventResurrect::activate () 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(m_pGamePlayer != NULL);

	Creature * pDeadPC = m_pGamePlayer->getCreature();

	Assert(pDeadPC != NULL);

	// 하이드한 상태에서 죽었다면, 하이드를 풀어준다.
	pDeadPC->removeFlag(Effect::EFFECT_CLASS_HIDE);

	// 무브모드를 바꿔준다.
	if (pDeadPC->isVampire() && pDeadPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
	{
		pDeadPC->setMoveMode(Creature::MOVE_MODE_FLYING);
	}
	else
	{
		pDeadPC->setMoveMode(Creature::MOVE_MODE_WALKING);
	}

	// HP를 채워준다.
	if (pDeadPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pDeadPC);
		pSlayer->setHP(pSlayer->getHP(ATTR_MAX), ATTR_CURRENT);
	}
	else if (pDeadPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pDeadPC);
		pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
	}
	else if (pDeadPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pDeadPC);
		pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
	}

	// 새 zone을 설정하지 않는다. by sigi. 2002.5.11
	Zone* pOldZone = pDeadPC->getZone();
	Assert(pOldZone != NULL);

	try 
	{
		// 존그룹의 ZPM에서 플레이어를 삭제한다.
		pOldZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(m_pGamePlayer->getSocket()->getSOCKET());

		// 여기서 설정해줘야지만 Save 이벤트가 IPM에서 동작하지 않는다.
		m_pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);

		// IPM으로 플레이어를 옮긴다.
		//g_pIncomingPlayerManager->pushPlayer(m_pGamePlayer);
		pOldZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(m_pGamePlayer);

	} 
	catch (NoSuchElementException& t) 
	{
		filelog("eventRessurect.txt", "%s-%s", t.toString().c_str(), pDeadPC->getName().c_str());
		cerr << "EventResurrect::activate() : NoSuchElementException" << endl;
		//throw Error("존에 플레이어가 존재하지 않습니다.");
		// 어떻게 없어졌겠지.. -_-;
		// 무시하고.. 그냥 진행한다.
		// by sigi. 2002.11.25
	}

	// 죽었을 당시 killCreature에서 존을 셋팅 하기 때문에 그냥 할당 받으면 된다.

	// 이거는 ZonePlayerManager의 heartbeat에서 처리한다.
	// 주석처리 by sigi. 2002.5.14
	//pDeadPC->registerObject();

	/*
	// GCUpdateInfo 패킷을 만들어둔다.
	GCUpdateInfo gcUpdateInfo;

	makeGCUpdateInfo(&gcUpdateInfo, pDeadPC);
	
	m_pGamePlayer->sendPacket(&gcUpdateInfo);
	*/

	__END_DEBUG
	__END_CATCH
}

string EventResurrect::toString () const 
	
{
	StringStream msg;
	msg << "EventResurrect("
		<< ")";
	return msg.toString();
}
