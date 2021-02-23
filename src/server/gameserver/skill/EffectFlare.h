//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFlare.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FLARE__
#define __EFFECT_FLARE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFlare
//////////////////////////////////////////////////////////////////////////////

class EffectFlare : public Effect 
{
public:
	EffectFlare(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FLARE; }

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

	int getLevel() const throw() { return m_Level; }
	void setLevel(int Level) throw() { m_Level = Level; }

	Sight_t getOldSight() const throw() { return m_OldSight; }
	void setOldSight(Sight_t OldSight) throw() { m_OldSight = OldSight; }

private:
	int		m_Level;
	Sight_t m_OldSight;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectFlareLoader
//////////////////////////////////////////////////////////////////////////////

class EffectFlareLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_FLARE; }
	virtual string getEffectClassName() const throw() { return "EffectFlare"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectFlareLoader* g_pEffectFlareLoader;

#endif // __EFFECT_YELLOW_POISON_TO_CREATURE__
