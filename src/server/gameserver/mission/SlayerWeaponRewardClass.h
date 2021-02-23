//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerWeaponRewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_WEAPON_REWARD_CLASS_H__
#define __SLAYER_WEAPON_REWARD_CLASS_H__

#include "RewardClass.h"

//////////////////////////////////////////////////////////////////////////////
// class SlayerWeaponRewardClass;
//////////////////////////////////////////////////////////////////////////////

class SlayerWeaponRewardClass : public RewardClass
{
public:
	SlayerWeaponRewardClass( RewardClass_t rClass ) : RewardClass(rClass) { }

public:
	virtual RewardInfo*		selectReward( PlayerCreature* pPC ) const throw(Error);
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) const throw(Error);

	virtual string	toString() const throw();

private:
};

#endif
