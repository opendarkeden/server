//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKillAftermath.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_KILL_AFTERMATH__
#define __EFFECT_KILL_AFTERMATH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectKillAftermath
//////////////////////////////////////////////////////////////////////////////

class EffectKillAftermath : public Effect 
{
public:
	EffectKillAftermath(Creature* pCreature) throw(Error);
	~EffectKillAftermath() throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_KILL_AFTERMATH; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);
	virtual void save(const string & ownerID) throw(Error);

	string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class EffectKillAftermathLoader
//////////////////////////////////////////////////////////////////////////////

class EffectKillAftermathLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_KILL_AFTERMATH; }
	virtual string getEffectClassName() const throw() { return "EffectKillAftermath"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectKillAftermathLoader* g_pEffectKillAftermathLoader;

#endif // __EFFECT_KILL_AFTERMATH__
