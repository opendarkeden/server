//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCrossCounter.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CROSS_COUNTER__
#define __EFFECT_CROSS_COUNTER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCrossCounter
//////////////////////////////////////////////////////////////////////////////

class EffectCrossCounter : public Effect 
{
public:
	EffectCrossCounter(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CROSS_COUNTER; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();

private:

};

//////////////////////////////////////////////////////////////////////////////
// class EffectCrossCounterLoader
//////////////////////////////////////////////////////////////////////////////

class EffectCrossCounterLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_CROSS_COUNTER; }
	virtual string getEffectClassName() const throw() { return "EffectCrossCounter"; }

public:
	virtual void load(Creature* pCreature)  {}

};

extern EffectCrossCounterLoader* g_pEffectCrossCounterLoader;

#endif // __EFFECT_CROSS_COUNTER__
