//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAftermath.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AFTERMATH__
#define __EFFECT_AFTERMATH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAftermath
//////////////////////////////////////////////////////////////////////////////

class EffectAftermath : public Effect 
{
public:
	EffectAftermath(Creature* pCreature) throw(Error);
	~EffectAftermath() throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_AFTERMATH; }

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
// class EffectAftermathLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAftermathLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_AFTERMATH; }
	virtual string getEffectClassName() const throw() { return "EffectAftermath"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectAftermathLoader* g_pEffectAftermathLoader;

#endif // __EFFECT_AFTERMATH__
