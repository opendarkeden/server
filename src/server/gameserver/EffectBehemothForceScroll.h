//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBehemothForceScroll.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BEHEMOTH_FORCE_SCROLL__
#define __EFFECT_BEHEMOTH_FORCE_SCROLL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBehemothForceScroll
//////////////////////////////////////////////////////////////////////////////

class EffectBehemothForceScroll : public Effect
{
public:
	EffectBehemothForceScroll(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_BEHEMOTH_FORCE_SCROLL; }

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
// class EffectBehemothForceScrollLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBehemothForceScrollLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_BEHEMOTH_FORCE_SCROLL; }
	virtual string getEffectClassName() const  { return "EffectBehemothForceScroll"; }

public:
	virtual void load(Creature* pCreature ) ;
};

extern EffectBehemothForceScrollLoader* g_pEffectBehemothForceScrollLoader;

#endif 

