#include "EffectBlindness.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "Ousters.h"
#include "Player.h"
#include "SkillUtil.h"
#include "Zone.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

EffectBlindness::EffectBlindness(Creature* pCreature) throw(Error)
{
	__BEGIN_TRY

	m_pTarget = pCreature;

	__END_CATCH
}

void EffectBlindness::affect() throw(Error)
{
	__BEGIN_TRY

	if ( m_pTarget != NULL && m_pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
	{
		affect( dynamic_cast<Creature*>(m_pTarget) );
	}

//	setNextTime(10);

	__END_CATCH
}

void EffectBlindness::affect(Creature* pCreature) throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;
	
	Zone* pZone = pCreature->getZone();
	if ( pZone == NULL ) return;

	GCModifyInformation gcMI;

	if ( !pCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE)
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			::setDamage( pPC, getDamage(), NULL, SKILL_ATTACK_MELEE, &gcMI, NULL );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			::setDamage( pCreature, getDamage(), NULL, SKILL_ATTACK_MELEE, NULL, NULL );
		}
	}

	setNextTime(30);

	__END_CATCH
}

void EffectBlindness::unaffect() throw(Error)
{
	__BEGIN_TRY

	if ( m_pTarget != NULL && m_pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
	{
		unaffect( dynamic_cast<Creature*>(m_pTarget) );
	}

	__END_CATCH
}

void EffectBlindness::unaffect( Creature* pCreature ) throw (Error)
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

string EffectBlindness::toString() const throw()
{
	__BEGIN_TRY

	return "EffectBlindness";

	__END_CATCH
}
