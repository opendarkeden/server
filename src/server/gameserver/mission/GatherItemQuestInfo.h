#ifndef __GATHER_ITEM_QUEST_INFO_H__
#define __GATHER_ITEM_QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"

#include "Item.h"
#include "GatherItemQuestStatus.h"

//////////////////////////////////////////////////////////////////////////////
// class GatherItemQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class GatherItemQuestInfo : public QuestInfo
{
public:
	GatherItemQuestInfo(QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, Item::ItemClass itemClass, ItemType_t itemType, int num)
		: QuestInfo( questID, race, maxGrade, minGrade, timeLimitSec, rClass, QUEST_CLASS_GATHER_ITEM ), m_TargetItemClass(itemClass), m_TargetItemType(itemType), m_TargetNum(num)
	{
	}

	virtual ~GatherItemQuestInfo() { }

public:
	bool			isTargetItem( Item* pItem ) { Assert( pItem != NULL ); return m_TargetItemClass==pItem->getItemClass() && m_TargetItemType==pItem->getItemType(); }
	GatherItemQuestStatus*	makeQuestStatus( PlayerCreature* pPC ) const throw(Error);

private:
	Item::ItemClass	m_TargetItemClass;
	ItemType_t		m_TargetItemType;
	int				m_TargetNum;
};

#endif// __GATHER_ITEM_QUEST_INFO_H__
