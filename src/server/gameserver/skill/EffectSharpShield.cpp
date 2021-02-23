//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSharpShield.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSharpShield.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSharpShield::EffectSharpShield(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSharpShield" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_SHARP_SHIELD_1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList( m_ClientEffectClass );
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectSharpShield" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSharpShield::setLevel(Level_t Level) 
	throw()
{
//	m_ClientEffectClass = EFFECT_CLASS_SHARP_SHIELD_1;
	if( Level <= GRADE_ADEPT_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_SHARP_SHIELD_1;
	else if( Level <= GRADE_EXPERT_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_SHARP_SHIELD_2;
	else if( Level <= GRADE_MASTER_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_SHARP_SHIELD_3;
	else m_ClientEffectClass = EFFECT_CLASS_SHARP_SHIELD_4;
} 

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSharpShield::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSharpShield("
		<< "ObjectID:" << getObjectID()
		<< ",ClientEffectClass:" << (int)m_ClientEffectClass
		<< ",Damage:" << m_Damage
		<< ")";
	return msg.toString();

	__END_CATCH

}

