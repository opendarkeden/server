#include "EffectTrying.h"
#include "Creature.h"
#include "Zone.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCRemoveEffect.h"

/*EffectTrying::EffectTrying(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) 
{
	__BEGIN_TRY

	m_pZone = pZone;
	setXY( X, Y );

	__END_CATCH
}*/

EffectTrying::EffectTrying(Creature* pCreature) 
{
	__BEGIN_TRY

	setTarget( pCreature );

	__END_CATCH
}

void EffectTrying::unaffect() 
{
	__BEGIN_TRY

/*	GCDeleteEffectFromTile gcDeleteEffect;
	gcDeleteEffect.setEffectID( getSendEffectClass() );
	gcDeleteEffect.setObjectID( getObjectID() );
	gcDeleteEffect.setXY( m_X, m_Y );

	m_pZone->broadcastPacket( m_X, m_Y, &gcDeleteEffect );*/
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	Assert( pCreature != NULL );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.addEffectList( getSendEffectClass() );
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );

	pCreature->getZone()->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect );

	__END_CATCH
}
