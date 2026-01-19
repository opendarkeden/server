#ifndef __EFFECT_REGEN_ZONE_H__
#define __EFFECT_REGEN_ZONE_H__

#include "Effect.h"
#include "Exception.h"
#include "RegenZoneManager.h"
#include "Types.h"

class MonsterCorpse;

class EffectRegenZone : public Effect {
public:
    EffectRegenZone(MonsterCorpse* pTower);

    EffectClass getEffectClass() const {
        return Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE;
    }
    EffectClass getSendEffectClass() const {
        return (EffectClass)(getEffectClass() + m_OwnerRace);
    }
    void setOwner(RegenZoneInfo::RegenZoneIndex Owner) {
        m_OwnerRace = Owner;
    }

    void unaffect();

    string toString() const {
        return "EffectRegenZone";
    }

private:
    RegenZoneInfo::RegenZoneIndex m_OwnerRace;
};

#endif
