////////////////////////////////////////////////////////////////////////////////
// Filename    : MasterLairManager.h 
// Written By  : 쉭
// Description : 
////////////////////////////////////////////////////////////////////////////////


#include "MasterLairManager.h"
#include "MasterLairInfoManager.h"
#include "Assert.h"
#include "Zone.h"
#include "VariableManager.h"
#include "Timeval.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "PCManager.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemFactoryManager.h"
#include "EffectMasterLairPass.h"
#include "EffectContinualGroundAttack.h"
#include "PacketUtil.h"
#include "Player.h"
#include "MonsterCorpse.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "StringPool.h"

#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSay.h"

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////
MasterLairManager::MasterLairManager (Zone* pZone) 
	throw (Error)
{
	__BEGIN_TRY
		
	Assert(pZone != NULL);
	m_pZone = pZone;

	MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
	Assert(pInfo!=NULL);

	m_MasterID = 0;           // 마스터 한 마리 
	m_MasterX = 0;
	m_MasterY = 0;

	m_bMasterReady = false;      // 마스터가 싸울 준비가 되었나? 

	//m_nMaxSummonMonster = pInfo->getMaxSummonMonster(); // 마스터가 소환할 최대의 몬스터 수 
	//m_nSummonedMonster = 0;

	m_nMaxPassPlayer = pInfo->getMaxPassPlayer(); // 최대 출입 가능자 수
	m_nPassPlayer = 0;

	m_Event = EVENT_WAITING_REGEN;
	m_EventValue = 0;

	Timeval currentTime;
	getCurrentTime(currentTime);

	// 의미없당. - -;
	m_EventTime.tv_sec = currentTime.tv_sec + pInfo->getFirstRegenDelay();
	m_EventTime.tv_usec = 0;

	m_RegenTime.tv_sec = currentTime.tv_sec + pInfo->getFirstRegenDelay();
	m_RegenTime.tv_usec = 0;

	m_Mutex.setName("MasterLairManager");

	//cout << "Init MasterLairManager: zoneID=" << (int)m_pZone->getZoneID() << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// destructor
//
////////////////////////////////////////////////////////////////////////////////
MasterLairManager::~MasterLairManager () 
	throw ()
{
	__BEGIN_TRY

	__END_CATCH
}
	
////////////////////////////////////////////////////////////////////////////////
//
// enterCreature ( Creature* )
//
////////////////////////////////////////////////////////////////////////////////
//
// Creature가 이 Zone(MasterLair)에 들어올 수 있는지 체크하고
// 들어올 수 있다면 들어왔다고 보고 체크해둔다.
//
// [조건]
//   - EVENT_WAITING_PLAYER, 
//     EVENT_MINION_COMBAT, 
//     EVENT_MASTER_COMBAT인 경우만 들어올 가능성이 있다.
//   - EffectMasterLairPass가 있고 현재 MasterLair의 것이 맞는 경우는 무조건 들어온다.
//   - EVENT_WAITING_PLAYER가 아니면 못 들어온다.
//   - 마스터가 없는 경우 m_nPassPlayer >= m_nMaxPassPlayer인 경우 못 들어옴
//
// 출입 가능한 캐릭터에게는 EffectMasterLairPass가 없다면
//   - m_nPassPlayer를 1증가시키고 EffectMasterLairPass를 붙여준다.
//   - EffectMasterLairPass의 지속 시간은 EVENT_MASTER_COMBAT이 끝나는 시간까지이다.
//
////////////////////////////////////////////////////////////////////////////////
bool MasterLairManager::enterCreature(Creature* pCreature)
	throw(Error)
{	
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	if (pCreature->isDM() || pCreature->isGOD())
	{
		m_Mutex.unlock();
			
		goto ENTER_OK;
	}

	if (m_Event!=EVENT_WAITING_PLAYER
		&& m_Event!=EVENT_MINION_COMBAT
		&& m_Event!=EVENT_MASTER_COMBAT)
	{
		//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: 지금은 들어갈 수 없는 모드" << endl;
		m_Mutex.unlock();
		return false;
	}

	EffectMasterLairPass* pPassEffect = NULL;

	// 현재 Zone의 EffectMasterLairPass를 갖고 있는가?
	if (pCreature->isFlag( Effect::EFFECT_CLASS_MASTER_LAIR_PASS ))
	{
		if (g_pVariableManager->isRetryMasterLair())
		{
			Effect* pEffect = pCreature->getEffectManager()->findEffect( Effect::EFFECT_CLASS_MASTER_LAIR_PASS );
			Assert(pEffect!=NULL);

			pPassEffect = dynamic_cast<EffectMasterLairPass*>(pEffect);

			if (pPassEffect->getZoneID()==m_pZone->getZoneID())
			{
				//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: " << pCreature->getName().c_str() << " has EffectPass" << endl;
				m_Mutex.unlock();

				goto ENTER_OK;
			}

			// 다른 Lair의 Pass다. - -;
			//cout << "[" << (int)m_pZone->getZoneID() << "] MMasterLairManager: " << pCreature->getName().c_str() << " has Wrong EffectPass" << endl;
		}
		else
		{
			//cout << "[" << (int)m_pZone->getZoneID() << "] MMasterLairManager: " << pCreature->getName().c_str() << " can't enter more" << endl;

			m_Mutex.unlock();
			return false;
		}
	}

	// 들어올 수 없는 경우
	if (m_Event!=EVENT_WAITING_PLAYER)
	{
		//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: Not WAITING_PLAYER: "
		//	<< m_pZone->getPCManager()->getSize() << " / " << m_nPassPlayer << "/" << m_nMaxPassPlayer << endl;

		m_Mutex.unlock();
		return false;
	}

	//if (m_nPassPlayer >= m_nMaxPassPlayer)
	if (m_nPassPlayer >= g_pVariableManager->getVariable(MASTER_LAIR_PLAYER_NUM))	// by sigi. 2002.12.31
	{
		//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: Already Maximum Players: "
			//<< m_pZone->getPCManager()->getSize() << " / " << m_nPassPlayer << "/" << m_nMaxPassPlayer << endl;

		m_Mutex.unlock();
		return false;
	}

	// 들어올 수 있다고 판단된 경우
	m_nPassPlayer ++;

	if (pPassEffect==NULL)
	{
		pPassEffect = new EffectMasterLairPass(pCreature, m_pZone->getZoneID());

		//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: " << pCreature->getName().c_str() << " received EffectPass: "
		//	<< m_pZone->getPCManager()->getSize() << " / " << m_nPassPlayer << "/" << m_nMaxPassPlayer << endl;
	}
	else
	{
		pPassEffect->setZoneID( m_pZone->getZoneID() );
	}

	pCreature->getEffectManager()->addEffect( pPassEffect );
	pCreature->setFlag( Effect::EFFECT_CLASS_MASTER_LAIR_PASS );
	
	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH

ENTER_OK :

	/*
	// Sniping 제거
	if (pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
	{
        EffectManager* pEffectManager = pCreature->getEffectManager();
        Assert(pEffectManager);
        pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_INVISIBILITY);
		pCreature->removeFlag(Effect::EFFECT_CLASS_INVISIBILITY);
	}

	// Invisibility제거
	if (pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
	{
        EffectManager* pEffectManager = pCreature->getEffectManager();
        Assert(pEffectManager!=NULL);
        pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_INVISIBILITY);
		pCreature->removeFlag(Effect::EFFECT_CLASS_INVISIBILITY);
	}
	*/

	if (m_Event==EVENT_MINION_COMBAT
		|| m_Event==EVENT_MASTER_COMBAT)
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

		int timeGap = m_EventTime.tv_sec - currentTime.tv_sec;

		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_MASTER_COMBAT_TIME );
		gcNoticeEvent.setParameter( timeGap );
		//m_pZone->broadcastPacket( &gcNoticeEvent );
		pCreature->getPlayer()->sendPacket( &gcNoticeEvent );
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// leaveCreature ( Creature* )
//
////////////////////////////////////////////////////////////////////////////////
//
// WaitingPlayer상태이면 PassPlayer를 하나 줄여준다.
//
// 마스터 레어에 다시 들어갈 수 없는 상태이면 EffectPass를 없애준다.
//
////////////////////////////////////////////////////////////////////////////////
bool MasterLairManager::leaveCreature(Creature* pCreature)
	throw(Error)
{	
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	if (pCreature->isDM() || pCreature->isGOD())
	{
		m_Mutex.unlock();
		return true;
	}

	// waiting player인 경우만 숫자를 줄인다.
	if (m_Event==EVENT_WAITING_PLAYER)
	{
		if (m_nPassPlayer>0) m_nPassPlayer--;
	}

	// 나간 경우(죽은 경우) 마스터 레어에 다시 돌아올 수 없는 모드..가 되어있다면
	// 나갈 때 EffectMasterLairPass를 제거한다.
	if (!g_pVariableManager->isRetryMasterLair())
	{
		if (pCreature->isFlag( Effect::EFFECT_CLASS_MASTER_LAIR_PASS ))
		{
			pCreature->getEffectManager()->deleteEffect( Effect::EFFECT_CLASS_MASTER_LAIR_PASS );
			pCreature->removeFlag( Effect::EFFECT_CLASS_MASTER_LAIR_PASS );
		}
	}
	
	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH

	//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager: " << pCreature->getName().c_str() << " leaved: "
	//		<< m_pZone->getPCManager()->getSize() << " / " << m_nPassPlayer << "/" << m_nMaxPassPlayer << endl;
	return true;
}



////////////////////////////////////////////////////////////////////////////////
//
// heartbeat
// 
////////////////////////////////////////////////////////////////////////////////
bool MasterLairManager::heartbeat() 
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	switch (m_Event)
	{
		case EVENT_WAITING_PLAYER :
			processEventWaitingPlayer();
		break;

		case EVENT_MINION_COMBAT :
			processEventMinionCombat();
		break;
		
		case EVENT_MASTER_COMBAT :
			processEventMasterCombat();
		break;

		case EVENT_WAITING_KICK_OUT :
			processEventWaitingKickOut();
		break;

		case EVENT_WAITING_REGEN :
			processEventWaitingRegen();
		break;

		default :
			break;
	}; 

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// process EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::processEventWaitingPlayer() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	// 대기 시간이 끝나면..
	// 마스터가 몬스터를 소환하기 하기 시작한다.
	if (currentTime >= m_EventTime)
	{
		// 마스터 레어가 열려있다고 사람들에게 알려준다.
//		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
//		Assert(pZoneInfo!=NULL);

//		StringStream msg;
//		msg << "마스터 레어(" << pZoneInfo->getFullName().c_str() << ")가 닫혔습니다.";

//        char msg[50];
 //       sprintf( msg, g_pStringPool->c_str( STRID_MASTER_LAIR_CLOSED ),
  //                      pZoneInfo->getFullName().c_str() );
//
 //       string sMsg( msg );
//
//		GCSystemMessage gcSystemMessage;
//		gcSystemMessage.setType(SYSTEM_MESSAGE_MASTER_LAIR);
//		gcSystemMessage.setMessage( sMsg );
//		g_pZoneGroupManager->broadcast( &gcSystemMessage );

		GCNoticeEvent gcNoticeEvent;

		gcNoticeEvent.setCode(NOTICE_EVENT_MASTER_LAIR_CLOSED);
		gcNoticeEvent.setParameter( m_pZone->getZoneID() );

		g_pZoneGroupManager->broadcast( &gcNoticeEvent );

		// Minion과의 싸움 시작
		activeEventMinionCombat();
	}
	else
	{ 
		int remainSec = m_EventTime.tv_sec - currentTime.tv_sec;

		// 1분 마다 한번씩 알린다.
		if (remainSec!=m_EventValue && remainSec!=0 && remainSec % 60 == 0)
		{
			// 마스터 레어가 열려있다고 사람들에게 알려준다.
//			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
//			Assert(pZoneInfo!=NULL);

//			StringStream msg;
//			msg << "마스터 레어(" << pZoneInfo->getFullName().c_str() << ") 출입 가능 시간이 "
//				<< (remainSec/60) << "분 남았습니다.";

//            char msg[100];
 //           sprintf( msg, g_pStringPool->c_str( STRID_MASTER_LAIR_OPENING_COUNT_DOWN ),
  //                          pZoneInfo->getFullName().c_str(),
   //                         (int)(remainSec/60) );
//
 //           string sMsg( msg );
//
//			GCSystemMessage gcSystemMessage;
//			gcSystemMessage.setType(SYSTEM_MESSAGE_MASTER_LAIR);
//			gcSystemMessage.setMessage( sMsg );
//			g_pZoneGroupManager->broadcast( &gcSystemMessage );

			GCNoticeEvent gcNoticeEvent;

			gcNoticeEvent.setCode(NOTICE_EVENT_MASTER_LAIR_COUNT);

			int remainMin = remainSec/60;
			uint param = (remainMin << 16) | ((int)m_pZone->getZoneID());
			gcNoticeEvent.setParameter( param );

			g_pZoneGroupManager->broadcast( &gcNoticeEvent );


			m_EventValue = remainSec;
		}
	}


	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// process EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::processEventMinionCombat() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	// 대기 시간이 끝나면..
	// 몹을 덜 죽였다는 의미이므로..
	// 강제추방한다.
	if (currentTime >= m_EventTime)
	{
		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_MASTER_COMBAT_END );
		m_pZone->broadcastPacket( &gcNoticeEvent );

		activeEventWaitingKickOut();
	}

	// 소환된 몹이 다 죽은 경우라면..
	// 마스터가 나와서 싸운다.
	//if (m_nSummonedMonster >= m_nMaxSummonMonster
	if (m_bMasterReady
		// 존에 마스터 혼자만 남은 경우
		&& m_pZone->getMonsterManager()->getSize()==1)
	{
		activeEventMasterCombat();
	}

	// 플레이어들이 다 죽은 경우
	if (m_pZone->getPCManager()->getSize()==0)
	{
		activeEventWaitingRegen();
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// process EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::processEventMasterCombat() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	Creature* pMaster = m_pZone->getMonsterManager()->getCreature( m_MasterID );

	if (pMaster==NULL)
	{
		// 마스터 어디갔나?
		StringStream msg;
		msg << "마스터가 없어졌다. zoneID = " << (int)m_pZone->getZoneID();

		filelog("masterLairBug.txt", "%s", msg.toString().c_str());
			
		//throw Error(msg.toString());
	}
	else
	{
		// 현재 마스터의 위치
		m_MasterX = pMaster->getX();
		m_MasterY = pMaster->getY();
	}

	// 마스터가 죽었거나
	// 대기 시간이 끝나면..
	// 강제추방 모드로 바꾼다.
	if (pMaster==NULL || pMaster->isDead() )
	{
		killAllMonsters();
		giveKillingReward();
		activeEventWaitingKickOut();
	}

	else if (currentTime >= m_EventTime)
	{
		activeEventWaitingKickOut();
	}

	// 플레이어들이 다 죽은 경우
	if (m_pZone->getPCManager()->getSize()==0)
	{
		activeEventWaitingRegen();
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// process EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::processEventWaitingKickOut() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	// 대기 시간이 끝나면 
	//   사용자들을 kickOut 시키고
	//   Regen되기를 기다린다.
	if (currentTime >= m_EventTime)
	{
		kickOutPlayers();
		activeEventWaitingRegen();
	}

	__END_CATCH
}
////////////////////////////////////////////////////////////////////////////////
//
// process EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::processEventWaitingRegen() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	// 리젠 시간이 되면 
	//   사용자들을 기다린다.
	if (currentTime >= m_RegenTime)
	{
		if (g_pVariableManager->isActiveMasterLair())
		{
			activeEventWaitingPlayer();
		}
		else
		{
			// 아니면 다음 리젠 시간까지 대기한다.
			MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
			Assert(pInfo!=NULL);

			m_RegenTime.tv_sec += pInfo->getRegenDelay();
		}
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// active EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::activeEventWaitingPlayer() 
	throw (Error)
{
	__BEGIN_TRY

	MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
	Assert(pInfo!=NULL);

	deleteAllMonsters();

	m_bMasterReady = false;
	//m_nSummonedMonster = 0;

	m_nPassPlayer = 0;

	// 5분 대기 시간
	getCurrentTime( m_RegenTime );
	m_EventTime.tv_sec = m_RegenTime.tv_sec + pInfo->getStartDelay();
	m_EventTime.tv_usec = m_RegenTime.tv_usec;
	m_EventValue = 0;

	// 바닥에서 계속 불꽃이 솟아오른다.
	// 3초마다
	int lairAttackTick = pInfo->getLairAttackTick();
	int lairAttackMinNumber = pInfo->getLairAttackMinNumber();
	int lairAttackMaxNumber = pInfo->getLairAttackMaxNumber();

	//cout << "EffectCon: " << (int)m_pZone->getZoneID() << ", " << lairAttackTick << ", " << lairAttackMinNumber << ", " << lairAttackMaxNumber << endl;

	if (lairAttackMinNumber>0 && lairAttackMaxNumber>0)
	{
		// 기존에 있던 공격 Effect를 모두 지운다.
		for (int i=0; i<10; i++) // 무한루프 방지 -_-;
		{
			Effect* pOldEffect = m_pZone->findEffect( Effect::EFFECT_CLASS_CONTINUAL_GROUND_ATTACK );
			if (pOldEffect==NULL)
				break;
			m_pZone->deleteEffect( pOldEffect->getObjectID() );
		}

		EffectContinualGroundAttack* pEffect = new EffectContinualGroundAttack(m_pZone, Effect::EFFECT_CLASS_GROUND_ATTACK, lairAttackTick);
		//EffectContinualGroundAttack* pEffect = new EffectContinualGroundAttack(m_pZone, Effect::EFFECT_CLASS_METEOR_STRIKE, lairAttackTick);
		pEffect->setDeadline( pInfo->getStartDelay()*10 );
		pEffect->setNumber( lairAttackMinNumber, lairAttackMaxNumber );

		ObjectRegistry & objectregister = m_pZone->getObjectRegistry();
		objectregister.registerObject(pEffect);

		// 존에다가 이펙트를 추가한다.
		m_pZone->addEffect( pEffect );

		// 불기둥
		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
		gcNoticeEvent.setParameter( pInfo->getStartDelay() );	// 초

		m_pZone->broadcastPacket( &gcNoticeEvent );
	}

	// 마스터 레어가 열렸다고 사람들에게 알려준다.
//	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
//	Assert(pZoneInfo!=NULL);

//	StringStream msg;
//	msg << "마스터 레어(" << pZoneInfo->getFullName().c_str() << ")가 열렸습니다.";

//    char msg[50];
 //   sprintf( msg, g_pStringPool->c_str( STRID_MASTER_LAIR_OPENED ),
  //                  pZoneInfo->getFullName().c_str() );
//
 //   string sMsg( msg );
//
//	GCSystemMessage gcSystemMessage;
//	gcSystemMessage.setType(SYSTEM_MESSAGE_MASTER_LAIR);
//	gcSystemMessage.setMessage( sMsg );
//	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	GCNoticeEvent gcNoticeEvent;

	gcNoticeEvent.setCode(NOTICE_EVENT_MASTER_LAIR_OPEN);
	gcNoticeEvent.setParameter( m_pZone->getZoneID() );

	g_pZoneGroupManager->broadcast( &gcNoticeEvent );

	// 다음 리젠 시간 설정
	m_RegenTime.tv_sec += pInfo->getRegenDelay();

	m_Event = EVENT_WAITING_PLAYER;

	//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager::activeEventWaitingPlayer" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// active EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::activeEventMinionCombat() 
	throw (Error)
{
	__BEGIN_TRY

	MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
	Assert(pInfo!=NULL);

	// 불기둥 끝났다는 신호
	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK_END );
	m_pZone->broadcastPacket( &gcNoticeEvent );

	gcNoticeEvent.setCode( NOTICE_EVENT_MASTER_COMBAT_TIME );
	gcNoticeEvent.setParameter( pInfo->getEndDelay() );
	m_pZone->broadcastPacket( &gcNoticeEvent );


	// tile에서는 지우고 packet은 안 보낸다.
	deleteAllMonsters();

	// 마스터 생성
	Monster* pMaster = new Monster( pInfo->getMasterNotReadyMonsterType() );
	Assert(pMaster != NULL);

	// 시체에서 아이템이 안 나오도록 한다.
	pMaster->setTreasure( false );

	// 무적 상태로 설정
	pMaster->setFlag(Effect::EFFECT_CLASS_NO_DAMAGE);

	// 마스터를 생성해 놓으면
	// 마스터가 알아서 몬스터를 소환하게 된다.

	try
	{
		m_pZone->addCreature(pMaster, pInfo->getMasterX(), pInfo->getMasterY(), pInfo->getMasterDir());

		// ObjectID를 기억해두고 읽어서 사용한다.
		m_MasterID = pMaster->getObjectID();
	}
	catch (EmptyTileNotExistException&)
	{
		// 마스터가 들어갈 자리가 없다고? -_-;
		SAFE_DELETE(pMaster);
	}

	//m_nSummonedMonster = 0;  // 마스터가 소환한 몬스터 수 

	m_Event = EVENT_MINION_COMBAT;
	m_EventValue = 0;

	// 언제까지 싸울까?
	getCurrentTime( m_EventTime );
	m_EventTime.tv_sec += pInfo->getEndDelay();

	//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager::activeEventMinionCombat" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// active EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::activeEventMasterCombat() 
	throw (Error)
{
	__BEGIN_TRY

	Creature* pMaster = m_pZone->getMonsterManager()->getCreature( m_MasterID );
	// 여기서 마스터 관련 하드코딩을 해도 되겠지. - -;

	if (pMaster!=NULL)
	{
		MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
		Assert(pInfo!=NULL);

		Monster* pMasterMonster = dynamic_cast<Monster*>(pMaster);

		// 소환 단계의 마스터 대신에 직접 싸우는 마스터 몬스터로 바꾼다.
		if (pInfo->getMasterMonsterType()!=pMasterMonster->getMonsterType())
		{
		  	// 마스터 생성
			Monster* pNewMaster = new Monster( pInfo->getMasterMonsterType() );
			Assert(pNewMaster != NULL);

			// 시체에서 아이템이 안 나오도록 한다.
			pNewMaster->setTreasure( false );

			try
			{
				m_pZone->addCreature(pNewMaster, pInfo->getSummonX(), pInfo->getSummonY(), pMaster->getDir());

				// ObjectID를 기억해두고 읽어서 사용한다.
				m_MasterID = pNewMaster->getObjectID();
			}
			catch (EmptyTileNotExistException&)
			{
				m_MasterID = 0;

				// 마스터가 들어갈 자리가 없다고? -_-;
				SAFE_DELETE(pNewMaster);
			}

			// NotReady상태의 Master를 그냥 남겨 두는 경우
			if (pInfo->isMasterRemainNotReady())
			{
				ZoneCoord_t cx = pMasterMonster->getX();
				ZoneCoord_t cy = pMasterMonster->getY();

			 	// 먼저 바닥에 쓰러뜨리라고, 이펙트를 뿌린다.
			   	GCAddEffect gcAddEffect;
			    gcAddEffect.setObjectID(pMasterMonster->getObjectID());
			    gcAddEffect.setEffectID(Effect::EFFECT_CLASS_COMA);
				gcAddEffect.setDuration(0);
			    m_pZone->broadcastPacket(cx, cy, &gcAddEffect);

				// AI만 제거하고 그대로 둔다.
				pMasterMonster->removeBrain();

				/*
				// 아이템으로 남겨둘랬는데.. AI제거하고 그냥 두는게 나을거 같아서
				m_pZone->deleteCreature( pMaster, pMaster->getX(), pMaster->getY() );

				ZoneCoord_t cx = pMasterMonster->getX();
				ZoneCoord_t cy = pMasterMonster->getY();

				Tile& tile = m_pZone->getTile( cx, cy );

				bool bCreateCorpse = true;

				// 시체를 타일에 추가한다. 현재 타일에 아이템이 존재한다면,
				if (tile.hasItem())
				{
					bCreateCorpse = false;
				}

				// Zone에 시체(관)를 추가한다.
				if (bCreateCorpse)
				{
					Timeval currentTime;
					getCurrentTime(currentTime);
					int timeGap = m_EventTime.tv_sec - currentTime.tv_sec;
					Turn_t decayTurn = timeGap * 10;

					MonsterCorpse* pMonsterCorpse = new MonsterCorpse(pMasterMonster);
					TPOINT pt = m_pZone->addItem(pMonsterCorpse, cx, cy, true, decayTurn);
					if (pt.x == -1)
					{
						SAFE_DELETE(pMonsterCorpse);
					}
				}
				else
				{
					SAFE_DELETE(pMaster);
				}
				*/
			}
			else
			{
				m_pZone->deleteCreature( pMaster, pMaster->getX(), pMaster->getY() );

				SAFE_DELETE(pMaster);
			}
		}
		else
		{
			// 무적 상태 해제
			// 원래 있던 마스터가 새 마스터로 대체되지 않고 직접 싸우게 하면 그전에 마스터가 무적이었으므로
			// 무적을 풀어줘야 한다. 새 마스터가 싸우게 하려면 원래 마스터는 NO_DAMAGE상태로 남아있어야 한다.
			// 테페즈레어에서 원래 마스터가 테페즈 관인데 이거 너무 일찍 풀어주는 바람에 테페즈 관이 NO_DAMAGE
			// 가 풀려서 테페즈 관을 때려서 경험치를 얻을 수 있게 되는 버그가 있었다.
			// 이 if절 들어오기 전에 있었던 것을 else 절로 옮긴다. 2003. 1.16. by Sequoia
			pMaster->removeFlag(Effect::EFFECT_CLASS_NO_DAMAGE);
		}
	}

	m_Event = EVENT_MASTER_COMBAT;
	m_EventValue = 0;

	//cout << "[" << (int)m_pZone->getZoneID() << "[ MasterLairManager::activeEventMasterCombat" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// active EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::activeEventWaitingKickOut() 
	throw (Error)
{
	__BEGIN_TRY

	MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
	Assert(pInfo!=NULL);

	// 마스터가 안 죽었다면 메세지 출력
	Creature* pMaster = m_pZone->getMonsterManager()->getCreature( m_MasterID );

	if (pMaster!=NULL && pMaster->isAlive())
	{
		GCSay gcSay;
		gcSay.setObjectID( pMaster->getObjectID() );
		gcSay.setColor( MASTER_SAY_COLOR );
		gcSay.setMessage( pInfo->getRandomMasterNotDeadSay() );
		if (!gcSay.getMessage().empty())
			m_pZone->broadcastPacket(pMaster->getX(), pMaster->getY(), &gcSay);
	}
	
    // 안의 사용자들을 밖으로 내보내는 시간 
	m_Event = EVENT_WAITING_KICK_OUT;
	m_EventValue = 0;

	getCurrentTime( m_EventTime );
	m_EventTime.tv_sec += pInfo->getKickOutDelay();

	// Lair의 유저들에게 종료 시간을 보내준다.
	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode( NOTICE_EVENT_KICK_OUT_FROM_ZONE );
	gcNoticeEvent.setParameter( pInfo->getKickOutDelay() );

	m_pZone->broadcastPacket( &gcNoticeEvent );

	//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager::activeEventKickOut" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// active EventWaitingPlayer
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::activeEventWaitingRegen() 
	throw (Error)
{
	__BEGIN_TRY

	deleteAllMonsters();

	// EffectContinualGroundAttack를 꺼준다.

	//m_nSummonedMonster = 0;
	m_nPassPlayer = 0;
	m_Event = EVENT_WAITING_REGEN;
	m_EventValue = 0;

	m_bMasterReady = false;

	//cout << "[" << (int)m_pZone->getZoneID() << "] MasterLairManager::activeEventWaitingRegen" << endl;
	

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// delete All Monsters
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::deleteAllMonsters()
	throw (Error)
{
	__BEGIN_TRY

	// Zone의 MonsterManager에서 제거한 다음에 지워준다.
	//m_pZone->getMonsterManager()->deleteCreature( m_pMaster->getObjectID() );
	//SAFE_DELETE(m_pMaster);
	bool bDeleteFromZone = true;
	m_pZone->getMonsterManager()->deleteAllMonsters( bDeleteFromZone );

	m_MasterID = 0;
	m_MasterX = 0;
	m_MasterY = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// kill All Monsters
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::killAllMonsters()
	throw (Error)
{
	__BEGIN_TRY

	// 이 부분에 뭔가 문제가 있는거 같아 제거한다.

	/*
	// 강제로 죽이지 않을 몬스터
	hash_map<ObjectID_t, ObjectID_t> exceptCreatures;
	exceptCreatures[m_MasterID] = m_MasterID;

	// 모든 몬스터를 죽인다.
	m_pZone->getMonsterManager()->killAllMonsters( exceptCreatures );
	*/

	__END_CATCH
}
////////////////////////////////////////////////////////////////////////////////
//
// increase SummonedMonster Number
// 
////////////////////////////////////////////////////////////////////////////////
/*
void MasterLairManager::increaseSummonedMonsterNumber(int num) 
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_nSummonedMonster += num;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
*/
////////////////////////////////////////////////////////////////////////////////
//
// start Event
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::startEvent()
	throw (Error)
{
	__BEGIN_TRY

	activeEventWaitingPlayer();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// start Event
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::stopEvent()
	throw (Error)
{
	__BEGIN_TRY

	kickOutPlayers();
	activeEventWaitingRegen();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// kickOut Players
//
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::kickOutPlayers()
	throw (Error)
{
	__BEGIN_TRY

	MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( m_pZone->getZoneID() );
	Assert(pInfo!=NULL);

	/*
	ZoneID_t 	zoneID 	= pInfo->getKickZoneID();
	ZoneCoord_t zoneX 	= pInfo->getKickZoneX();
	ZoneCoord_t zoneY 	= pInfo->getKickZoneY();

	//cout << "[kickOut] " << (int)zoneID << ": "<< (int)zoneX << ", " << (int)zoneY << endl;

	// 존의 모든 사용자들을 다른 곳으로 이동시킨다.
	PCManager* pPCManager = (PCManager*)(m_pZone->getPCManager());
	pPCManager->transportAllCreatures( zoneID, zoneX, zoneY );
	*/


	// 추방 시간 후에는 메테오 공격
	int lairAttackTick = pInfo->getLairAttackTick();
	int lairAttackMinNumber = pInfo->getLairAttackMinNumber();
	int lairAttackMaxNumber = pInfo->getLairAttackMaxNumber();

	EffectContinualGroundAttack* pEffect = new EffectContinualGroundAttack(m_pZone, Effect::EFFECT_CLASS_METEOR_STRIKE, lairAttackTick);
	pEffect->setDeadline( pInfo->getStartDelay()*10 );
	pEffect->setNumber( lairAttackMinNumber, lairAttackMaxNumber );

	ObjectRegistry & objectregister = m_pZone->getObjectRegistry();
	objectregister.registerObject(pEffect);

	// 존에다가 이펙트를 추가한다.
	m_pZone->addEffect( pEffect );

	// 메테오 공격
	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
	gcNoticeEvent.setParameter( pInfo->getStartDelay() );	// 초

	m_pZone->broadcastPacket( &gcNoticeEvent );

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// give Killing Reward
//
////////////////////////////////////////////////////////////////////////////////
// 마스터가 죽었을때의 보상
// 지금은 QuestItem을 현재 존의 사람들에게 각자의 인벤토리에 넣어준다.
// 인벤토리에 자리가 없는 경우엔 바닥에 떨어뜨리는데
// 이미 가지고 있는 사람은 주울 수 없다.
////////////////////////////////////////////////////////////////////////////////
void MasterLairManager::giveKillingReward() 
	throw (Error)
{
	__BEGIN_TRY

	const PCManager* pPCManager = m_pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr;

	if (creatures.empty())
		return;

	int goodOneIndex = rand()%creatures.size();	// 펜던트를 가질 사람은 누구일까?

	ItemType_t itemType;
	int i;
	for (i=0, itr=creatures.begin(); itr!=creatures.end(); i++, itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isPC())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();

			//------------------------------------------------------------
			// 계급 경험치를 올려준다.
			//------------------------------------------------------------
			// 마스터 위치와 7타일 이내에 이는 경우
			//
			if (pPC->getDistance(m_MasterX, m_MasterY) <= 7)
			{
				pPC->increaseRankExp( MASTER_KILL_RANK_EXP );
			}

			//------------------------------------------------------------
			// 보상 아이템을 생성한다.
			//------------------------------------------------------------
			// 하드. - -;
			switch (m_pZone->getZoneID())
			{
				// 바토리레어 & 클론
				case 1104 :
				case 1106 :
					itemType = ((goodOneIndex==i)? 1:0);
				break;

				// 테페즈 레어 & 클론
				case 1114 :
				case 1115 :
					itemType = ((goodOneIndex==i)? 3:2);
				break;

				default :
					filelog("MasterLairBUG.txt", "ZoneID가 잘못되었습니다");
				return;

			}

			list<OptionType_t> nullList;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_QUEST_ITEM, itemType, nullList);
 
			(m_pZone->getObjectRegistry()).registerObject(pItem);

			// 인벤토리의 빈 곳을 찾는다.
			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	            pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "LairMaster", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// 인벤토리에 아이템 생성 패킷을 보내준다.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// 인벤토리에 자리가 없어서 바닥에 떨어뜨린다.

				TPOINT p = m_pZone->addItem(pItem, pCreature->getX(), pCreature->getY());
				if (p.x != -1)
				{
					pItem->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName , "%4d%3d%3d", m_pZone->getZoneID(), p.x, p.y);
						remainTraceLog( pItem, "LairMaster", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem, zoneName, ITL_GET , ITLD_EVENTNPC, m_pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem);
				}
			}
		}
		else
		{
			throw Error("PCManager에 PC아닌게 들어있노 -_-");
		}
	}

	__END_CATCH
}

string MasterLairManager::toString() const 
	throw(Error)
{
	StringStream msg;

	int eventSec = m_EventTime.tv_sec;

	switch (m_Event)
	{
		case EVENT_WAITING_PLAYER :     // 사람들이 들어오길 기다린다.
			msg << "WAITING_PLAYER, ";
		break;

		case EVENT_MINION_COMBAT:      // 소환된 몬스터와 싸운다.
			msg << "MINION_COMBAT, ";
		break;

		case EVENT_MASTER_COMBAT:
			msg << "MASTER_COMBAT, ";
		break;

		case EVENT_WAITING_KICK_OUT:    // 사용자 강제추방 대기(마스터 잡은 경우의 정리 시간)
			msg << "WAITING_KICK_OUT, ";
		break;

		case EVENT_WAITING_REGEN:      // 다시 리젠되길 기다린다.
			msg << "WAITING_REGEN, ";

			eventSec = m_RegenTime.tv_sec;
		break;

		default :
		break;
	}

	Timeval currentTime;
	getCurrentTime(currentTime);

	int timeGap = eventSec - currentTime.tv_sec;

	msg << timeGap << " sec remain, " << (int)m_pZone->getPCManager()->getSize() << " players";

	return msg.toString();
}
