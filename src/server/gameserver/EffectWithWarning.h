#ifndef __EFFECT_WITH_WARNING_H__
#define __EFFECT_WITH_WARNING_H__

#include "Effect.h"

class EffectWithWarning : public Effect
{
public:
	EffectWithWarning(EffectClass sE, EffectClass mE, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) : Effect(pZone, x, y, NULL, 99999999), m_SignEffect(sE), m_MainEffect(mE), m_SignDuration(15), m_MainDuration(20), m_State(false) { }
	EffectClass	getEffectClass() const ;

	void affect() ;
	void unaffect() ;

	void	setSignDuration( Turn_t turn ) { m_SignDuration = turn; }
	void	setMainDuration( Turn_t turn ) { m_MainDuration = turn; }

	void start();

private:
	EffectClass	m_SignEffect;
	EffectClass m_MainEffect;
	Turn_t		m_SignDuration;
	Turn_t		m_MainDuration;
	bool		m_State;
};

class EffectIcicle : public EffectWithWarning
{
public:
	EffectIcicle(EffectClass icicle, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) : EffectWithWarning( (EffectClass)(icicle + 1), icicle, pZone, x, y ) { }
	void affect() ;

	string toString() const  { return "EffectIcicle"; }
};

class EffectLargeIcicle : public EffectWithWarning
{
public:
	EffectLargeIcicle(EffectClass icicle, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) : EffectWithWarning( (EffectClass)(icicle + 1), icicle, pZone, x, y ) { }
	void affect() ;

	string toString() const  { return "EffectLargeIcicle"; }
};

class EffectSideTrap : public EffectWithWarning
{
public:
	EffectSideTrap(EffectClass icicle, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) : EffectWithWarning( (EffectClass)(icicle + 1), icicle, pZone, x, y ) { m_Dir = 0; }
	void affect() ;

	void setDir( Dir_t dir ) { m_Dir = dir; }

	string toString() const  { return "EffectSideTrap"; }

private:
	Dir_t	m_Dir;
};

#endif
