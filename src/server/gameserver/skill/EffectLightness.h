//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLightness.h
// Written by  : excel96
// Description : 
// Lightness에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LIGHTNESS__
#define __EFFECT_LIGHTNESS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLightness
//////////////////////////////////////////////////////////////////////////////

class EffectLightness : public Effect 
{
public:
	EffectLightness(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LIGHTNESS; }

	void affect() {}

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

};

#endif // __EFFECT_LIGHTNESS__
