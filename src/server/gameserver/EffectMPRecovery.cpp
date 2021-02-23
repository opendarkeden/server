//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMPRecovery.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "EffectMPRecovery.h"
#include "Gpackets/GCMPRecoveryEnd.h"
#include "Zone.h"
#include "Slayer.h"
#include "Ousters.h"
#include "Creature.h"
#include "Player.h"

EffectMPRecovery::EffectMPRecovery () 
	throw (Error)
{
	__BEGIN_TRY

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectMPRecovery::EffectMPRecovery (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pCreature , Turn_t delay) 
	throw (Error)
: Effect(pZone,x,y,pCreature,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectMPRecovery::~EffectMPRecovery () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMPRecovery::affect()
	throw(Error)
{
	__BEGIN_TRY

	// Delay에 따른 체력 회복.
	setNextTime(m_Delay);

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	affect(pCreature);

	__END_CATCH
}

void EffectMPRecovery::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature->isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) )
	{
		cout << "Pleasure Explosion 땜에 안 찬다." << endl;
		return;
	}

	Timeval CurrentTime;

	getCurrentTime(CurrentTime);

	if ( pCreature->isSlayer() )
	{
		Turn_t timegapSec =  m_Deadline.tv_sec - CurrentTime.tv_sec;
		Turn_t timegapUSec = m_Deadline.tv_usec - CurrentTime.tv_usec;

		Turn_t timegap = timegapSec* 1000000 + timegapUSec;

		int RecoveryPeriod = (timegap / (m_Delay* 100000));

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		if (pSlayer->getMP(ATTR_CURRENT) != pSlayer->getMP(ATTR_MAX) && m_Period != 0) 
		{
			// 플레그 걸귀
			pSlayer->setFlag(Effect::EFFECT_CLASS_MP_RECOVERY);

			// 한 턴에 얼마나 회복 시킬 것인가.
			MP_t CurrentMP = pSlayer->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pSlayer->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* (m_Period - RecoveryPeriod)));

			pSlayer->setMP(NewMP, ATTR_CURRENT);
		} 
		else 
		{
			setDeadline(0);
		}

		m_Period = RecoveryPeriod;
	}
	else if ( pCreature->isOusters() )
	{
		Turn_t timegapSec =  m_Deadline.tv_sec - CurrentTime.tv_sec;
		Turn_t timegapUSec = m_Deadline.tv_usec - CurrentTime.tv_usec;

		Turn_t timegap = timegapSec* 1000000 + timegapUSec;

		int RecoveryPeriod = (timegap / (m_Delay* 100000));

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if (pOusters->getMP(ATTR_CURRENT) <= pOusters->getMP(ATTR_MAX) && m_Period != 0) 
		{
			// 플레그 걸귀
			pOusters->setFlag(Effect::EFFECT_CLASS_MP_RECOVERY);

			// 한 턴에 얼마나 회복 시킬 것인가.
			MP_t CurrentMP = pOusters->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pOusters->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* (m_Period - RecoveryPeriod)));

			pOusters->setMP(NewMP, ATTR_CURRENT);
		} 
		else 
		{
			setDeadline(0);
		}

		m_Period = RecoveryPeriod;
	}

	__END_CATCH
}

void EffectMPRecovery::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void EffectMPRecovery::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	unaffect(pCreature);

	__END_CATCH
}

void EffectMPRecovery::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	
	if ( pCreature->isSlayer() )
	{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		if (m_Period != 0)
		{
			MP_t CurrentMP = pSlayer->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pSlayer->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* m_Period));

			pSlayer->setMP(NewMP, ATTR_CURRENT);
		}

		// 현재 MP를 브로드캐스팅한다.
		// 이제 회복이 끝났나는 것을 알리도록 한다.
		// 자신에게 먼저
		GCMPRecoveryEnd gcEffectMPRecoveryEnd;
		gcEffectMPRecoveryEnd.setCurrentMP(pSlayer->getMP(ATTR_CURRENT));
		pSlayer->getPlayer()->sendPacket(&gcEffectMPRecoveryEnd);

		pSlayer->removeFlag(Effect::EFFECT_CLASS_MP_RECOVERY);
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if (pOusters->getMP(ATTR_CURRENT) <= pOusters->getMP(ATTR_MAX) && m_Period != 0)
		{
			MP_t CurrentMP = pOusters->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pOusters->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* m_Period));

			pOusters->setMP(NewMP, ATTR_CURRENT);
		}

		// 현재 MP를 브로드캐스팅한다.
		// 이제 회복이 끝났나는 것을 알리도록 한다.
		// 자신에게 먼저
		GCMPRecoveryEnd gcEffectMPRecoveryEnd;
		gcEffectMPRecoveryEnd.setCurrentMP(pOusters->getMP(ATTR_CURRENT));
		pOusters->getPlayer()->sendPacket(&gcEffectMPRecoveryEnd);

		pOusters->removeFlag(Effect::EFFECT_CLASS_MP_RECOVERY);
	}

	__END_CATCH
}

void EffectMPRecovery::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	__END_CATCH
}

string EffectMPRecovery::toString () const 
	throw ()
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectMPRecovery("
				<< "ZoneID:" << (int)m_pZone->getZoneID()
				<< ",X:"     << (int)getX()
				<< ",Y:"     << (int)getY();
	}

	if (m_pTarget)
	{
		msg << ",Target:" << m_pTarget->toString();
	}
	else
	{
		msg << ",Target:NULL";
	}

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
