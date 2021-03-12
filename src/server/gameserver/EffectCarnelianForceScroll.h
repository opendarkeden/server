//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCarnelianForceScroll.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CARNELIAN_FORCE_SCROLL__
#define __EFFECT_CARNELIAN_FORCE_SCROLL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCarnelianForceScroll
//////////////////////////////////////////////////////////////////////////////

class EffectCarnelianForceScroll : public Effect
{
public:
	EffectCarnelianForceScroll(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_CARNELIAN_FORCE_SCROLL; }

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
// class EffectCarnelianForceScrollLoader
//////////////////////////////////////////////////////////////////////////////

class EffectCarnelianForceScrollLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_CARNELIAN_FORCE_SCROLL; }
	virtual string getEffectClassName() const  { return "EffectCarnelianForceScroll"; }

public:
	virtual void load(Creature* pCreature ) ;
};

extern EffectCarnelianForceScrollLoader* g_pEffectCarnelianForceScrollLoader;

#endif 

