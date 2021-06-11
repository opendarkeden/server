//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDenialMagic.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DENIAL_MAGIC__
#define __EFFECT_DENIAL_MAGIC__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDenialMagic
//////////////////////////////////////////////////////////////////////////////

class EffectDenialMagic : public Effect 
{
public:
	EffectDenialMagic(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DENIAL_MAGIC; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect(Item* pItem)  {}
	void unaffect() ;

	string toString() const throw();

public:

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectDenialMagicLoader
//////////////////////////////////////////////////////////////////////////////

class EffectDenialMagicLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_DENIAL_MAGIC; }
	virtual string getEffectClassName() const throw() { return "EffectDenialMagic"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_DENIAL_MAGIC__
