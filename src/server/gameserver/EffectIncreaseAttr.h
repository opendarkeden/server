//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIncreaseAttr.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INCREASE_ATTR__
#define __EFFECT_INCREASE_ATTR__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIncreaseAttr
//////////////////////////////////////////////////////////////////////////////

class EffectIncreaseAttr : public Effect 
{
public:
	EffectIncreaseAttr(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_INCRASE_ATTR; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();

public:
	int getSTRBonus(void) const { return m_STRBonus; }
	void setSTRBonus(int bonus) { m_STRBonus = bonus; }

	int getDEXBonus(void) const { return m_DEXBonus; }
	void setDEXBonus(int bonus) { m_DEXBonus = bonus; }

	int getINTBonus(void) const { return m_INTBonus; }
	void setINTBonus(int bonus) { m_INTBonus = bonus; }

private :
	int m_STRBonus;
	int m_DEXBonus;
	int m_INTBonus;
};

#endif // __EFFECT_BLESS__
