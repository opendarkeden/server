//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDetectMine.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDetectMine.h"
#include "Creature.h"
#include "DB.h"
#include "Slayer.h"

EffectDetectMine::EffectDetectMine(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectDetectMine::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectDetectMine::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectDetectMine::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDetectMine " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_REVEALER);
	// detect hidden의 힘으로 볼수 있었던 hidden creature를 삭제해야한다.
	Zone* pZone = pCreature->getZone();
	pZone->updateMineScan(pCreature);

	//cout << "EffectDetectMine " << "unaffect END" << endl;

	__END_CATCH
}

void EffectDetectMine::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDetectMine " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectDetectMine " << "unaffect END" << endl;

	__END_CATCH
}

void EffectDetectMine::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectDetectMine::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDetectMine("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

