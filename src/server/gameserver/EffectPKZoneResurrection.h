//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPKZoneResurrection.h
// Written by  : 
// Description : PKZoneResurrection에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PK_ZONE_RESURRECTION__
#define __EFFECT_PK_ZONE_RESURRECTION__

#include "Effect.h"

class Creature;

//////////////////////////////////////////////////////////////////////////////
// class EffectPKZoneResurrection
//////////////////////////////////////////////////////////////////////////////

class EffectPKZoneResurrection : public Effect 
{
public:
	EffectPKZoneResurrection( Creature* pCreature );

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PK_ZONE_RESURRECTION; }

	void affect() throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:

private:
};

#endif // __EFFECT_PK_ZONE_RESURRECTION__
