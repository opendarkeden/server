//////////////////////////////////////////////////////////////////////////////
// Filename		: EffectExplosionWater.cpp
// Written By	:
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "EffectExplosionWater.h"
#include "DB.h"
#include "SkillHandler.h"

#include "Gpackets/GCRemoveEffect.h"

EffectExplosionWater::EffectExplosionWater( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	setTarget( pCreature );

	__END_CATCH
}

void EffectExplosionWater::affect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

void EffectExplosionWater::affect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectExplosionWater::unaffect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	//cout << "EffectExplosionWater " << "unaffect BEGIN" << endl;

	Assert( pCreature != NULL );

	pCreature->removeFlag( Effect::EFFECT_CLASS_EXPLOSION_WATER );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_EXPLOSION_WATER );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	if ( pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

		pPlayer->sendPacket( &gcRemoveEffect );
	}

	__END_CATCH
}

void EffectExplosionWater::unaffect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect( pCreature );

	__END_CATCH
}

string EffectExplosionWater::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectExplosionWater("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

