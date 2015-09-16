//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRecallMotorcycle.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RECALL_MOTORCYCLE_H__
#define __EFFECT_RECALL_MOTORCYCLE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRecallMotorcycle;
// 일정 시간이 지나서 바닥의 아이템은 사라지고
// 다른 존으로 옮겨지게 된다.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectRecallMotorcycle : public Effect 
{
public:
	EffectRecallMotorcycle(Zone* pZone, ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, ObjectID_t ownerOID, Turn_t delay) throw(Error);
	virtual ~EffectRecallMotorcycle() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	void unaffect() throw(Error);

	// get debug string
	virtual string toString() const throw();

private:
	ZoneCoord_t m_StartX; 
	ZoneCoord_t m_StartY;
	Zone*		m_pTargetZone;
	ObjectID_t  m_ObjectID;
	ObjectID_t	m_OwnerOID;
};

#endif
