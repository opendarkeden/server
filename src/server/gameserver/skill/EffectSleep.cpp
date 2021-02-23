//////////////////////////////////////////////////////////////////////////////
// Filename		: EffectSleep.cpp
// Written By	:
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "EffectSleep.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "SkillHandler.h"

#include "Gpackets/GCRemoveEffect.h"

EffectSleep::EffectSleep( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	setTarget( pCreature );

	__END_CATCH
}

void EffectSleep::affect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

void EffectSleep::affect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectSleep::unaffect( Creature* pCreature )
	throw( Error )
{
	__BEGIN_TRY

	//cout << "EffectSleep " << "unaffect BEGIN" << endl;

	Assert( pCreature != NULL );

	pCreature->removeFlag( Effect::EFFECT_CLASS_SLEEP );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_SLEEP );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	if ( pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

		pPlayer->sendPacket( &gcRemoveEffect );
	}

	__END_CATCH
}

void EffectSleep::unaffect()
	throw( Error )
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect( pCreature );

	__END_CATCH
}

string EffectSleep::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSleep("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

