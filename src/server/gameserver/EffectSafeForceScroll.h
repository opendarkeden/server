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
	EffectSafeForceScroll(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_SAFE_FORCE_SCROLL; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ; 
	void unaffect(Creature* pCreature) ;

	virtual void create(const string& ownerID ) ;
	virtual void destroy(const string& ownerID ) ;
	virtual void save(const string& ownerID ) ;

	string toString() const ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectSafeForceScrollLoader
//////////////////////////////////////////////////////////////////////////////

class EffectSafeForceScrollLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_SAFE_FORCE_SCROLL; }
	virtual string getEffectClassName() const  { return "EffectSafeForceScroll"; }

public:
	virtual void load(Creature* pCreature ) ;
};

extern EffectSafeForceScrollLoader* g_pEffectSafeForceScrollLoader;

#endif 
