//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrandMasterOusters.cpp
// Written by  : ��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectGrandMasterOusters.h"
#include "Creature.h"
#include "Player.h"
#include "Zone.h"
#include "Ousters.h"
#include "GCAddEffect.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGrandMasterOusters::EffectGrandMasterOusters(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

Effect::EffectClass EffectGrandMasterOusters::getSendEffectClass() const 
{
	Ousters* pOusters = dynamic_cast<Ousters*>(m_pTarget);
	if ( pOusters == NULL ) return getEffectClass();

	Level_t level = pOusters->getLevel();

	if ( level == 150 ) return Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS_150;
	else if ( level >= 130 ) return Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS_130;
	else return getEffectClass();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGrandMasterOusters::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGrandMasterOusters::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature->isOusters());

	pCreature->setFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS);

	// ������ �ѷ��ش�.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());
	gcAddEffect.setEffectID(getSendEffectClass());
	gcAddEffect.setDuration(999999);
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	__END_CATCH
}

void EffectGrandMasterOusters::unaffect() 
	
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGrandMasterOusters::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGrandMasterOusters::toString()
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectGrandMasterOusters("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
