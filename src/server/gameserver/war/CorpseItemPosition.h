#ifndef __CORPSE_ITEM_POSITION_H__
#define __CORPSE_ITEM_POSITION_H__

#include "Types.h"
#include "GlobalItemPosition.h"

class Item;

class CorpseItemPosition : public GlobalItemPosition
{

public:
	CorpseItemPosition() : GlobalItemPosition( POS_TYPE_CORPSE ){ }
	~CorpseItemPosition(){ }

public:
	virtual Item*	popItem( bool bLock = true ) throw(Error);
	virtual Item*	getItem_LOCKED( bool isDel ) throw(Error);
	virtual Item*	getItem_UNLOCKED( bool isDel ) throw(Error);

	Zone*   getZone() throw(Error)	{ return m_pZone; }

	ZoneID_t		getZoneID() const { return m_ZoneID; }
	void			setZoneID( ZoneID_t zoneID ) { m_ZoneID = zoneID; }

	ObjectID_t		getObjectID() const { return m_ObjectID; }
	void			setObjectID( ObjectID_t objectID ) { m_ObjectID = objectID; }

	ObjectID_t		getCorpseObjectID() const { return m_CorpseObjectID; }
	void			setCorpseObjectID( ObjectID_t objectID ) { m_CorpseObjectID = objectID; }

public:
	virtual string	toString() const throw(Error);

protected:
	Item*			getItem_CORE(Zone* pZone, bool isDel) throw(Error);

private:
	ZoneID_t	m_ZoneID;
	Zone*		m_pZone;
	ObjectID_t	m_CorpseObjectID;
	ObjectID_t	m_ObjectID;
};

#endif // __CORPSE_ITEM_POSITION_H__
