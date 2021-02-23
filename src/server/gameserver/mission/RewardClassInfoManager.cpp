
#include "RewardClassInfoManager.h"
#include "RandomRewardClass.h"
#include "SlayerWeaponRewardClass.h"
#include "ItemRewardInfo.h"
#include "DB.h"

RewardClassInfoManager::RewardClassInfoManager( NPC* pNPC )
{
	m_RewardClasses.clear();
	m_pOwnerNPC = pNPC;
}

RewardClassInfoManager::~RewardClassInfoManager()
{
	RewardClassHashMap::iterator itr = m_RewardClasses.begin();
	RewardClassHashMap::iterator endItr = m_RewardClasses.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL ) SAFE_DELETE( itr->second );
	}

	m_RewardClasses.clear();
}

QuestMessage RewardClassInfoManager::canGiveReward( RewardClass_t rClass, PlayerCreature* pPC ) const throw(Error)
{
	__BEGIN_TRY

	RewardClass* pRewardClass = getRewardClass( rClass );

	if ( pRewardClass == NULL ) return COMPLETE_FAIL_INVALID_NPC;

	return pRewardClass->canGiveReward(pPC);

	__END_CATCH
}

RewardClass* RewardClassInfoManager::getRewardClass( RewardClass_t rClass ) const throw(Error)
{
	__BEGIN_TRY

	RewardClassHashMap::const_iterator itr = m_RewardClasses.find( rClass );

	if ( itr == m_RewardClasses.end() ) return NULL;

	return itr->second;

	__END_CATCH
}

/*void RewardClassInfoManager::load( const string& name ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, IClass, IType, OptionType, TimeLimitSec FROM ItemRewardInfo");

		while (pResult->next()) 
		{
			int index = 0;

			RewardClass_t	rClass	= (RewardClass_t)		pResult->getInt( ++index );
			RewardID_t		rID		= (RewardID_t	)		pResult->getInt( ++index );
			Item::ItemClass	iClass	= (Item::ItemClass)		pResult->getInt( ++index );
			ItemType_t		iType	= (ItemType_t)			pResult->getInt( ++index );
			string			option	= 						pResult->getString( ++index );
			DWORD			time	= (DWORD)				pResult->getInt( ++index );

			if ( m_RewardClasses[ rClass ] == NULL ) m_RewardClasses[rClass] = new RandomRewardClass( rClass );

			ItemRewardInfo* pItemRI = new ItemRewardInfo( rID, rClass, iClass, iType, option, time );
			m_RewardClasses[rClass]->addRewardInfo( pItemRI );
		}

		pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, IClass, IType, OptionType, TimeLimitSec FROM SlayerWeaponRewardInfo");

		while (pResult->next())
		{
			int index = 0;

			RewardClass_t	rClass	= (RewardClass_t)		pResult->getInt( ++index );
			RewardID_t		rID		= (RewardID_t	)		pResult->getInt( ++index );
			Item::ItemClass	iClass	= (Item::ItemClass)		pResult->getInt( ++index );
			ItemType_t		iType	= (ItemType_t)			pResult->getInt( ++index );
			string			option	= 						pResult->getString( ++index );
			DWORD			time	= (DWORD)				pResult->getInt( ++index );

			if ( m_RewardClasses[ rClass ] == NULL ) m_RewardClasses[rClass] = new SlayerWeaponRewardClass( rClass );

			ItemRewardInfo* pItemRI = new ItemRewardInfo( rID, rClass, iClass, iType, option, time );
			m_RewardClasses[rClass]->addRewardInfo( pItemRI );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}*/
