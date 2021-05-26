//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPKZoneResurrection.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectPKZoneResurrection.h"
#include "Zone.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "Player.h"
#include "GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPKZoneResurrection::EffectPKZoneResurrection( Creature* pCreature )
{
	__BEGIN_TRY

	setTarget( pCreature );
	setBroadcastingEffect( false );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPKZoneResurrection::affect()
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectPKZoneResurrection::unaffect() 
	
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPKZoneResurrection::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCreature->getObjectID() );
	gcAddEffect.setEffectID( getSendEffectClass() );
	gcAddEffect.setDuration( 28 );

	Zone* pZone = pCreature->getZone();

	if ( pZone != NULL )
		pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );

	pCreature->removeFlag( getEffectClass() );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPKZoneResurrection::toString()
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPKZoneResurrection("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
