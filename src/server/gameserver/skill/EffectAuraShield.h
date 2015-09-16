//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAuraShield.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AURA_SHIELD__
#define __EFFECT_AURA_SHIELD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAuraShield
//////////////////////////////////////////////////////////////////////////////

class EffectAuraShield : public Effect 
{
public:
	EffectAuraShield(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_AURA_SHIELD; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect() throw(Error);

	string toString() const throw();

public:
	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

private:
	Level_t m_Level;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectAuraShieldLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAuraShieldLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_AURA_SHIELD; }
	virtual string getEffectClassName() const throw() { return "EffectAuraShield"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_AURA_SHIELD__
