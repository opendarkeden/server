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
	EffectAlignmentRecovery() throw(Error);
	EffectAlignmentRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay) throw(Error);
	virtual ~EffectAlignmentRecovery() throw(Error);
			
public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ALIGNMENT_RECOVERY; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	virtual void affect(Creature* pCreature) throw(Error);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() const throw();

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay() const throw() { return m_Delay; }

	void setQuantity(Alignment_t Quantity) throw() { m_AlignmentQuantity = Quantity; }
	Alignment_t getQuantity() const throw() { return m_AlignmentQuantity; }

	void setPeriod(Turn_t Period) throw() { m_Period = Period; }
	Turn_t getPeriod() const throw() { return m_Period; }
	
private:
	// 몇 초마다 TICK이 발동 되는가.
	Turn_t m_Delay;

	// 완료시 회복량
	Alignment_t m_AlignmentQuantity;

	// 회복이 완료되는데 걸리는 시간.
	Turn_t m_Period;
};

#endif
