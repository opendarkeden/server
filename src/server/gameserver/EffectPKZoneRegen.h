//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPKZoneRegen.h
// Written by  : 
// Description : PKZoneRegen에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PK_ZONE_REGEN__
#define __EFFECT_PK_ZONE_REGEN__

#include "Effect.h"

class Zone;

//////////////////////////////////////////////////////////////////////////////
// class EffectPKZoneRegen
//////////////////////////////////////////////////////////////////////////////

class EffectPKZoneRegen : public Effect 
{
public:
	EffectPKZoneRegen(Zone* pZone, ZoneCoord_t left, ZoneCoord_t top, ZoneCoord_t right, ZoneCoord_t bottom) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PK_ZONE_REGEN; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	Turn_t	getTurn() const { return m_Turn; }
	void	setTurn( Turn_t	t ) { m_Turn = t; }

	bool	isSlayer() const { return m_bSlayer; }
	void	setSlayer( bool bSlayer = true ) { m_bSlayer = bSlayer; }

	bool	isVampire() const { return m_bVampire; }
	void	setVampire( bool bVampire = true ) { m_bVampire = bVampire; }

	bool	isOusters() const { return m_bOusters; }
	void	setOusters( bool bOusters = true ) { m_bOusters = bOusters; }

	HP_t	getHP() const { return m_HP; }
	void	setHP( HP_t hp ) { m_HP = hp; }

private:
	Turn_t	m_Turn;
	VSRect	m_Rect;

	bool	m_bSlayer;
	bool	m_bVampire;
	bool	m_bOusters;

	HP_t	m_HP;
};

#endif // __EFFECT_PK_ZONE_REGEN__
