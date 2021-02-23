#include "GDRLairAbstractStates.h"
#include "StringPool.h"
#include "Gpackets/GCSay.h"
#include "Gpackets/GCGlobalChat.h"
#include "Zone.h"
#include "Monster.h"
#include "Utility.h"
#include "CreatureUtil.h"
#include "ZoneUtil.h"
#include "GDRLairManager.h"
#include "MonsterManager.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "skill/Skill.h"
#include "PCManager.h"
#include "ZoneGroup.h"

void GDRScene::start()
{
	getCurrentTime(m_NextActionTurn);
	m_NextAction = m_ActionList.begin();
}

DWORD GDRScene::heartbeat(Timeval currentTime)
{
	if ( m_NextAction == m_ActionList.end() )
		return m_NextState;

	if ( currentTime < m_NextActionTurn )
		return 0;

	Zone* pZone = (*m_NextAction)->getTarget()->getZone();
	Assert( pZone != NULL );

	Turn_t result;

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) );

//	cout << (*m_NextAction)->getActionType() << " action execute.." << endl;
	result = (*m_NextAction)->execute();

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) );

	if ( result == 0 ) ++m_NextAction;
	else
	{
		getCurrentTime( m_NextActionTurn );
		m_NextActionTurn.tv_sec += result / 10;
		m_NextActionTurn.tv_usec += (result % 10) * 100000;
	}

	return 0;
}

Monster*		GDRScene::getGDR() const
{
	return GDRLairManager::Instance().m_pGDR;
}

void			GDRScene::setGDR(Monster* pGDR) const
{
	GDRLairManager::Instance().m_pGDR = pGDR;
}

Turn_t GDRScene::ActionSay::execute()
{
	GCSay gcSay;
	gcSay.setObjectID( getTarget()->getObjectID() );
	gcSay.setMessage( g_pStringPool->getString( m_strID ) );
	gcSay.setColor( 0x00ffffff );

	cout << "질드레가 말합니다 : " << gcSay.getMessage() << endl;

	getTarget()->getZone()->broadcastPacket( getTarget()->getX(), getTarget()->getY(), &gcSay );

	GCGlobalChat gcGC;
	gcGC.setColor( 0x00ffffff );
	gcGC.setMessage( "질드레 " + g_pStringPool->getString( m_strID ) );
	gcGC.setRace( RACE_VAMPIRE );

	getTarget()->getZone()->broadcastPacket( &gcGC );
	return 0;
}

Turn_t GDRScene::ActionWalk::execute()
{
	Monster* pTarget = getTarget();
	Assert( pTarget != NULL );

	Dir_t dir = computeDirection( pTarget->getX(), pTarget->getY(), m_TargetX, m_TargetY );
	ZoneCoord_t nx = 0;
	ZoneCoord_t ny = 0;

	Zone* pZone = pTarget->getZone();
	Assert( pZone != NULL );

	static int offset[5] = { 0, -1, 1, -2, 2 };
	int i = 0;
	
	for ( i = 0 ; i < 5 ; ++i )
	{
		nx = pTarget->getX() + dirMoveMask[dir+offset[i]].x;
		ny = pTarget->getY() + dirMoveMask[dir+offset[i]].y;

		if ( isValidZoneCoord(pZone, nx, ny) && !pZone->getTile(nx, ny).isBlocked(pTarget->getMoveMode()) )
		{
			if ( i != 0 )
			{
				int temp;
				SWAP( offset[1], offset[i], temp );
				m_DodgeCount++;
				cout << "DodgeCount : " << m_DodgeCount << endl;
				filelog("GDRLair.log", "DodgeCount : %d", m_DodgeCount);
			}

			dir += offset[i];
			break;
		}
	}

	if ( i != 5 )
	{
		pZone->moveCreature( pTarget, nx, ny, dir );
		if ( nx == m_TargetX && ny == m_TargetY ) return 0;
	}
	else
	{
		m_DodgeCount++;
		cout << "DodgeCount : " << m_DodgeCount << endl;
		filelog("GDRLair.log", "DodgeCount : %d", m_DodgeCount);
	}

	if ( m_DodgeCount > 20 )
	{
		pZone->moveFastMonster( pTarget, pTarget->getX(), pTarget->getY(), m_TargetX, m_TargetY, SKILL_RAPID_GLIDING );
		return 0;
	}

	return m_MoveDelay;
}

