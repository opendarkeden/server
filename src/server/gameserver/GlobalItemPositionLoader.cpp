#include "GlobalItemPositionLoader.h"
#include "DB.h"
#include "InventoryItemPosition.h"
#include "MouseItemPosition.h"
#include "ZoneItemPosition.h"
#include "CorpseItemPosition.h"

GlobalItemPosition* GlobalItemPositionLoader::load( Item::ItemClass itemClass, ItemID_t itemID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	GlobalItemPosition* pRet = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT OwnerID, Storage, StorageID, X, Y, ObjectID FROM %s WHERE ItemID = %d", 
				ItemObjectTableName[ (int)itemClass ].c_str(), itemID );

		if (pResult->next()) 
		{
			int i=0;
			GlobalDBItemPosition	gip;
			gip.OwnerID 	= pResult->getString( ++i );
			gip.ItemStorage = (Storage)pResult->getInt( ++i );
			gip.StorageID 	= (StorageID_t)pResult->getInt( ++i );
			gip.X			= pResult->getInt( ++i );
			gip.Y			= pResult->getInt( ++i );
			gip.ObjectID	= pResult->getInt( ++i );

			pRet = makeGlobalItemPosition( gip );
		}
		else
		{
			pRet = NULL;
		}
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return pRet;

	__END_CATCH
}

GlobalItemPosition*	GlobalItemPositionLoader::makeGlobalItemPosition( GlobalDBItemPosition& gip )
	throw(Error)
{
	__BEGIN_TRY

	switch( gip.ItemStorage )
	{
		case STORAGE_INVENTORY:
		{
			InventoryItemPosition* pIIP = new InventoryItemPosition();
			pIIP->setOwnerName( gip.OwnerID );
			pIIP->setInventoryX( gip.X );
			pIIP->setInventoryY( gip.Y );
			return (GlobalItemPosition*)pIIP;
		}
		break;
		case STORAGE_EXTRASLOT:
		{
			MouseItemPosition* pMIP = new MouseItemPosition();
			pMIP->setOwnerName( gip.OwnerID );
			return (GlobalItemPosition*)pMIP;
		}
		break;
		case STORAGE_ZONE:
		{
			ZoneItemPosition* pZIP = new ZoneItemPosition();
			pZIP->setZoneID( gip.StorageID );
			pZIP->setZoneX( gip.X );
			pZIP->setZoneY( gip.Y );
			return (GlobalItemPosition*)pZIP;
		}
		break;
		case STORAGE_CORPSE:
		{
			CorpseItemPosition* pCIP = new CorpseItemPosition();
			pCIP->setZoneID( atoi(gip.OwnerID.c_str()) );
			pCIP->setCorpseObjectID( gip.StorageID );
			pCIP->setObjectID( gip.ObjectID );

			return (GlobalItemPosition*)pCIP;
		}
		break;

		default:
			return NULL;
		break;
	}

	__END_CATCH
}
