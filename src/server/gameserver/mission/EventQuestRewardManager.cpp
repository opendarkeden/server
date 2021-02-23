
#include "EventQuestRewardManager.h"
#include "DB.h"
#include "Item.h"
#include "RandomRewardClass.h"
#include "SlayerWeaponRewardClass.h"
#include "QuestAdvanceRewardInfo.h"
#include "ItemRewardInfo.h"

void EventQuestRewardManager::load(const string& name) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		// 이거 안쓰는거다.
		
/*		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult;

		pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, QuestLevel FROM EventQuestRewardInfo WHERE NPC='%s'", name.c_str());
		
		while( pResult->next() )
		{
			int index = 0;

			RewardClass_t	rClass	= (RewardClass_t)		pResult->getInt( ++index );
			RewardID_t		rID		= (RewardID_t	)		pResult->getInt( ++index );
			int				qLevel	= (int)					pResult->getInt( ++index );

			if ( m_RewardClasses[rClass] != NULL )
			{
				cout << "EventQuestRewardManager : 왜 똑같은게 두개나 들어있어" << (uint)rClass << endl;
				Assert( false );
			}

			m_RewardClasses[rClass] = new RandomRewardClass( rClass );
			QuestAdvanceRewardInfo* pRI = new QuestAdvanceRewardInfo( rID, rClass, qLevel, qLevel+1 );
			m_RewardClasses[rClass]->addRewardInfo( pRI );
		}*/

		/*pResult = pStmt->executeQuery("SELECT RewardClass, RewardID, IClass, IType, OptionType, TimeLimitSec FROM ItemRewardInfo WHERE NPC='%s'", name.c_str());

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
				cout << "EventQuestRewardManager : 이놈이 줄 수 없는 이벤트퀘스트자나" << (uint)rClass << endl;
				Assert( false );
			//	m_RewardClasses[rClass] = new RandomRewardClass( rClass );
			//	cout << "NPC : " << name << ", RewardClass : " << (uint)rClass << endl;
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
				cout << "EventQuestRewardManager : 이놈이 줄 수 없는 이벤트퀘스트자나" << endl;
				Assert( false );
			}

			ItemRewardInfo* pItemRI = new ItemRewardInfo( rID, rClass, iClass, iType, option, time );
			m_RewardClasses[rClass]->addRewardInfo( pItemRI );
		}*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}
