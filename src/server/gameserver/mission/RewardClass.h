//////////////////////////////////////////////////////////////////////////////
// Filename    : RewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __REWARD_CLASS_H__
#define __REWARD_CLASS_H__

#include "Types.h"
#include "Exception.h"

#include "GCNPCResponse.h"

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
	virtual ~RewardClass() ;

public:
	RewardClass_t	getRewardClass() const { return m_RewardClass; }

	virtual void	addRewardInfo( RewardInfo* pRewardInfo ) ;
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) const ;
	virtual QuestMessage	canGiveReward( PlayerCreature* pPC ) const ;

	virtual RewardInfo*		selectReward( PlayerCreature* pPC ) const  = 0;
	virtual string	toString() const ;

	virtual bool	anotherQuestReward() const { return false; }

private:
	RewardClass_t	m_RewardClass;

protected:
	vector<RewardInfo*>	m_RewardInfos;
};

#endif
