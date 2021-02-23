//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVampirePortal.h
// Written by  : excel96
// Description : 
// 뱀파이어가 포탈을 열 경우, 포탈을 연 곳과 목표 지점에 동시에 생기는
// 타일에 붙은 뱀파이어 포탈 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VAMPIRE_PORTAL__
#define __EFFECT_VAMPIRE_PORTAL__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectVampirePortal
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItem;

class EffectVampirePortal : public Effect 
{
public:
	EffectVampirePortal(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_VAMPIRE_PORTAL; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error) {};
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();

public:
	string getOwnerID(void) const { return m_OwnerID; }
	void setOwnerID(string ownerID) { m_OwnerID = ownerID; }

	ZONE_COORD getZoneCoord(void) const { return m_ZoneCoord; }
	void setZoneCoord(ZONE_COORD& rCoord) { m_ZoneCoord = rCoord; }
	void setZoneCoord(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y) { m_ZoneCoord.id = id; m_ZoneCoord.x = x; m_ZoneCoord.y = y; }

	Duration_t getDuration() const { return m_Duration;}
	void setDuration(Duration_t d) { m_Duration = d;}

	int getCount(void) const { return m_Count; }
	void setCount(int count) { m_Count = count; }

private:
	string      m_OwnerID;   // 이 포탈의 주인
	ZONE_COORD  m_ZoneCoord; // 포탈의 목표 존 ID 및 좌표
	Duration_t  m_Duration;  // 마법의 지속 시간
	int         m_Count;     // 이 포탈을 사용할 수 있는 최대 횟수
};

#endif // __EFFECT_VAMPIRE_PORTAL__
