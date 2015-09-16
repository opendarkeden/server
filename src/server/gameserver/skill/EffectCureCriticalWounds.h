//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCureCriticalWounds.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 CureCriticalWounds의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CURE_CRITICAL_WOUNDS__
#define __EFFECT_CURE_CRITICAL_WOUNDS__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCureCriticalWounds
//////////////////////////////////////////////////////////////////////////////

class EffectCureCriticalWounds : public Effect 
{
public:
	EffectCureCriticalWounds(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CURE_CRITICAL_WOUNDS; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	// unaffect method
	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	Range_t getRange() const throw() { return m_Range; }
	void setRange(HP_t Range) throw() { m_Range = Range; }

	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setDelay(Turn_t Delay) throw() { m_Delay = Delay; }
	Turn_t getDelay() const throw() { return m_Delay; }

private:

	Range_t m_Range;
	HP_t    m_Point;
	Turn_t  m_Delay;

};

#endif // __EFFECT_CURE_CRITICAL_WOUNDS__
