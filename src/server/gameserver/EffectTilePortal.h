//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTilePortal.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TILE_PORTAL__
#define __EFFECT_TILE_PORTAL__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTilePortal
//////////////////////////////////////////////////////////////////////////////

class TilePortalItem;

class EffectTilePortal : public Effect 
{
public:
	EffectTilePortal(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TILE_PORTAL; }

	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error) {};
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);

	string toString() const throw();

public:
	ZONE_COORD getZoneCoord(void) const { return m_ZoneCoord; }
	void setZoneCoord(ZONE_COORD& rCoord) { m_ZoneCoord = rCoord; }
	void setZoneCoord(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y) { m_ZoneCoord.id = id; m_ZoneCoord.x = x; m_ZoneCoord.y = y; }

private:
	ZONE_COORD  m_ZoneCoord; // Æ÷Å»ÀÇ ¸ñÇ¥ Á¸ ID ¹× ÁÂÇ¥
};

#endif // __EFFECT_TILE_PORTAL__
