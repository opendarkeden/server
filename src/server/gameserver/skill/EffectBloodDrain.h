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
	EffectBloodDrain(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOOD_DRAIN; }

	void affect()  { }
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
	virtual void load(Creature* pCreature) ;

};

extern EffectBloodDrainLoader* g_pEffectBloodDrainLoader;

#endif // __EFFECT_BLOOD_DRAIN__
