
#include "SlayerWeaponRewardClass.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "Ousters.h"
#include "ItemRewardInfo.h"
#include "ItemUtil.h"

RewardInfo*	SlayerWeaponRewardClass::selectReward( PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	Assert( pPC != NULL );
//	Assert( pPC->isSlayer() );

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		vector<RewardInfo*>::const_iterator itr = m_RewardInfos.begin();
		vector<RewardInfo*>::const_iterator endItr = m_RewardInfos.end();

		for (; itr != endItr; ++itr )
		{
			ItemRewardInfo* pItemRI = dynamic_cast<ItemRewardInfo*>(*itr);
			Assert( pItemRI != NULL );

			Item::ItemClass iClass = pItemRI->getItemClass();
			SkillDomainType_t domain = pSlayer->getHighestSkillDomain();

			if ( suitableItemClass( iClass, domain ) && pItemRI->canGiveReward( pPC ) )
			{
			//	QuestMessage result = pItemRI->giveReward(pPC);
			//	if ( result == COMPLETE_SUCCESS ) return result;
				return pItemRI;
			}
		}
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		vector<RewardInfo*>::const_iterator itr = m_RewardInfos.begin();
		vector<RewardInfo*>::const_iterator endItr = m_RewardInfos.end();
		Item::ItemClass targetItemClass;

		vector<RewardInfo*> candidates;
		candidates.clear();

		if ( pOusters->getSTR( ATTR_BASIC ) > pOusters->getINT( ATTR_BASIC ) )
		{
			targetItemClass = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
		}
		else
		{
			targetItemClass = Item::ITEM_CLASS_OUSTERS_WRISTLET;
		}

		for (; itr != endItr; ++itr )
		{
			ItemRewardInfo* pItemRI = dynamic_cast<ItemRewardInfo*>(*itr);
			Assert( pItemRI != NULL );

			Item::ItemClass iClass = pItemRI->getItemClass();

			if ( iClass == targetItemClass && pItemRI->canGiveReward( pPC ) )
			{
//				return pItemRI;
				candidates.push_back( pItemRI );
			}
		}

		if ( !candidates.empty() )
		{
			return candidates[rand()%candidates.size()];
		}
	}

	return NULL;
	
	__END_CATCH
}

QuestMessage SlayerWeaponRewardClass::giveReward( PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	RewardInfo* pRI = selectReward( pPC );
	if ( pRI == NULL ) return COMPLETE_FAIL_NO_INVENTORY_SPACE;

	return pRI->giveReward(pPC);

	__END_CATCH
}

string SlayerWeaponRewardClass::toString() const throw()
{
	return "SlayerWeaponRewardClass() : \n" + RewardClass::toString();
}
