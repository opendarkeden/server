//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEnergyDropToCreature.h
// Written by  : 장홍창
// Date        : 2002. 3. 28
//
// Description : EffectEnergyDropToCreature는 상대방에게 3번의 연속 타격을
//               주는 이펙트이다. 
//               Effect 시리즈는 Tick과 deadline을 사용해서 임의의 동작을
//               할 수 있도록 구현되었기 때문에 다른 기술의 Effect
//               글 그대로 가져와서 사용할 수 있다.
//               실제 EffectEnergyDropToCreature도 EffectPoison과 같은 형태로
//               되어 있다.
//
//               EffectEnergyDropToCreature가 사용되기 위해서는
//               Effect.h 파일에 
//                EFFECT_CLASS_ENERGY_DROP_TO_CREATURE
//               가 정의되어 있어야 한다. 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ENERGY_DROP_TO_CREATURE__
#define __EFFECT_ENERGY_DROP_TO_CREATURE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEnergyDropToCreature
//////////////////////////////////////////////////////////////////////////////

class EffectEnergyDropToCreature : public Effect 
{
public:
	EffectEnergyDropToCreature(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ENERGY_DROP_TO_CREATURE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

//	int getPartyID(void) const { return m_PartyID; }
//	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }
	Turn_t getTick() const throw() { return m_Tick; }

private:
//	string  m_CasterName;
//	int     m_PartyID;
	ObjectID_t	m_UserObjectID;
	Level_t		m_Level;
	HP_t		m_Point;
	Turn_t		m_Tick;
};

#endif // __EFFECT_STORM__
