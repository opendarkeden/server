#ifndef __SUB_INVENTORY_ITEM_POSITION_H__
#define __SUB_INVENTORY_ITEM_POSITION_H__

#include "Types.h"
#include "GlobalItemPosition.h"
#include "PlayerCreature.h"


class Item;
class Zone;

class SubInventoryItemPosition : public GlobalItemPosition
{

public:
	SubInventoryItemPosition() : GlobalItemPosition(POS_TYPE_SUB_INVENTORY ){ m_bSetZone = false; }
	~SubInventoryItemPosition(){ }

public:
	virtual Item*	popItem(bool bLock = true ) throw(Error);
	virtual Zone*	getZone() throw(Error);

public:
	string			getOwnerName() const { return m_OwnerName; }
	void			setOwnerName(const string& ownerName ) { m_bSetZone = false; m_OwnerName = ownerName; }

	ItemID_t		getSubInventoryID() const { return m_SubInventoryID; }
	void			setSubInventoryID(ItemID_t subInventoryID ) { m_SubInventoryID = subInventoryID; }

	CoordInven_t	getInventoryX() const { return m_InvenX; }
	void			setInventoryX(CoordInven_t invenX ) { m_bSetZone = false; m_InvenX = invenX; }

	CoordInven_t	getInventoryY() const { return m_InvenY; }
	void			setInventoryY(CoordInven_t invenY ) { m_bSetZone = false; m_InvenY = invenY; }

	string			toString() const throw(Error);

protected:
	Creature*		findCreature() throw(Error);
	Zone*			getZoneByCreature(Creature* pCreature ) throw(Error);
	Item*			popItem_CORE(PlayerCreature* pPC ) throw(Error);
	Item*			popItem_LOCKED() throw(Error);
	Item*			popItem_UNLOCKED() throw(Error);

private:
	string			m_OwnerName;
	ItemID_t		m_SubInventoryID;
	CoordInven_t	m_InvenX;
	CoordInven_t	m_InvenY;

	// getZone À» À§ÇÑ......
	Zone*			m_pZone;
	bool			m_bSetZone;
};

#endif // __INVENTORY_ITEM_POSITION_H__