Turn_t GDRScene::ActionEffect::execute()
{
	Monster* pTarget = getTarget();
	Assert( pTarget != NULL );
	Zone* pZone = pTarget->getZone();
	Assert( pZone != NULL );

	addSimpleCreatureEffect( pTarget, m_EffectClass, m_Duration, true );
	return 0;
}

Turn_t GDRScene::ActionRemoveEffect::execute()
{
	Monster* pTarget = getTarget();
	Assert( pTarget != NULL );

	Effect* pEffect = pTarget->findEffect( m_EffectClass );
	if ( pEffect != NULL ) pEffect->setDeadline(0);

	return 0;
}

Turn_t GDRScene::ActionHollywood::execute()
{
	Monster* pTarget = getTarget();
	Assert( pTarget != NULL );

	GCSkillToObjectOK4 gcOK;
	gcOK.setTargetObjectID( pTarget->getObjectID() );
	gcOK.setSkillType( SKILL_ATTACK_MELEE );

	pTarget->getZone()->broadcastPacket( pTarget->getX(), pTarget->getY(), &gcOK );
	return 0;
}

Turn_t GDRScene::ActionWarp::execute()
{
	Monster* pTarget = getTarget();
	Assert( pTarget != NULL );

	Zone* pZone = pTarget->getZone();
	Assert( pZone != NULL );

	pZone->moveFastMonster( pTarget, pTarget->getX(), pTarget->getY(), m_TargetX, m_TargetY, SKILL_TELEPORT );

	return 0;
}

void MonsterSummonState::start()
{
	if ( m_TimeLimit ) TimerState::start();
}

DWORD MonsterSummonState::heartbeat(Timeval currentTime)
{
	if ( m_TimeLimit )
	{
		DWORD nState = TimerState::heartbeat(currentTime);
		if ( nState != 0 ) return nState;
	}

	__ENTER_CRITICAL_SECTION( (*(m_pZone->getZoneGroup())) )

	const PCManager* pPM = m_pZone->getPCManager();

	if ( pPM->getSize() < 1 )
	{
		m_pZone->getZoneGroup()->unlock();
		return m_FailState;
	}

	MonsterManager* pMM = m_pZone->getMonsterManager();

	if ( pMM->getSize() <= 1 )
	{
		if ( m_CurrentSummonInfo == m_GroupSummonInfos.end() )
		{
			m_pZone->getZoneGroup()->unlock();
			return m_ClearState;
		}
		else
		{
			(*m_CurrentSummonInfo)->executeSummon( m_pZone );
			++m_CurrentSummonInfo;
		}
	}

	__LEAVE_CRITICAL_SECTION( (*(m_pZone->getZoneGroup())) )

	return 0;
}

void MonsterSummonState::GroupSummonInfo::executeSummon( Zone* pZone )
{
	list<SummonInfo*>::iterator itr = m_SummonInfos.begin();
	list<SummonInfo*>::iterator endItr = m_SummonInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		for ( int i=0; i<(*itr)->m_MonsterNum; ++i )
		{
			cout << "몬스터 소환 " << (*itr)->m_MonsterType << endl;
			Monster* pMonster = new Monster( (*itr)->m_MonsterType );
			pMonster->setTreasure(false);
			try
			{
				pZone->addCreature( pMonster, (*itr)->m_X, (*itr)->m_Y, 0 );
			}
			catch( Exception& e )
			{
				cout << e.toString() << endl;
			}
		}
	}
}
