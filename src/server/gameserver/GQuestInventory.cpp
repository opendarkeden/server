#include "GQuestInventory.h"
#include "DB.h"

void GQuestInventory::load(const string& ownerName) throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT ItemType FROM GQuestItemObject WHERE OwnerID='%s'", ownerName.c_str() );

		while ( pResult->next() )
		{
			getItems().push_back( pResult->getInt(1) );
		}
	}
	END_DB(pStmt)

	__END_CATCH
}

void GQuestInventory::removeOne(const string& ownerName, ItemType_t item)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM GQuestItemObject WHERE OwnerID='%s' AND ItemType=%u LIMIT 1", ownerName.c_str(), item );
	}
	END_DB(pStmt)

	__END_CATCH
}

void GQuestInventory::addOne(ItemType_t item)
{
	getItems().push_back(item);
}

void GQuestInventory::saveOne(const string& ownerName, ItemType_t item)
{
	addOne(item);

	Statement* pStmt = NULL;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO GQuestItemObject(ItemType, OwnerID) VALUES (%u, '%s')",
				item, ownerName.c_str());
		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)
}

