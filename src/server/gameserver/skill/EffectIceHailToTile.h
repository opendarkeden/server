#ifndef __EFFECT_ICE_HAIL_TO_TILE_H__
#define __EFFECT_ICE_HAIL_TO_TILE_H__

#include "EffectWithWarning.h"

class EffectIceHailToTile : public EffectWithWarning
{
public:
	EffectIceHailToTile(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) : EffectWithWarning( Effect::EFFECT_CLASS_ICICLE_DROP_SIGN, Effect::EFFECT_CLASS_ICE_HAIL, pZone, x, y ) { }
	void affect() throw(Error);

	string toString() const throw() { return "EffectIceHailToTile"; }

	Damage_t	getDamage() const { return m_Damage; }
	void		setDamage(Damage_t damage) { m_Damage = damage; }

private:
	Damage_t	m_Damage;
};

#endif
