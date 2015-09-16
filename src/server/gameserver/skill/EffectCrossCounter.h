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
	EffectCrossCounter(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CROSS_COUNTER; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

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
	virtual void load(Creature* pCreature) throw(Error) {}

};

extern EffectCrossCounterLoader* g_pEffectCrossCounterLoader;

#endif // __EFFECT_CROSS_COUNTER__
