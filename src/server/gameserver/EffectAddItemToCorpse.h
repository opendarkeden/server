//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAddItemToCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ADD_ITEM_TO_CORPSE_H__
#define __EFFECT_ADD_ITEM_TO_CORPSE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAddItemToCorpse;
// 아이템을 시체에 추가한다.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectAddItemToCorpse : public Effect 
{
public:
	EffectAddItemToCorpse(Zone* pZone, Item* pItem, ObjectID_t corpseObjectID, Turn_t delay) throw(Error);
	virtual ~EffectAddItemToCorpse() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ADD_ITEM_TO_CORPSE; }

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

	void		setCorpseObjectID(ObjectID_t objectID) 	{ m_CorpseObjectID = objectID; }
	ObjectID_t	getCorpseObjectID() const				{ return m_CorpseObjectID; }
	
	// get debug string
	virtual string toString() const throw();

private:
	ObjectID_t m_CorpseObjectID;
};

#endif
