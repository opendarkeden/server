#include "EffectKickOut.h"
#include "Zone.h"
#include "PCManager.h"
#include "Gpackets/GCSystemMessage.h"
#include <cstdio>

void EffectKickOut::affect() 
{
	// 1盒俊 茄锅
	setNextTime( 600 );
	m_MinutesCount--;

	char msg[200];
	sprintf(msg, "离规定时间还剩下%d分.", m_MinutesCount);
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	m_pZone->broadcastPacket( &gcSM );
}

void EffectKickOut::unaffect() 
{
	__BEGIN_TRY

	GCSystemMessage gcSM;
	gcSM.setMessage("已过规定时间. 10秒后移动到复活地点.");
	m_pZone->broadcastPacket( &gcSM );

	if ( m_pZone != NULL ) m_pZone->getPCManager()->transportAllCreatures(0xffff);

	__END_CATCH
}
