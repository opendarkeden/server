#include "EffectGDRLairClose.h"

#include <cstdio>

#include "GCSystemMessage.h"
#include "GDRLairManager.h"
#include "ZoneGroupManager.h"

void EffectGDRLairClose::affect() {
    setNextTime(600);

    char msg[200];
    sprintf(msg, "%d롸빈,쉥밑균훑댐흩契묵흙왯.", m_MinutesCount);
    GCSystemMessage gcSM;
    gcSM.setMessage(msg);
    g_pZoneGroupManager->broadcast(&gcSM);
    m_MinutesCount--;
}

void EffectGDRLairClose::unaffect() {
    __BEGIN_TRY

    cout << "질드레 레어 닫습니다." << endl;
    GDRLairManager::Instance().close();

    GCSystemMessage gcSM;
    gcSM.setMessage("훑댐흩契묵綠밑균.");
    g_pZoneGroupManager->broadcast(&gcSM);

    __END_CATCH
}
