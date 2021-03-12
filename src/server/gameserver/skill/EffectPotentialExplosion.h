//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPotentialExplosion.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_POTENTIAL_EXPLOSION__
#define __EFFECT_POTENTIAL_EXPLOSION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPotentialExplosion
//////////////////////////////////////////////////////////////////////////////

class EffectPotentialExplosion : public Effect 
{
public:
	EffectPotentialExplosion(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_POTENTIAL_EXPLOSION; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect() ; 
	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:
	int getDiffSTR(void) throw() { return m_diffSTR;}
	int getDiffDEX(void) throw() { return m_diffDEX;}
	void setDiffSTR(int diffSTR)  { m_diffSTR = diffSTR;}
	void setDiffDEX(int diffDEX)  { m_diffDEX = diffDEX;}

private :
	int m_diffSTR;
	int m_diffDEX;
};

#endif // __EFFECT_POTENTIAL_EXPLOSION__
