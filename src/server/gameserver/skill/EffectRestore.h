//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRestore.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RESTORE__
#define __EFFECT_RESTORE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRestore
//////////////////////////////////////////////////////////////////////////////

class EffectRestore : public Effect 
{
public:
	EffectRestore(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RESTORE; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Item* pItem)  {}
	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	virtual void create(const string & ownerID) ;
	virtual void destroy(const string & ownerID) ;
	virtual void save(const string & ownerID) ;

	string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class EffectRestoreLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRestoreLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_RESTORE; }
	virtual string getEffectClassName() const throw() { return "EffectRestore"; }

public:
	virtual void load(Creature* pCreature) ;

};

extern EffectRestoreLoader* g_pEffectRestoreLoader;

#endif // __EFFECT_RESTORE__
