//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTryingPosition.h
// Written by  : 
// Description : TryingPosition에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRYING_POSITION__
#define __EFFECT_TRYING_POSITION__

#include "Effect.h"

class Zone;
class MonsterCorpse;

//////////////////////////////////////////////////////////////////////////////
// class EffectTryingPosition
//////////////////////////////////////////////////////////////////////////////

class EffectTryingPosition : public Effect 
{
public:
	EffectTryingPosition(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, MonsterCorpse* pTower) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRYING_POSITION; }

	void affect(Creature* pCreature) throw(Error);
	void unaffect( Creature* pCreature ) throw(Error);

	void unaffect() throw(Error); 
	MonsterCorpse* getTower() const { return m_pTower; }

	string toString() const throw();

public:
	MonsterCorpse* m_pTower;
	Effect::EffectClass m_LastEffect;
};

#endif // __EFFECT_TRYING_POSITION__
