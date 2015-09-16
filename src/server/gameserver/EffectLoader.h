//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoader.h
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOADER_H__
#define __EFFECT_LOADER_H__

#include "Types.h"
#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLoader;
//////////////////////////////////////////////////////////////////////////////

class Creature;

class EffectLoader 
{
public:
	virtual ~EffectLoader() {}

public:
	virtual Effect::EffectClass getEffectClass() const throw() = 0;
	virtual string getEffectClassName() const throw() = 0;
	virtual void load(Creature* pCreature) throw(Error) = 0;
	virtual void load(Zone* pZone) throw(Error) { }
};

#endif
