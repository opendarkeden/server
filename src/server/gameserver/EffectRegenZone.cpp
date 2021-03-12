#include "EffectRegenZone.h"
#include "MonsterCorpse.h"
#include "Zone.h"

#include "Gpackets/GCRemoveEffect.h"

EffectRegenZone::EffectRegenZone( MonsterCorpse* pTower )
{
	setTarget( pTower );
}

void EffectRegenZone::unaffect()
	
{
	__BEGIN_TRY

	MonsterCorpse* pTower = dynamic_cast<MonsterCorpse*>( m_pTarget );
	Assert( pTower != NULL );

	pTower->removeFlag( getEffectClass() );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pTower->getObjectID() );
	gcRemoveEffect.addEffectList( getSendEffectClass() );

	pTower->getZone()->broadcastPacket( pTower->getX(), pTower->getY(), &gcRemoveEffect );

	__END_CATCH
}
