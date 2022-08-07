//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPenetrateWheel.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "Effect.h"
#include "EffectPenetrateWheel.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "HitRoll.h"

#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPenetrateWheel::EffectPenetrateWheel(Creature* pCreature)
{
	__BEGIN_TRY

	m_pTarget = pCreature;
	m_CanSteal = false;

	__END_CATCH
}

void EffectPenetrateWheel::affect()
{
	__BEGIN_TRY

	if ( m_pTarget != NULL && m_pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
	{
		affect( dynamic_cast<Creature*>(m_pTarget) );
	}

	setNextTime(10);

	__END_CATCH
}

void EffectPenetrateWheel::affect(Creature* pCreature)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;
	
	Zone* pZone = pCreature->getZone();
	if ( pZone == NULL ) return;

	Creature* pCastCreature = pZone->getCreature( getCasterID() );

	GCModifyInformation gcMI, gcAttackerMI;

	if ( canAttack( pCastCreature, pCreature )
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			// There is no attacker. This is to ensure that the Sharp Shield is not applied and the Steel is not applied.
			::setDamage( pPC, getDamage(), NULL, SKILL_Penetrate_Wheel, &gcMI, &gcAttackerMI, false, m_CanSteal );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			// There is no attacker. This is to ensure that the Sharp Shield is not applied and the Steel is not applied.
			::setDamage( pCreature, getDamage(), NULL, SKILL_Penetrate_Wheel, NULL, &gcAttackerMI, false, m_CanSteal );
		}

		if ( pCastCreature != NULL && pCastCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCastCreature);

			computeAlignmentChange(pCreature, getDamage(), pOusters, &gcMI, &gcAttackerMI);
			increaseAlignment(pOusters, pCreature, gcAttackerMI);

			if (pCreature->isDead())
			{
				int exp = computeCreatureExp(pCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, gcAttackerMI);
			}

			pOusters->getPlayer()->sendPacket( &gcAttackerMI );
		}
	}

	setNextTime(20);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPenetrateWheel::unaffect()
{
	__BEGIN_TRY


	if ( m_pTarget != NULL && m_pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
	{
		unaffect( dynamic_cast<Creature*>(m_pTarget) );
	}

	__END_CATCH
}

void EffectPenetrateWheel::unaffect( Creature* pCreature )
{
	__BEGIN_TRY

	pCreature->removeFlag( getEffectClass() );

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList( getSendEffectClass() );
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPenetrateWheel::toString() const 
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectPenetrateWheel("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

