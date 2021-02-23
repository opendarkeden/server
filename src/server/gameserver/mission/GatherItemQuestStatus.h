#ifndef __GATHER_ITEM_QUEST_STATUS_H__
#define __GATHER_ITEM_QUEST_STATUS_H__

#include "QuestStatus.h"
#include "Item.h"

#include "Gpackets/GCQuestStatus.h"

class GatherItemQuestStatus : public QuestStatus
{
public:
	GatherItemQuestStatus( QuestID_t qID, const VSDateTime& deadline, Item::ItemClass itemClass, ItemType_t itemType, int num )
		: QuestStatus( qID, deadline, QUEST_CLASS_GATHER_ITEM ), m_TargetItemClass( itemClass ), m_TargetItemType( itemType ), m_TargetNum(num), m_CurrentNum(0)
	{
	}
	~GatherItemQuestStatus() { }

//	bool			got( Item* pItem ) throw(Error);
	bool			isTarget( Item* pItem ) const throw(Error);
	void			reset() { m_CurrentNum = 0; }

	bool			isSuccess() const throw(Error);
	GCQuestStatus*	makeStatusPacket() const;

private:
	Item::ItemClass	m_TargetItemClass;
	ItemType_t		m_TargetItemType;
	
	int				m_TargetNum;
	mutable int		m_CurrentNum;
};

#endif// __GATHER_ITEM_QUEST_STATUS_H__

