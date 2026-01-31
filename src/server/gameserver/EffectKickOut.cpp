#include "EffectKickOut.h"

#include <cstdio>

#include "GCSystemMessage.h"
#include "PCManager.h"
#include "Zone.h"

void EffectKickOut::affect() {
    // 1분에 한번
    setNextTime(600);
    m_MinutesCount--;

    char msg[200];
    sprintf(msg, "잼방땍珂쇌뻘假苟%d롸.", m_MinutesCount);
    GCSystemMessage gcSM;
    gcSM.setMessage(msg);
    m_pZone->broadcastPacket(&gcSM);
}

void EffectKickOut::unaffect() {
    __BEGIN_TRY

    GCSystemMessage gcSM;
    gcSM.setMessage("綠법방땍珂쇌. 10취빈盧땡돕릿삶뒈듐.");
    m_pZone->broadcastPacket(&gcSM);

    if (m_pZone != NULL)
        m_pZone->getPCManager()->transportAllCreatures(0xffff);

    __END_CATCH
}
