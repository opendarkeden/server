//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectOnBridge.h
// Written by  : 
// Description : OnBridge에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ON_BRIDGE__
#define __EFFECT_ON_BRIDGE__

#include "Effect.h"
#include "EffectLoader.h"

class Zone;

//////////////////////////////////////////////////////////////////////////////
// class EffectOnBridge
//////////////////////////////////////////////////////////////////////////////

class EffectOnBridge : public Effect 
{
public:
	EffectOnBridge(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ON_BRIDGE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

};

class EffectOnBridgeLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_ON_BRIDGE; }
	virtual string getEffectClassName() const throw() { return "EffectOnLoader"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
	virtual void load(Zone* pZone) throw(Error);
};

extern EffectOnBridgeLoader* g_pEffectOnBridgeLoader;

#endif // __EFFECT_ON_BRIDGE__
