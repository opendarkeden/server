
#include "SimpleQuestRewardManager.h"
#include "DB.h"
#include "Item.h"
#include "RandomRewardClass.h"
#include "SlayerWeaponRewardClass.h"
#include "ItemRewardInfo.h"

void SimpleQuestRewardManager::load(const string& name) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, IClass, IType, OptionType, TimeLimitSec FROM ItemRewardInfo WHERE NPC='%s'", name.c_str());

		while (pResult->next()) 
		{
			int index = 0;

			RewardClass_t	rClass	= (RewardClass_t)		pResult->getInt( ++index );
			RewardID_t		rID		= (RewardID_t	)		pResult->getInt( ++index );
			Item::ItemClass	iClass	= (Item::ItemClass)		pResult->getInt( ++index );
			ItemType_t		iType	= (ItemType_t)			pResult->getInt( ++index );
			string			option	= 						pResult->getString( ++index );
			DWORD			time	= (DWORD)				pResult->getInt( ++index );

			if ( m_RewardClasses[ rClass ] == NULL ){
				m_RewardClasses[rClass] = new RandomRewardClass( rClass );
				//cout << "NPC : " << name << ", RewardClass : " << (uint)rClass << endl;
			}

			ItemRewardInfo* pItemRI = new ItemRewardInfo( rID, rClass, iClass, iType, option, time );
			m_RewardClasses[rClass]->addRewardInfo( pItemRI );
		}

		pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, IClass, IType, OptionType, TimeLimitSec FROM SlayerWeaponRewardInfo WHERE NPC='%s'", name.c_str());

		while (pResult->next())
		{
			int index = 0;

			RewardClass_t	rClass	= (RewardClass_t)		pResult->getInt( ++index );
			RewardID_t		rID		= (RewardID_t	)		pResult->getInt( ++index );
			Item::ItemClass	iClass	= (Item::ItemClass)		pResult->getInt( ++index );
			ItemType_t		iType	= (ItemType_t)			pResult->getInt( ++index );
			string			option	= 						pResult->getString( ++index );
			DWORD			time	= (DWORD)				pResult->getInt( ++index );

			if ( m_RewardClasses[ rClass ] == NULL ){
				m_RewardClasses[rClass] = new SlayerWeaponRewardClass( rClass );
				//cout << "NPC : " << name << ", RewardClass : " << (uint)rClass << endl;
			}

			ItemRewardInfo* pItemRI = new ItemRewardInfo( rID, rClass, iClass, iType, option, time );
			m_RewardClasses[rClass]->addRewardInfo( pItemRI );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}
