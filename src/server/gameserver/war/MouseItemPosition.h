#ifndef __MOUSE_ITEM_POSITION_H__
#define __MOUSE_ITEM_POSITION_H__

#include "Types.h"
#include "GlobalItemPosition.h"

class Creature;
class Zone;

class MouseItemPosition : public GlobalItemPosition
{

public:
	MouseItemPosition() : GlobalItemPosition( POS_TYPE_MOUSE ){ m_bSetZone = false; }
	~MouseItemPosition(){ }

public:
	virtual Item*	popItem( bool bLock = true ) throw(Error);
	virtual Zone*	getZone() throw(Error);

	string			getOwnerName() const { return m_OwnerName; }
	void			setOwnerName( const string& ownerName ) { m_bSetZone = false; m_OwnerName = ownerName; }

public:
	virtual string	toString() const throw(Error);

protected:
	Item*			popItem_LOCKED() throw (Error);
	Item*			popItem_UNLOCKED() throw (Error);
	Creature*		findCreature() throw (Error);
	Zone*			getZoneByCreature( Creature* pCreature ) throw (Error);
	Item*			popItem_CORE( PlayerCreature* pPC ) throw (Error);

private:
	string			m_OwnerName;

	// getZone À» À§ÇÑ......
	Zone*			m_pZone;
	bool			m_bSetZone;
};

#endif // __MOUSE_ITEM_POSITION_H__
