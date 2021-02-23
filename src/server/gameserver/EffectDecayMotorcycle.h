//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecayMotorcycle.h
// Written by  : Reiot
// Description :
//               일정 시간이 지나면 바닥에 있는 아이템을 사라지게 하는 
//               EffectDecayItem의 별종으로,
//               Motorcycle에만 적용된다. 
//               기존에 Motorcycle을 다른 Zone에 가지고 있는 사용자가 
//               Motorcycle을 call하게 되면, 기존의 motorcycle을 없애고
//               새로운 Motorcycle을 만들어 주어야 한다.
//               이 과정에서
//                 1. 모터사이클을 없애는 과정
//                 2. 새로 생성화는 과정이 순차적으로 일어나야 하며
//               다른 존에 영향을 끼쳐서는 안 된다. 그러므로 이런 방식으로
//               Effect를 통해서 heartbeat시에 motorcycle을 없애고
//               새로운 Effect를 통해서 다음 heartbeat시에 motorcycle을 만든다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECAY_MOTORCYCLE_H__
#define __EFFECT_DECAY_MOTORCYCLE_H__

#include "Effect.h"

class Item;
class Zone;
class Slayer;

class EffectDecayMotorcycle : public Effect 
{
public:
	EffectDecayMotorcycle(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay, bool bDeleteFromDB=true) throw(Error);
	virtual ~EffectDecayMotorcycle() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DECAY_ITEM; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Item* pItem = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget, Slayer* pSlayer) throw(Error);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() const throw();

private:
	ObjectID_t m_ObjectID;
	bool	   m_bDeleteFromDB;
};

#endif
