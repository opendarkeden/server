//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDarknessForbidden.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 DarknessForbidden의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DARKNESS_FORBIDDEN__
#define __EFFECT_DARKNESS_FORBIDDEN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDarknessForbidden
//////////////////////////////////////////////////////////////////////////////

class EffectDarknessForbidden : public Effect 
{
public:
	EffectDarknessForbidden(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DARKNESS_FORBIDDEN; }

	void unaffect() throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_DARKNESS_FORBIDDEN__
