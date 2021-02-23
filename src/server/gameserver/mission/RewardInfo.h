//////////////////////////////////////////////////////////////////////////////
// Filename    : RewardInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __REWARD_INFO_H__
#define __REWARD_INFO_H__

#include "Types.h"
#include "Exception.h"

#include "Gpackets/GCNPCResponse.h"

#include <vector>

class PlayerCreature;

//////////////////////////////////////////////////////////////////////////////
// class RewardInfo;
//////////////////////////////////////////////////////////////////////////////

class RewardInfo 
{
public:
	RewardInfo( RewardID_t rID, RewardClass_t rClass );
	virtual ~RewardInfo();

public:
	virtual QuestMessage	canGiveReward(PlayerCreature* pPC) const throw(Error) = 0;
	virtual QuestMessage	giveReward(PlayerCreature* pPC) const throw(Error) = 0;

	virtual string	toString() const throw();

	virtual bool	isAnotherQuest() const { return false; }

private:
	RewardID_t		m_RewardID;
	RewardClass_t	m_RewardClass;
};

#endif
