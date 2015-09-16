//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLight.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LIGHT__
#define __EFFECT_LIGHT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLight
//////////////////////////////////////////////////////////////////////////////

class EffectLight : public Effect 
{
public:
	EffectLight(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LIGHT; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item*  pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);
	virtual void save(const string & ownerID) throw(Error);

	string toString() const throw();

public:
	Sight_t getOldSight() const throw() { return m_OldSight; }
	void setOldSight(Sight_t OldSight) throw() { m_OldSight = OldSight; }

private:
	Sight_t m_OldSight;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectLightLoader
//////////////////////////////////////////////////////////////////////////////

class EffectLightLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_LIGHT; }
	virtual string getEffectClassName() const throw() { return "EffectLight"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectLightLoader* g_pEffectLightLoader;

#endif // __EFFECT_LIGHT__
