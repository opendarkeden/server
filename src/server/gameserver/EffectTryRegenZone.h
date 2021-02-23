#ifndef __EFFECT_TRY_REGEN_ZONE_H__
#define __EFFECT_TRY_REGEN_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Effect.h"
#include "RegenZoneManager.h"

class Creature;
class MonsterCorpse;

class EffectTryRegenZone : public Effect
{
public:
	EffectTryRegenZone( MonsterCorpse* pTower );

	EffectClass	getEffectClass() const throw() { return (EffectClass)(Effect::EFFECT_CLASS_SLAYER_TRYING_1 + (m_OwnerRace*3)); }
	EffectClass	getSendEffectClass() const throw() { return (EffectClass)(getEffectClass() + m_Progress); }

	void affect() throw(Error);
	void unaffect() throw(Error);

	Race_t getOwnerRace() const { return m_OwnerRace; }
	void setOwnerRace( Race_t race ) { m_OwnerRace = race; }

	uint getProgress() const { return m_Progress; }
	void setProgress( uint pro ) { m_Progress = pro; }

	string toString() const throw() { return "EffectTryRegenZone"; }

private:
	Race_t	m_OwnerRace;
	uint	m_Progress;
};

#endif
