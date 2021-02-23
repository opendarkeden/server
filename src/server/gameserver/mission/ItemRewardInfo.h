//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemRewardInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_REWARD_INFO_H__
#define __ITEM_REWARD_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include "RewardInfo.h"

#include <list>

class RewardClass;

//////////////////////////////////////////////////////////////////////////////
// class ItemRewardInfo;
//////////////////////////////////////////////////////////////////////////////

class ItemRewardInfo : public RewardInfo
{
public:
	ItemRewardInfo( RewardID_t rID, RewardClass_t rClass, Item::ItemClass iClass, ItemType_t iType, const string& option, DWORD time );
	virtual ~ItemRewardInfo();

public:
	virtual QuestMessage	canGiveReward(PlayerCreature* pPC) const throw(Error);
	virtual QuestMessage	giveReward(PlayerCreature* pPC) const throw(Error);

	Item::ItemClass	getItemClass() const { return m_IClass; }

	virtual string	toString() const throw();

public:
//	static void		loadRewardClass( RewardClass& rClass ) throw(Error);

private:
	Item::ItemClass			m_IClass;
	ItemType_t				m_IType;
	list<OptionType_t>		m_OptionType;

	DWORD					m_TimeLimit;
};

#endif
