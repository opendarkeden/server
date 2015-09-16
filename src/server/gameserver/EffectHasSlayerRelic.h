//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasSlayerRelic.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_SLAYER_RELIC__
#define __EFFECT_HAS_SLAYER_RELIC__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasSlayerRelic
//////////////////////////////////////////////////////////////////////////////

class EffectHasSlayerRelic : public EffectHasRelic 
{
public:
	EffectHasSlayerRelic(Creature* pCreature) throw(Error);
	EffectHasSlayerRelic(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HAS_SLAYER_RELIC; }

	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	string toString() const throw();
};

#endif // __EFFECT_DOOM__
