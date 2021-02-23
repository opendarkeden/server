//////////////////////////////////////////////////////////////////////////////
// Filename    : UniqueItemManager.cpp
// Written By  : suigui
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "UniqueItemManager.h"
#include "ItemInfoManager.h"
#include "Item.h"
#include "DB.h"


UniqueItemManager* g_pUniqueItemManager = NULL;

//----------------------------------------------------------------------
// init
//----------------------------------------------------------------------
void UniqueItemManager::init() 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// DB에서 현재의 값을 읽어온다.
		Result* pResult = pStmt->executeQuery(
			"SELECT ItemClass, ItemType FROM UniqueItemInfo");

		// 지정된 itemClas, itemType을 Unique Item으로 설정한다.
		while (pResult->next())
		{
			Item::ItemClass itemClass = (Item::ItemClass)pResult->getInt(1);
			int itemType  = pResult->getInt(2);

			ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( itemClass, itemType );
			Assert(pItemInfo!=NULL);

			pItemInfo->setUnique();
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
	__END_DEBUG
}

//----------------------------------------------------------------------
// is Possible Create
//----------------------------------------------------------------------
bool UniqueItemManager::isPossibleCreate(Item::ItemClass itemClass, ItemType_t itemType) 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// DB에서 현재의 값을 읽어온다.
		Result* pResult = pStmt->executeQuery(
			"SELECT LimitNumber, CurrentNumber FROM UniqueItemInfo WHERE ItemClass=%d AND ItemType=%d",
			(int)itemClass, (int)itemType);

		if (pResult->next())
		{
			int limitNumber  = pResult->getInt(1);
			int currentNumber  = pResult->getInt(2);

			return limitNumber==0 || currentNumber<limitNumber;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
	__END_DEBUG

	return false;
}

//----------------------------------------------------------------------
// createItem
//----------------------------------------------------------------------
// DB에서 개수 증가
//----------------------------------------------------------------------
void UniqueItemManager::createItem(Item::ItemClass itemClass, ItemType_t itemType) 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// DB에서 현재의 값을 읽어온다.
		pStmt->executeQuery(
			"UPDATE UniqueItemInfo SET CurrentNumber=CurrentNumber+1 WHERE ItemClass=%d AND ItemType=%d",
			(int)itemClass, (int)itemType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
	__END_DEBUG
}

//----------------------------------------------------------------------
// deleteItem
//----------------------------------------------------------------------
// DB에서 개수 증가
//----------------------------------------------------------------------
void UniqueItemManager::deleteItem(Item::ItemClass itemClass, ItemType_t itemType) 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// DB에서 현재의 값을 읽어온다.
		pStmt->executeQuery(
			"UPDATE UniqueItemInfo SET CurrentNumber=CurrentNumber-1 WHERE ItemClass=%d AND ItemType=%d",
			(int)itemClass, (int)itemType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
	__END_DEBUG
}

