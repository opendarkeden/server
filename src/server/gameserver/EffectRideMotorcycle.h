//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRideMotorcycle.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RIDE_MOTORCYCLE_H__
#define __EFFECT_RIDE_MOTORCYCLE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRideMotorcycle;
// 일정 시간이 지나서 바닥의 아이템은 사라지고
// 다른 존으로 옮겨지게 된다.
//////////////////////////////////////////////////////////////////////////////

class Slayer;
class Item;

class EffectRideMotorcycle : public Effect 
{
public:
	EffectRideMotorcycle(Slayer* pOwner, Item* pMotorcycle, ZoneCoord_t motorX, ZoneCoord_t motorY) throw(Error);
	virtual ~EffectRideMotorcycle() throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	void unaffect() throw(Error);

	// get debug string
	string toString() const throw();

private:
	ZoneCoord_t m_MotorX; 
	ZoneCoord_t m_MotorY;
	ObjectID_t	m_OwnerObjectID;
	Item*		m_pMotorcycle;
};

#endif
