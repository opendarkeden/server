//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectExplosionWater.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EXPLOSION_WATER__
#define __EFFECT_EXPLOSION_WATER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectExplosionWater
//////////////////////////////////////////////////////////////////////////////

class EffectExplosionWater : public Effect
{
public:
    EffectExplosionWater(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_EXPLOSION_WATER; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

	void setDamageReduce( int dr ) { m_DamageReduce = dr; }
	int getDamageReduce() const { return m_DamageReduce; }

public:
	int m_DamageReduce;
};

#endif // __EFFECT_EXPLOSION_WATER__

