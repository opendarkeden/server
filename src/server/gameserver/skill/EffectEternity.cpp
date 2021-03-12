//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEternity.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectEternity.h"
#include "Slayer.h"
#include "Player.h"
#include "CreatureUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCRemoveEffect.h"

EffectEternity::EffectEternity(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_TargetObjectID = pCreature->getObjectID();

	m_pZone = pCreature->getZone();

	__END_CATCH
}

void EffectEternity::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEternity::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectEternity " << "unaffect BEGIN" << endl;

	Zone* pZone = m_pZone;
	Assert( pZone != NULL );

    Creature* pCreature = pZone->getCreature( m_TargetObjectID );
	if ( pCreature == NULL ) return;
    unaffect(pCreature);

	//cout << "EffectEternity " << "unaffect END" << endl;

    __END_CATCH
}

void EffectEternity::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	Assert( pSlayer != NULL );

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	if ( !pSlayer->isFlag( Effect::EFFECT_CLASS_COMA ) ) return;

	// 타일에다가 이펙트를 붙여준다.
	GCAddEffectToTile gcAddEffect;
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ETERNITY);
	gcAddEffect.setXY( pSlayer->getX(), pSlayer->getY() );
	gcAddEffect.setDuration(31);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

	pSlayer->deleteEffect( Effect::EFFECT_CLASS_COMA );
	pSlayer->removeFlag( Effect::EFFECT_CLASS_COMA );

	HP_t NewHP = getPercentValue( pSlayer->getHP( ATTR_MAX ), 100 + m_HPPenalty );
	NewHP = min(NewHP, pSlayer->getHP(ATTR_MAX));
	NewHP = max((HP_t)1, NewHP);

	pSlayer->setHP( NewHP );

	// 코마 이펙트가 날아갔다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pSlayer->getObjectID());
	gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

	GCStatusCurrentHP gcHP;
	gcHP.setObjectID( pSlayer->getObjectID() );
	gcHP.setCurrentHP( pSlayer->getHP() );
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHP);

	// 이펙트들을 다시 보내준다.
	pSlayer->getEffectManager()->sendEffectInfo(pSlayer, pZone, pSlayer->getX(), pSlayer->getY());

	addSimpleCreatureEffect( pSlayer, Effect::EFFECT_CLASS_NO_DAMAGE, 30, false );
	addSimpleCreatureEffect( pSlayer, Effect::EFFECT_CLASS_ETERNITY_PAUSE, 30 );

	__END_DEBUG
	__END_CATCH
}

string EffectEternity::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectEternity("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
