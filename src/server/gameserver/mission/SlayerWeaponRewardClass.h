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
	virtual RewardInfo*		selectReward( PlayerCreature* pPC ) const ;
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) const ;

	virtual string	toString() const ;

private:
};

#endif
