#ifndef __ZONE_ITEM_POSITION_H__
#define __ZONE_ITEM_POSITION_H__

#include "Types.h"
#include "GlobalItemPosition.h"
#include "ZoneUtil.h"

class ZoneItemPosition : public GlobalItemPosition
{

public:
	ZoneItemPosition() : GlobalItemPosition( POS_TYPE_ZONE ){ }
	~ZoneItemPosition(){ }

public:
	virtual Item*	popItem( bool bLock = true ) throw(Error);
	virtual Zone*	getZone() throw(Error) { return getZoneByZoneID( m_ZoneID ); }

	Item*		getItem( bool isDel ) throw(Error);
	Item*		getItem_LOCKED( bool isDel ) throw (Error);

	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t zoneID ) { m_ZoneID = zoneID; }

	ZoneCoord_t	getZoneX() const { return m_ZoneX; }
	void		setZoneX( ZoneCoord_t zoneX ) { m_ZoneX = zoneX; }

	ZoneCoord_t	getZoneY() const { return m_ZoneY; }
	void		setZoneY( ZoneCoord_t zoneY ) { m_ZoneY = zoneY; }

public:
	virtual string	toString() const throw(Error);

protected:
	Item*		getItemFromZone( Zone* pZone ) throw(Error);
	void		deleteItemFromZone( Zone* pZone, Item* pItem ) throw(Error);

private:
	ZoneID_t	m_ZoneID;
	ZoneCoord_t	m_ZoneX;
	ZoneCoord_t m_ZoneY;
};

#endif // __ZONE_ITEM_POSITION_H__
