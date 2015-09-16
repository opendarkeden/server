//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRegenerate.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REGENERATE__
#define __EFFECT_REGENERATE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRegenerate
//////////////////////////////////////////////////////////////////////////////

class EffectRegenerate : public Effect 
{
public:
	EffectRegenerate(Creature* pCreature) throw(Error);
	~EffectRegenerate() throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	void affect() throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

	void setPoint(HP_t point) { m_Point = point; }
	void setTick(Turn_t tick) { m_Tick = tick; }

private:
	HP_t	m_Point;
	Turn_t	m_Tick;
};


#endif // __EFFECT_REGENERATE__
