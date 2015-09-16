//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransportItemToCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSPORT_ITEM_TO_CORPSE_H__
#define __EFFECT_TRANSPORT_ITEM_TO_CORPSE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransportItemToCorpse;
// 일정 시간이 지나서 바닥의 아이템은 사라지고
// 다른 존으로 옮겨지게 된다.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectTransportItemToCorpse : public Effect 
{
public:
	EffectTransportItemToCorpse(Zone* pZone, Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID, Turn_t delay) throw(Error);
	virtual ~EffectTransportItemToCorpse() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM_TO_CORPSE; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Item* pItem = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() const throw();

private:
	Zone*		m_pTargetZone;
	ObjectID_t  m_CorpseObjectID;
};

#endif
