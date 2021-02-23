
#include "GatherItemQuestStatus.h"
#include "GatherItemQuestInfo.h"
#include "PlayerCreature.h"

GatherItemQuestStatus* GatherItemQuestInfo::makeQuestStatus( PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	return new GatherItemQuestStatus( getQuestID(), VSDateTime::currentDateTime().addSecs(getTimeLimit()), m_TargetItemClass, m_TargetItemType, m_TargetNum );

	__END_CATCH
}
