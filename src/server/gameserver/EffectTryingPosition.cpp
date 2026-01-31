#include "EffectTryingPosition.h"

#include "EffectTryRegenZone.h"
#include "EffectTrying.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCDeleteEffectFromTile.h"
#include "GCRemoveEffect.h"
#include "MonsterCorpse.h"
#include "PlayerCreature.h"
#include "RegenZoneManager.h"
#include "Slayer.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "skill/EffectFadeOut.h"
#include "war/WarSystem.h"

EffectTryingPosition::EffectTryingPosition(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, MonsterCorpse* pTower) {
    __BEGIN_TRY

    m_pZone = pZone;
    setXY(X, Y);
    m_pTower = pTower;

    m_LastEffect = Effect::EFFECT_CLASS_TRYING_POSITION;

    __END_CATCH
}

void EffectTryingPosition::affect(Creature* pCreature) {
    __BEGIN_TRY

    if (!pCreature->isPC())
        return;
    if (!g_pWarSystem->hasActiveRaceWar())
        return;
    if (pCreature->getMoveMode() != Creature::MOVE_MODE_WALKING)
        return;

    if (pCreature->isSlayer()) {
        Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
        if (pSlayer != NULL && pSlayer->hasRideMotorcycle())
            return;
    }

    if (pCreature->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH))
        return;

    PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
    Assert(pPC != NULL);

    if (pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) {
        //		Effect* pEffect = pPC->findEffect( Effect::EFFECT_CLASS_SNIPING_MODE );
        //		if ( pEffect != NULL ) pEffect->setDeadline(0);
        addUnSnipingModeCreature(pPC->getZone(), pPC, true);
        // pPC->deleteEffect( Effect::EFFECT_CLASS_SNIPING_MODE );
    }

    if (pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)) {
        //		Effect* pEffect = pPC->findEffect( Effect::EFFECT_CLASS_INVISIBILITY );
        //		if ( pEffect != NULL ) pEffect->setDeadline(0);
        addVisibleCreature(pPC->getZone(), pPC, true);
        // pPC->deleteEffect( Effect::EFFECT_CLASS_INVISIBILITY );
    }

    if (pPC->isFlag(Effect::EFFECT_CLASS_FADE_OUT)) {
        EffectFadeOut* pEffect = dynamic_cast<EffectFadeOut*>(pPC->findEffect(Effect::EFFECT_CLASS_FADE_OUT));

        GCRemoveEffect gcRemoveEffect;
        gcRemoveEffect.setObjectID(pPC->getObjectID());
        gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_FADE_OUT);

        if (pEffect->isInvisibility())
            gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_INVISIBILITY);
        if (pEffect->isSniping())
            gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SNIPING_MODE);

        pPC->getZone()->broadcastPacket(pPC->getX(), pPC->getY(), &gcRemoveEffect);
        pPC->deleteEffect(Effect::EFFECT_CLASS_FADE_OUT);
    }

    if (!RegenZoneManager::getInstance()->canTryRegenZone(pPC, m_pTower))
        return;

    // 리젠존타워가 먹히는 중이라는 이펙트를 찍어준다.
    EffectTryRegenZone* pTowerEffect = new EffectTryRegenZone(m_pTower);
    Assert(pTowerEffect != NULL);

    pTowerEffect->setOwnerRace(pPC->getRace());
    pTowerEffect->setProgress(0);
    pTowerEffect->setDeadline(300);
    pTowerEffect->setNextTime(50);

    m_pTower->setFlag(pTowerEffect->getEffectClass());
    m_pTower->getEffectManager().addEffect(pTowerEffect);

    m_LastEffect = pTowerEffect->getEffectClass();

    GCAddEffect gcAddEffect;
    gcAddEffect.setObjectID(m_pTower->getObjectID());
    gcAddEffect.setEffectID(pTowerEffect->getSendEffectClass());
    gcAddEffect.setDuration(300);

    m_pZone->broadcastPacket(m_pTower->getX(), m_pTower->getY(), &gcAddEffect);

    EffectTrying* pCreatureEffect = new EffectTrying(pCreature);
    pCreatureEffect->setDeadline(200);
    pCreature->setFlag(pCreatureEffect->getEffectClass());
    pCreature->addEffect(pCreatureEffect);

    gcAddEffect.setObjectID(pCreature->getObjectID());
    gcAddEffect.setEffectID(pCreatureEffect->getSendEffectClass());
    gcAddEffect.setDuration(200);

    m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

    __END_CATCH
}

void EffectTryingPosition::unaffect(Creature* pCreature)

{
    __BEGIN_TRY

    if (m_LastEffect < EFFECT_CLASS_SLAYER_TRYING_1 || m_LastEffect > EFFECT_CLASS_OUSTERS_TRYING_3)
        return;
    Effect* pEffect = m_pTower->getEffectManager().findEffect(m_LastEffect);
    if (pEffect != NULL)
        pEffect->setDeadline(0);
    pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_TRYING);
    if (pEffect != NULL)
        pEffect->setDeadline(0);

    __END_CATCH
}

void EffectTryingPosition::unaffect() {
    __BEGIN_TRY

    m_pZone->getTile(getX(), getY()).deleteEffect(getObjectID());

    GCDeleteEffectFromTile gcDeleteEffect;
    gcDeleteEffect.setXY(getX(), getY());
    gcDeleteEffect.setObjectID(getObjectID());
    gcDeleteEffect.setEffectID(getSendEffectClass());

    m_pZone->broadcastPacket(getX(), getY(), &gcDeleteEffect);

    __END_CATCH
}

string EffectTryingPosition::toString() const {
    return "EffectTryingPosition" + m_pTower->toString();
}
