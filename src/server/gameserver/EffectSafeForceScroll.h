//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSafeForceScroll.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SAFE_FORCE_SCROLL__
#define __EFFECT_SAFE_FORCE_SCROLL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSafeForceScroll
//////////////////////////////////////////////////////////////////////////////

class EffectSafeForceScroll : public Effect
{
public:
	EffectSafeForceScroll(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SAFE_FORCE_SCROLL; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error); 
	void unaffect(Creature* pCreature) throw(Error);

	virtual void create(const string& ownerID ) throw(Error);
	virtual void destroy(const string& ownerID ) throw(Error);
	virtual void save(const string& ownerID ) throw(Error);

	string toString() const throw();

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectSafeForceScrollLoader
//////////////////////////////////////////////////////////////////////////////

class EffectSafeForceScrollLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_SAFE_FORCE_SCROLL; }
	virtual string getEffectClassName() const throw() { return "EffectSafeForceScroll"; }

public:
	virtual void load(Creature* pCreature ) throw(Error);
};

extern EffectSafeForceScrollLoader* g_pEffectSafeForceScrollLoader;

#endif 
