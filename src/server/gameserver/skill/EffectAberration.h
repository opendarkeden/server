//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAberration.h
// Written by  : 
// Description : Aberration에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ABERRATION__
#define __EFFECT_ABERRATION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAberration
//////////////////////////////////////////////////////////////////////////////

class EffectAberration : public Effect 
{
public:
	EffectAberration(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ABERRATION; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getRatio() const { return m_Ratio; }
	void setRatio(int ratio) throw() { m_Ratio = ratio; }

private:
	int m_Ratio;
};

#endif // __EFFECT_ABERRATION__
