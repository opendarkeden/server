//--------------------------------------------------------------------------------
// 
// Filename   : ItemDestroyer.cpp
// Written By : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "ItemDestroyer.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
ItemDestroyer::ItemDestroyer () 
{
}


//--------------------------------------------------------------------------------
// destroy all item whose owner is ...
//--------------------------------------------------------------------------------
void ItemDestroyer::destroyAll ( const string & ownerID ) 
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	try
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQueryString("DELETE FROM MotorcycleObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM PotionObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM WaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM HolyWaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM MagazineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM BombMaterialObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM ETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM KeyObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM RingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM BraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM NecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM CoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM TrouserObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM ShoesObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SwordObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM BladeObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM ShieldObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM CrossObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM MaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM GloveObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM HelmObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SMGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM ARObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SRObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM BombObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM MineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM BeltObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM LearningItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampireRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampireBraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampireNecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampireCoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SkullObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM MaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SerumObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampireETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM SlayerPortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM VampirePortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM EventGiftBoxObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQueryString("DELETE FROM EventStarObject WHERE OwnerID = '" + ownerID + "'");

		delete pStmt;
	}
	catch ( SQLQueryException & sqe )
	{
		delete pStmt;
		throw Error(sqe.toString());
	}

	__END_CATCH
}

ItemDestroyer * g_pItemDestroyer = NULL;
