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
	EffectLight(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LIGHT; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item*  pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	virtual void create(const string & ownerID) ;
	virtual void destroy(const string & ownerID) ;
	virtual void save(const string & ownerID) ;

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
	virtual void load(Creature* pCreature) ;

};

extern EffectLightLoader* g_pEffectLightLoader;

#endif // __EFFECT_LIGHT__
