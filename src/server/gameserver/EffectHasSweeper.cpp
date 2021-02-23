
#include "EffectHasSweeper.h"
#include "Creature.h"
#include "Zone.h"
#include "Gpackets/GCRemoveEffect.h"

EffectHasSweeper::EffectHasSweeper(Creature* pCreature) throw(Error)
{
	__BEGIN_TRY

	setTarget( pCreature );
	m_Part = 0;

	__END_CATCH
}

void EffectHasSweeper::unaffect() throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	Assert( pCreature != NULL );

	pCreature->removeFlag( getEffectClass() );

	GCRemoveEffect gcRE;
	gcRE.setObjectID( pCreature->getObjectID() );
	gcRE.addEffectList( getSendEffectClass() );

	pCreature->getZone()->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRE );

	__END_CATCH
}

string EffectHasSweeper::toString() const throw()
{
	__BEGIN_TRY

	return "EffectHasSweeper";

	__END_CATCH
}
