//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectYellowPoison.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_YELLOW_POISON__
#define __EFFECT_YELLOW_POISON__

#include "Tile.h"
#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectYellowPoison
//////////////////////////////////////////////////////////////////////////////

class EffectYellowPoison : public Effect 
{
public:
	EffectYellowPoison(Zone*, ZoneCoord_t, ZoneCoord_t) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_YELLOW_POISON; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error); 
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect(Item*  pItem) throw(Error) {}

	string toString() const throw();

public:
	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t d) throw() { m_Duration = d; }
	
	Attr_t getLevel() const throw() { return m_Level; }
	void setLevel(Attr_t l) throw() { m_Level = l; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() { return m_bVampire; }

	void setForce( bool force ) { m_bForce = force; }
	bool isForce() { return m_bForce; }
	
	bool affectCreature(Creature* pCreature, bool bAffectByMove) throw(Error); 

private:
	Duration_t m_Duration;
	Attr_t     m_Level;

	bool       m_bVampire;
	bool	   m_bForce;
};

class EffectYellowPoisonLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_YELLOW_POISON; }
	virtual string getEffectClassName() const throw() { return "EffectYellowPoison"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
	virtual void load(Zone* pZone) throw(Error);
};

extern EffectYellowPoisonLoader* g_pEffectYellowPoisonLoader;

#endif // __EFFECT_YELLOW_POISON__
