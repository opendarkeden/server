#include "EffectKickOut.h"
#include "Zone.h"
#include "PCManager.h"
#include "GCSystemMessage.h"
#include <cstdio>

void EffectKickOut::affect() throw(Error)
{
	// 1분에 한번
	setNextTime(600);
	m_MinutesCount--;

	char msg[200];
	sprintf(msg, "Timeout in %d minutes.", m_MinutesCount);
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	m_pZone->broadcastPacket(&gcSM);
}

void EffectKickOut::unaffect() throw(Error)
{
	__BEGIN_TRY

	GCSystemMessage gcSM;
	gcSM.setMessage("Limit time was reached, teleporting to ressurection point in 10 seconds.");
	m_pZone->broadcastPacket(&gcSM);

	if (m_pZone != NULL ) m_pZone->getPCManager()->transportAllCreatures(0xffff);

	__END_CATCH
}
