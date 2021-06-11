//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAlignmentRecovery.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ALIGNMENT_RECOVERY_H__
#define __EFFECT_ALIGNMENT_RECOVERY_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAlignmentRecovery;
//////////////////////////////////////////////////////////////////////////////

class EffectAlignmentRecovery : public Effect 
{
public:
	EffectAlignmentRecovery() ;
	EffectAlignmentRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay) ;
	virtual ~EffectAlignmentRecovery() ;
			
public:
	virtual EffectClass getEffectClass() const  { return EFFECT_CLASS_ALIGNMENT_RECOVERY; }

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

	void setQuantity(Alignment_t Quantity)  { m_AlignmentQuantity = Quantity; }
	Alignment_t getQuantity() const  { return m_AlignmentQuantity; }

	void setPeriod(Turn_t Period)  { m_Period = Period; }
	Turn_t getPeriod() const  { return m_Period; }
	
private:
	// 몇 초마다 TICK이 발동 되는가.
	Turn_t m_Delay;

	// 완료시 회복량
	Alignment_t m_AlignmentQuantity;

	// 회복이 완료되는데 걸리는 시간.
	Turn_t m_Period;
};

#endif
