#ifndef __EFFECT_CASTING_TRAP_H__
#define __EFFECT_CASTING_TRAP_H__

#include "Effect.h"

class EffectCastingIcicleTrap : public Effect
{
public:
	EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }
	EffectCastingIcicleTrap( EffectClass IcicleEffect, Zone* pZone ) : Effect( pZone, 0, 0, NULL, 99999999 ), m_IcicleEffect(IcicleEffect), m_bLarge(false) { }

	void setStartXY( ZoneCoord_t x, ZoneCoord_t y ) { m_StartX = x; m_StartY = y; }
	void setDir(Dir_t dir) { m_Dir = dir; }
	void setLength(int len) { m_Length = len; }
	void setTick(Turn_t tick) { m_Tick = tick; }
	void setUnit(int unit) { m_Unit = unit; }
	void setLarge(bool large) { m_bLarge = large; }

	void affect() throw(Error);
	void unaffect() throw(Error) { }

	string toString() const throw() { return "EffectCastingIcicleTrap"; }

private:
	EffectClass	m_IcicleEffect;
	ZoneCoord_t	m_StartX, m_StartY;
	Dir_t		m_Dir;
	int			m_Length;
	Turn_t		m_Tick;
	int			m_Unit;
	bool		m_bLarge;
};

class EffectCastingSideTrap : public Effect
{
public:
	EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }
	EffectCastingSideTrap( Zone* pZone ) : Effect( pZone, 0, 0, NULL, 99999999 ) { }

	void setStartXY( ZoneCoord_t x, ZoneCoord_t y ) { m_StartX = x; m_StartY = y; }
	void setDir(Dir_t dir) { m_Dir = dir; }
	void setLength(int len) { m_Length = len; }
	void setTick(Turn_t tick) { m_Tick = tick; }
	void setUnit(int unit) { m_Unit = unit; }

	void affect() throw(Error);
	void unaffect() throw(Error) { }

	string toString() const throw() { return "EffectCastingSideTrap"; }

private:
	ZoneCoord_t	m_StartX, m_StartY;
	Dir_t		m_Dir;
	int			m_Length;
	Turn_t		m_Tick;
	int			m_Unit;
};

class EffectCastingIceWall : public Effect
{
public:
	EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }
	EffectCastingIceWall( Zone* pZone ) : Effect( pZone, 0, 0, NULL, 99999999 ), m_State(0) { }

	void setStartXY( ZoneCoord_t x, ZoneCoord_t y ) { m_StartX = x; m_StartY = y; }
	void setDir(Dir_t dir) { m_Dir = dir; }
	void setLength(int len) { m_Length = len; }
	void setWallLength(int len) { m_WallLength = len; }
	void setTick(Turn_t tick) { m_Tick = tick; }

	void affect() throw(Error);
	void unaffect() throw(Error) { }

	string toString() const throw() { return "EffectCastingSideTrap"; }

private:
	ZoneCoord_t	m_StartX, m_StartY;
	Dir_t		m_Dir;
	int			m_Length;
	int			m_WallLength;
	Turn_t		m_Tick;
	int			m_State;
};

#endif
