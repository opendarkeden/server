
#include "GatherItemQuestStatus.h"
#include "QuestInfoManager.h"
#include "PlayerCreature.h"
#include "Inventory.h"

#include <map>

GCQuestStatus* GatherItemQuestStatus::makeStatusPacket() const
{
	GCQuestStatus* pPacket = new GCQuestStatus();

	pPacket->setQuestID( (WORD)getQuestID() );
	pPacket->setCurrentNum( (WORD)m_CurrentNum );
	pPacket->setRemainTime( (DWORD)max(VSDateTime::currentDateTime().secsTo( m_Deadline ), 0) );

	return pPacket;
}

/*bool GatherItemQuestStatus::got( Item* pItem ) throw(Error)
{
	__BEGIN_TRY

	bool ret = false;
	if ( m_TargetNum > m_CurrentNum && isTarget( pItem ) ){ ++m_CurrentNum; ret = true; }
	if ( m_TargetNum <= m_CurrentNum && m_State == QUEST_STARTED ){ setSuccess(); ret = true; }

	return ret;

	__END_CATCH
}
*/
bool GatherItemQuestStatus::isTarget( Item* pItem ) const throw(Error)
{
	__BEGIN_TRY

	Assert( pItem != NULL );

	return ( pItem->getItemClass() == m_TargetItemClass && ( m_TargetItemType == 999 || pItem->getItemType() == m_TargetItemType ) );

	__END_CATCH
}

bool GatherItemQuestStatus::isSuccess() const throw(Error)
{
	__BEGIN_TRY

	PlayerCreature* pOwnerPC = getOwnerPC();
	Inventory*		pInventory = pOwnerPC->getInventory();

	// 인벤토리 뒤지기 ㅎㅎㅎ
	map<ObjectID_t,Item*> ItemList;
	int height = pInventory->getHeight();
	int width  = pInventory->getWidth();

	m_CurrentNum = 0;

	for (int j=0; j<height; j++)
	{
		for (int i=0; i<width; i++)
		{
			Item* pItem = pInventory->getItem(i, j);
			if (pItem != NULL)
			{
				// 체크된 아이템의 리스트에서 현재 아이템을 찾는다.
				map<ObjectID_t,Item*>::iterator itr = ItemList.find(pItem->getObjectID());

				if (itr == ItemList.end())
				{
					i += pItem->getVolumeWidth() - 1;
					if ( isTarget( pItem ) )
					{
						++m_CurrentNum;
						if ( m_CurrentNum >= m_TargetNum ) break;
					}
				}
				ItemList[pItem->getObjectID()] = pItem;
			}
		}
		if ( m_CurrentNum >= m_TargetNum ) break;
	}

	if ( m_TargetNum <= m_CurrentNum )
	{
		if ( !QuestStatus::isSuccess() && !isRewarded() ) setSuccess();
		return true;
	}

	return false;

	__END_CATCH
}
