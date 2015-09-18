#include "EffectGDRLairClose.h"
#include "GDRLairManager.h"
#include "GCSystemMessage.h"
#include "ZoneGroupManager.h"
#include <cstdio>

void EffectGDRLairClose::affect() throw(Error)
{
	setNextTime(600);

	char msg[200];
	sprintf(msg, "GDR Lair Entrace closes in %d minutes.", m_MinutesCount);
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	g_pZoneGroupManager->broadcast(&gcSM);
	m_MinutesCount--;
}

void EffectGDRLairClose::unaffect() throw(Error)
{
	__BEGIN_TRY

	GDRLairManager::Instance().close();

	GCSystemMessage gcSM;
	gcSM.setMessage("GDR Lair Entrace has closed.");
	g_pZoneGroupManager->broadcast(&gcSM);

	__END_CATCH
}
