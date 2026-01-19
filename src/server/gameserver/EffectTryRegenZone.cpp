#include "EffectTryRegenZone.h"

#include "Creature.h"
#include "GCAddEffect.h"
#include "GCRemoveEffect.h"
#include "MonsterCorpse.h"
#include "Zone.h"

EffectTryRegenZone::EffectTryRegenZone(MonsterCorpse* pTower) {
    setTarget(pTower);
}

void EffectTryRegenZone::affect()

{
    __BEGIN_TRY

    MonsterCorpse* pTower = dynamic_cast<MonsterCorpse*>(m_pTarget);
    Assert(pTower != NULL);

    GCRemoveEffect gcRemoveEffect;
    gcRemoveEffect.setObjectID(pTower->getObjectID());
    gcRemoveEffect.addEffectList(getSendEffectClass());

    pTower->getZone()->broadcastPacket(pTower->getX(), pTower->getY(), &gcRemoveEffect);

    ++m_Progress;

    if (m_Progress >= 3) {
        RegenZoneManager::getInstance()->changeRegenZoneOwner(pTower, m_OwnerRace);
        setDeadline(0);
    } else {
        GCAddEffect gcAddEffect;
        gcAddEffect.setObjectID(pTower->getObjectID());
        gcAddEffect.setEffectID(getSendEffectClass());
        gcAddEffect.setDuration(200);

        pTower->getZone()->broadcastPacket(pTower->getX(), pTower->getY(), &gcAddEffect);
        setNextTime(50);
    }

    __END_CATCH
}

void EffectTryRegenZone::unaffect()

{
    __BEGIN_TRY

    MonsterCorpse* pTower = dynamic_cast<MonsterCorpse*>(m_pTarget);
    Assert(pTower != NULL);

    GCRemoveEffect gcRemoveEffect;
    gcRemoveEffect.setObjectID(pTower->getObjectID());
    gcRemoveEffect.addEffectList(getSendEffectClass());

    pTower->getZone()->broadcastPacket(pTower->getX(), pTower->getY(), &gcRemoveEffect);

    pTower->removeFlag(getEffectClass());

    __END_CATCH
}
