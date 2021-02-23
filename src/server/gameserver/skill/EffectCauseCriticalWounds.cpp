//////////////////////////////////////////////////////////////////////////////
// Filename		: EffectCauseCriticalWounds.cpp
// Written By	:
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "EffectCauseCriticalWounds.h"
#include "DB.h"
#include "SkillHandler.h"

#include "Gpackets/GCRemoveEffect.h"

EffectCauseCriticalWounds::EffectCauseCriticalWounds( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	setTarget( pCreature );

	__END_CATCH
}

void EffectCauseCriticalWounds::affect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

void EffectCauseCriticalWounds::affect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectCauseCriticalWounds::unaffect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	//cout << "EffectCauseCriticalWounds " << "unaffect BEGIN" << endl;

	Assert( pCreature != NULL );
	Assert( pCreature->isVampire() || pCreature->isOusters() || pCreature->isMonster() );

	pCreature->removeFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	if ( pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

		pPlayer->sendPacket( &gcRemoveEffect );
	}

	__END_CATCH
}

void EffectCauseCriticalWounds::unaffect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect( pCreature );

	__END_CATCH
}

string EffectCauseCriticalWounds::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCauseCriticalWounds("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

