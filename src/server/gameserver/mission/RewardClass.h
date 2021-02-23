//////////////////////////////////////////////////////////////////////////////
// Filename    : RewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __REWARD_CLASS_H__
#define __REWARD_CLASS_H__

#include "Types.h"
#include "Exception.h"

#include "Gpackets/GCNPCResponse.h"

#include <vector>

class RewardInfo;
class PlayerCreature;

//////////////////////////////////////////////////////////////////////////////
// class RewardClass;
//////////////////////////////////////////////////////////////////////////////

class RewardClass 
{
public:
	RewardClass( RewardClass_t rClass );
	virtual ~RewardClass() throw (Error);

public:
	RewardClass_t	getRewardClass() const { return m_RewardClass; }

	virtual void	addRewardInfo( RewardInfo* pRewardInfo ) throw(Error);
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) const throw(Error);
	virtual QuestMessage	canGiveReward( PlayerCreature* pPC ) const throw(Error);

	virtual RewardInfo*		selectReward( PlayerCreature* pPC ) const throw(Error) = 0;
	virtual string	toString() const throw();

	virtual bool	anotherQuestReward() const { return false; }

private:
	RewardClass_t	m_RewardClass;

protected:
	vector<RewardInfo*>	m_RewardInfos;
};

#endif
