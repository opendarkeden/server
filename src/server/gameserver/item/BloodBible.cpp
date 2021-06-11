//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBible.cpp
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "BloodBible.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
BloodBibleInfoManager* g_pBloodBibleInfoManager = NULL;

ItemID_t BloodBible::m_ItemIDRegistry = 0;
Mutex    BloodBible::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
BloodBible::BloodBible()
	
: m_ItemType(0), m_Durability(0)
{
	m_EnchantLevel = 0;
}

BloodBible::BloodBible(ItemType_t itemType, const list<OptionType_t>& optionType)
	
: m_ItemType(itemType), m_Durability(0)
{
	try {
		m_EnchantLevel = 0;

		m_Durability = computeMaxDurability(this);

		if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
		{
			filelog("itembug.log", "BloodBible::BloodBible() : Invalid item type or option type");
			throw ("BloodBible::BloodBible() : Invalid item type or optionType");
		}
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		Assert(false);
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void BloodBible::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		sql << "INSERT INTO BloodBibleObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, Durability)"
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
void BloodBible::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	char query[255];

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		sprintf( query, "UPDATE BloodBibleObject SET %s WHERE ItemID=%ld",
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
void BloodBible::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE BloodBibleObject SET "
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

		pStmt->executeQuery( "UPDATE BloodBibleObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Durability=%d, EnchantLevel=%d WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Durability, (int)getEnchantLevel(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string BloodBible::toString() const 
	
{
	StringStream msg;

	msg << "BloodBible("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)m_ItemType
		<< ",Durability:"   <<(int)m_Durability
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t BloodBible::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pBloodBibleInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t BloodBible::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pBloodBibleInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t BloodBible::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pBloodBibleInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t BloodBible::getDefenseBonus() const 
	
{
	__BEGIN_TRY

	return g_pBloodBibleInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t BloodBible::getProtectionBonus() const
	
{
	__BEGIN_TRY

	return g_pBloodBibleInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string BloodBibleInfo::toString() const 
	
{
	StringStream msg;

	msg << "BloodBibleInfo("
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
void BloodBibleInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM BloodBibleInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel FROM BloodBibleInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			BloodBibleInfo* pBloodBibleInfo = new BloodBibleInfo();

			pBloodBibleInfo->setItemType(pResult->getInt(++i));
			pBloodBibleInfo->setName(pResult->getString(++i));
			pBloodBibleInfo->setEName(pResult->getString(++i));
			pBloodBibleInfo->setPrice(pResult->getInt(++i));
			pBloodBibleInfo->setVolumeType(pResult->getInt(++i));
			pBloodBibleInfo->setWeight(pResult->getInt(++i));
			pBloodBibleInfo->setRatio(pResult->getInt(++i));
			pBloodBibleInfo->setDurability(pResult->getInt(++i));
			pBloodBibleInfo->setDefenseBonus(pResult->getInt(++i));
			pBloodBibleInfo->setProtectionBonus(pResult->getInt(++i));
			pBloodBibleInfo->setReqAbility(pResult->getString(++i));
			pBloodBibleInfo->setItemLevel(pResult->getInt(++i));

			addItemInfo(pBloodBibleInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void BloodBibleLoader::load(Creature* pCreature) 
	
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
			<< " OptionType, Durability, EnchantLevel FROM BloodBibleObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// BloodBible load할게 있다는것은..
		// 현재로서는 이전에 서버다운이 되었다는 의미이다.
		// 그래서, 지운다. by sigi
		pStmt->executeQuery( 
				"DELETE FROM BloodBibleObject WHERE OwnerID = '%s'", 
				pCreature->getName().c_str() );

		/*
		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, EnchantLevel FROM BloodBibleObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			uint i = 0;

			BloodBible* pBloodBible = new BloodBible();

			pBloodBible->setItemID(pResult->getDWORD(++i));
			pBloodBible->setObjectID(pResult->getDWORD(++i));
			pBloodBible->setItemType(pResult->getDWORD(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getDWORD(++i);
			BYTE x = pResult->getBYTE(++i);
			BYTE y = pResult->getBYTE(++i);

			pBloodBible->setOptionType(pResult->getInt(++i));
			pBloodBible->setDurability(pResult->getInt(++i));
			pBloodBible->setEnchantLevel(pResult->getInt(++i));

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
					if (pInventory->canAddingEx(x, y, pBloodBible))
					{
						pInventory->addItemEx(x, y, pBloodBible);
					}
					else
					{
						processItemBugEx(pCreature, pBloodBible);
					}
					break;

				case STORAGE_GEAR:
					if (pCreature->isSlayer())
					{
						if (!pSlayer->isWear((Slayer::WearPart)x))
						{
							pSlayer->wearItem((Slayer::WearPart)x, pBloodBible);
						}
						else
						{
							processItemBugEx(pCreature, pBloodBible);
						}
					}
					else if (pCreature->isVampire())
					{
						processItemBugEx(pCreature, pBloodBible);
					}
					break;

				case STORAGE_BELT :
					processItemBugEx(pCreature, pBloodBible);
					break;

				case STORAGE_EXTRASLOT :
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pBloodBible);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pBloodBible);
					break;

				case STORAGE_MOTORCYCLE:
					processItemBugEx(pCreature, pBloodBible);
					break;

				case STORAGE_STASH:
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pBloodBible);
					}
					else pStash->insert(x, y, pBloodBible);
					break;

				case STORAGE_GARBAGE:
					processItemBug(pCreature, pBloodBible);
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
void BloodBibleLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " Durability, EnchantLevel FROM BloodBibleObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			BloodBible* pBloodBible = new BloodBible();

			pBloodBible->setItemID(pResult->getInt(++i));
			pBloodBible->setObjectID(pResult->getInt(++i));
			pBloodBible->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pBloodBible->setDurability(pResult->getInt(++i));
			pBloodBible->setEnchantLevel(pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pBloodBible);
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
void BloodBibleLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

BloodBibleLoader* g_pBloodBibleLoader = NULL;
