//////////////////////////////////////////////////////////////////////////////
// Filename    : CastleSymbol.cpp
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "CastleSymbol.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
CastleSymbolInfoManager* g_pCastleSymbolInfoManager = NULL;

ItemID_t CastleSymbol::m_ItemIDRegistry = 0;
Mutex    CastleSymbol::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
CastleSymbol::CastleSymbol()
	throw()
: m_ItemType(0), m_Durability(0)
{
	m_EnchantLevel = 0;
}

CastleSymbol::CastleSymbol(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
: m_ItemType(itemType), m_Durability(0)
{
	try {
		m_EnchantLevel = 0;

		m_Durability = computeMaxDurability(this);

		if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
		{
			filelog("itembug.log", "CastleSymbol::CastleSymbol() : Invalid item type or option type");
			throw ("CastleSymbol::CastleSymbol() : Invalid item type or optionType");
		}
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		Assert(false);
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void CastleSymbol::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	if (itemID==0)
	{
		__ENTER_CRITICAL_SECTION(m_Mutex)

		m_ItemIDRegistry += g_pItemInfoManager->getItemIDSuccessor();
		m_ItemID = m_ItemIDRegistry;

		__LEAVE_CRITICAL_SECTION(m_Mutex)
	}
	else
	{
		m_ItemID = itemID;
	}
	
	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "INSERT INTO CastleSymbolObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, Durability )"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", " << m_Durability << ")";

		pStmt->executeQuery(sql.toString());
		filelog( "WarLog.txt", "%s", sql.toString().c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CastleSymbol::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	char query[255];

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		sprintf( query, "UPDATE CastleSymbolObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);
		pStmt->executeQuery( query );
		filelog( "WarLog.txt", "%s", query );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CastleSymbol::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE CastleSymbolObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)m_OptionType
			<< ",Durability = " << m_Durability
			<< ",EnchantLevel = " <<(int)m_EnchantLevel
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE CastleSymbolObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Durability=%d, EnchantLevel=%d WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Durability, (int)m_EnchantLevel, m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CastleSymbol::toString() const 
	throw()
{
	StringStream msg;

	msg << "CastleSymbol("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)m_ItemType
		<< ",Durability:"   <<(int)m_Durability
		<< ",EnchantLevel:" <<(int)m_EnchantLevel
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t CastleSymbol::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pCastleSymbolInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t CastleSymbol::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pCastleSymbolInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t CastleSymbol::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pCastleSymbolInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t CastleSymbol::getDefenseBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pCastleSymbolInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t CastleSymbol::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pCastleSymbolInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CastleSymbolInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "CastleSymbolInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",Durability:" << m_Durability
		<< ",DefenseBonus:" << m_DefenseBonus
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void CastleSymbolInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM CastleSymbolInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel FROM CastleSymbolInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			CastleSymbolInfo* pCastleSymbolInfo = new CastleSymbolInfo();

			pCastleSymbolInfo->setItemType(pResult->getInt(++i));
			pCastleSymbolInfo->setName(pResult->getString(++i));
			pCastleSymbolInfo->setEName(pResult->getString(++i));
			pCastleSymbolInfo->setPrice(pResult->getInt(++i));
			pCastleSymbolInfo->setVolumeType(pResult->getInt(++i));
			pCastleSymbolInfo->setWeight(pResult->getInt(++i));
			pCastleSymbolInfo->setRatio(pResult->getInt(++i));
			pCastleSymbolInfo->setDurability(pResult->getInt(++i));
			pCastleSymbolInfo->setDefenseBonus(pResult->getInt(++i));
			pCastleSymbolInfo->setProtectionBonus(pResult->getInt(++i));
			pCastleSymbolInfo->setReqAbility(pResult->getString(++i));
			pCastleSymbolInfo->setItemLevel(pResult->getInt(++i));

			addItemInfo(pCastleSymbolInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void CastleSymbolLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, "
			<< " OptionType, Durability, EnchantLevel FROM CastleSymbolObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// CastleSymbol load할게 있다는것은..
		// 현재로서는 이전에 서버다운이 되었다는 의미이다.
		// 그래서, 지운다. by sigi
		pStmt->executeQuery( 
				"DELETE FROM CastleSymbolObject WHERE OwnerID = '%s'", 
				pCreature->getName().c_str() );

		/*
		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, EnchantLevel FROM CastleSymbolObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			uint i = 0;

			CastleSymbol* pCastleSymbol = new CastleSymbol();

			pCastleSymbol->setItemID(pResult->getDWORD(++i));
			pCastleSymbol->setObjectID(pResult->getDWORD(++i));
			pCastleSymbol->setItemType(pResult->getDWORD(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getDWORD(++i);
			BYTE x = pResult->getBYTE(++i);
			BYTE y = pResult->getBYTE(++i);

			pCastleSymbol->setOptionType(pResult->getInt(++i));
			pCastleSymbol->setDurability(pResult->getInt(++i));
			pCastleSymbol->setEnchantLevel(pResult->getInt(++i));

			Inventory*  pInventory      = NULL;
			Slayer*     pSlayer         = NULL;
			Vampire*    pVampire        = NULL;
			Motorcycle* pMotorcycle     = NULL;
			Inventory*  pMotorInventory = NULL;
			//Item*       pItem           = NULL;
			Stash*      pStash          = NULL;
			//Belt*       pBelt           = NULL;
			//Inventory*  pBeltInventory  = NULL;

			if (pCreature->isSlayer())
			{
				pSlayer     = dynamic_cast<Slayer*>(pCreature);
				pInventory  = pSlayer->getInventory();
				pStash      = pSlayer->getStash();
				pMotorcycle = pSlayer->getMotorcycle();

				if (pMotorcycle) pMotorInventory = pMotorcycle->getInventory();
			}
			else if (pCreature->isVampire()) 
			{
				pVampire   = dynamic_cast<Vampire*>(pCreature);
				pInventory = pVampire->getInventory();
				pStash     = pVampire->getStash();
			}
			else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

			switch(storage)
			{
				case STORAGE_INVENTORY:
					if (pInventory->canAddingEx(x, y, pCastleSymbol))
					{
						pInventory->addItemEx(x, y, pCastleSymbol);
					}
					else
					{
						processItemBugEx(pCreature, pCastleSymbol);
					}
					break;

				case STORAGE_GEAR:
					if (pCreature->isSlayer())
					{
						if (!pSlayer->isWear((Slayer::WearPart)x))
						{
							pSlayer->wearItem((Slayer::WearPart)x, pCastleSymbol);
						}
						else
						{
							processItemBugEx(pCreature, pCastleSymbol);
						}
					}
					else if (pCreature->isVampire())
					{
						processItemBugEx(pCreature, pCastleSymbol);
					}
					break;

				case STORAGE_BELT :
					processItemBugEx(pCreature, pCastleSymbol);
					break;

				case STORAGE_EXTRASLOT :
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pCastleSymbol);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pCastleSymbol);
					break;

				case STORAGE_MOTORCYCLE:
					processItemBugEx(pCreature, pCastleSymbol);
					break;

				case STORAGE_STASH:
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pCastleSymbol);
					}
					else pStash->insert(x, y, pCastleSymbol);
					break;

				case STORAGE_GARBAGE:
					processItemBug(pCreature, pCastleSymbol);
					break;

				default :
					SAFE_DELETE(pStmt);	// by sigi
					throw Error("invalid storage or OwnerID must be NULL");
			}
		}
		*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to zone
//--------------------------------------------------------------------------------
void CastleSymbolLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " Durability, EnchantLevel FROM CastleSymbolObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			CastleSymbol* pCastleSymbol = new CastleSymbol();

			pCastleSymbol->setItemID(pResult->getInt(++i));
			pCastleSymbol->setObjectID(pResult->getInt(++i));
			pCastleSymbol->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pCastleSymbol->setDurability(pResult->getInt(++i));
			pCastleSymbol->setEnchantLevel(pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pCastleSymbol);
					}
					break;

				case STORAGE_STASH :
				case STORAGE_CORPSE :
					throw UnsupportedError("상자 및 시체안의 아이템의 저장은 아직 지원되지 않습니다.");

				default :
					throw Error("Storage must be STORAGE_ZONE");
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to inventory
//--------------------------------------------------------------------------------
void CastleSymbolLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

CastleSymbolLoader* g_pCastleSymbolLoader = NULL;
