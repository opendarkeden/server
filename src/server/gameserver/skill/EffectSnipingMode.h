//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSnipingMode.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SNIPING_MODE__
#define __EFFECT_SNIPING_MODE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSnipingMode
//////////////////////////////////////////////////////////////////////////////

class EffectSnipingMode : public Effect 
{
public:
	EffectSnipingMode(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SNIPING_MODE; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	int getRevealRatio(void) const { return m_RevealRatio; }
	void setRevealRatio(int ratio) { m_RevealRatio = ratio; }

	/*
	int getToHitBonus(void) const { return m_ToHitBonus; }
	void setToHitBonus(int bonus) { m_ToHitBonus = bonus; }
	
	int getDamageBonus(void) const { return m_DamageBonus; }
	void setDamageBonus(int bonus) { m_DamageBonus = bonus; }
	*/

private:
	int m_RevealRatio;

	//int m_ToHitBonus;
	//int m_DamageBonus;
};

#endif // __EFFECT_SNIPING_MODE__
