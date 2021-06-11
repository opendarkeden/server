//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDarkBluePoison.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DARKBLUE_POISON__
#define __EFFECT_DARKBLUE_POISON__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDarkBluePoison
//////////////////////////////////////////////////////////////////////////////

class EffectDarkBluePoison : public Effect 
{
public:
	EffectDarkBluePoison(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DARKBLUE_POISON; }

	void affect() ;
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:
	MP_t getDamage(void) const { return m_Damage; }
	void setDamage(MP_t Damage) { m_Damage = Damage; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int l) { m_Level = l;}

	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }
	Turn_t getTick() const throw() { return m_Tick; }
	
	Duration_t getDuration() { return m_Duration;}
	void setDuration(Duration_t d) { m_Duration = d;}

	bool affectCreature(Creature* pCreature, bool bAffectByMove) ;

private:
	int        m_Level;
	MP_t       m_Damage;
	Duration_t m_Duration;
	Turn_t     m_Tick;
};

#endif // __EFFECT_DARKBLUE_POISON__
