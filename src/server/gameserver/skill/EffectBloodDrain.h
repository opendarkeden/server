//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodDrain.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOOD_DRAIN__
#define __EFFECT_BLOOD_DRAIN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodDrain
//////////////////////////////////////////////////////////////////////////////

class EffectBloodDrain : public Effect 
{
public:
	EffectBloodDrain(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOOD_DRAIN; }

	void affect() throw(Error) { }
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

public:
	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

private:
	Level_t m_Level;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodDrainLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodDrainLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOOD_DRAIN; }
	virtual string getEffectClassName() const throw() { return "EffectBloodDrain"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectBloodDrainLoader* g_pEffectBloodDrainLoader;

#endif // __EFFECT_BLOOD_DRAIN__
