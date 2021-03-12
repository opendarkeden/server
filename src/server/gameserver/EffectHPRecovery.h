//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHPRecovery.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HP_RECOVERY_H__
#define __EFFECT_HP_RECOVERY_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHPRecovery;
//////////////////////////////////////////////////////////////////////////////

class EffectHPRecovery : public Effect 
{
public:
	EffectHPRecovery() ;
	EffectHPRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay) ;
	virtual ~EffectHPRecovery() ;
	
public:
	virtual EffectClass getEffectClass() const  { return EFFECT_CLASS_HP_RECOVERY; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() ;
	virtual void affect(Creature* pCreature) ;
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) ;
	
	virtual void unaffect() ;
	virtual void unaffect(Creature* pCreature) ;
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) ;
	void unaffect(Item* pItem)  {}

	void create(const string & ownerID)  {}
	void save(const string & ownerID)  {}
	void destroy(const string & ownerID)  {}
	
	virtual string toString() const ;

public:
	void setDelay(Turn_t delay)  { m_Delay = delay; }
	Turn_t getDelay() const  { return m_Delay; }

	void setHPQuantity(HP_t Quantity)  { m_HPQuantity = Quantity; }
	HP_t getHPQuantity() const  { return m_HPQuantity; }

	void setPeriod(Turn_t Period)  { m_Period = Period; }
	Turn_t getPeriod() const  { return m_Period; }

private:
	Turn_t m_Delay;      // 몇 초마다 TICK이 발동 되는가.
	HP_t   m_HPQuantity; // 완료시 회복량
	Turn_t m_Period;     // 회복이 완료되는데 걸리는 시간.

};

#endif
