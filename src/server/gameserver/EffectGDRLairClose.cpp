#include "EffectGDRLairClose.h"
#include "GDRLairManager.h"
#include "GCSystemMessage.h"
#include "ZoneGroupManager.h"
#include <cstdio>

void EffectGDRLairClose::affect() 
{
	setNextTime( 600 );

	char msg[200];
	sprintf(msg, "%d分后,将关闭热达瑞行宫入口.", m_MinutesCount );
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	g_pZoneGroupManager->broadcast( &gcSM );
	m_MinutesCount--;
}

void EffectGDRLairClose::unaffect() 
{
	__BEGIN_TRY

	cout << "龙靛饭 饭绢 摧嚼聪促." << endl;
	GDRLairManager::Instance().close();

	GCSystemMessage gcSM;
	gcSM.setMessage("热达瑞行宫已关闭.");
	g_pZoneGroupManager->broadcast( &gcSM );

	__END_CATCH
}
