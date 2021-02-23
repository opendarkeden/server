//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWillOfLife.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectWillOfLife.h"
#include "Creature.h"
#include "Vampire.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectWillOfLife::EffectWillOfLife(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectWillOfLife::affect()
	throw(Error)
{
	__BEGIN_TRY

	if ( m_pTarget != NULL && m_pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
	{
		affect( dynamic_cast<Creature*>(m_pTarget) );
	}

	__END_CATCH
}

void EffectWillOfLife::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;

	if ( !pCreature->isVampire() ) return;

	Vampire* pVampire = dynamic_cast<Vampire*>( pCreature );
	Assert( pVampire != NULL );

	HP_t	curHP = pVampire->getHP( ATTR_CURRENT );
	HP_t	maxHP = pVampire->getHP( ATTR_MAX ) - pVampire->getSilverDamage();

	HP_t	nextHP = curHP + getBonus();

	if ( maxHP - getBonus() <= curHP ) nextHP = maxHP;

	pVampire->setHP( nextHP );

	setNextTime(10);

	__END_CATCH
}

void EffectWillOfLife::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

	//cout << "EffectWillOfLife" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectWillOfLife" << "unaffect END" << endl;

    __END_CATCH
}

void EffectWillOfLife::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectWillOfLife" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	pCreature->removeFlag(Effect::EFFECT_CLASS_WILL_OF_LIFE);

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pVampire->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_WILL_OF_LIFE);
	pVampire->getZone()->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcRemoveEffect);

	GCStatusCurrentHP gcHP;
	gcHP.setObjectID( pVampire->getObjectID() );
	gcHP.setCurrentHP( pVampire->getHP( ATTR_CURRENT ) );
	pVampire->getPlayer()->sendPacket( &gcHP );

	//cout << "EffectWillOfLife" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectWillOfLife::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectWillOfLife("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
