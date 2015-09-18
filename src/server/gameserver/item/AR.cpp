//////////////////////////////////////////////////////////////////////////////
// Filename    : AR.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "AR.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "SubInventory.h"

// global variable declaration
ARInfoManager* g_pARInfoManager = NULL;

ItemID_t AR::m_ItemIDRegistry = 0;
Mutex    AR::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
AR::AR()
	throw()
{
	setItemType(0);
	setDurability(0);
	setEnchantLevel(0);
	setBulletCount(0);
	setBonusDamage(0);
	setSilver(0);
}

AR::AR(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: Gun(itemType, optionType)
{
	setItemType(itemType);
	setOptionType(optionType);
	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "AR::AR() : Invalid item type or option type");
		throw("AR::AR() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
AR::~AR()
	throw()
{
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void AR::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		/*
		StringStream sql;

		sql << "INSERT INTO ARObject "
			<< "(ItemID, ObjectID, ItemType, OwnerID ," 
			<< " Storage, StorageID ,"
			<< " X, Y, OptionType ," 
			<< " Durability, BulletCount) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', "
			<<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", " <<(int)m_OptionType << ", "
			<< m_Durability << ", " <<(int)m_BulletCount << ")";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream 없애기. by sigi. 2002.5.13
		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("INSERT INTO ARObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability, BulletCount, Grade, ItemFlag) VALUES(%ld, %ld, %d, '%s', %d, %ld, %d, %d, '%s', %d, %d, %d, %d)",
							m_ItemID, m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), (int)getBulletCount(), (int)getGrade(), (int)m_CreateType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void AR::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE ARObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void AR::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE ARObject SET "
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
			<< ",BulletCount = " <<(int)m_BulletCount
			<< ",Silver = " <<(int)m_Silver
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("UPDATE ARObject SET ObjectID = %ld, ItemType = %d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, EnchantLevel=%d, BulletCount=%d, Silver=%d, Grade=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), (int)getEnchantLevel(), (int)getBulletCount(), (int)getSilver(), (int)getGrade(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void AR::saveBullet() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE ARObject SET BulletCount = %d WHERE ItemID = %d",
							getBulletCount(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void AR::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);
	result.setItemNum(getBulletCount());
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string AR::toString() const 
	throw()
{
	StringStream msg;
	msg << "AR("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",Durability:"   <<(int)getDurability()
		<< ",BulletCount:"  <<(int)getBulletCount()
		<< ",Silver:"       <<(int)getSilver()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";
	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
/*VolumeWidth_t AR::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t AR::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t AR::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's minDamage
//--------------------------------------------------------------------------------
Damage_t AR::getMinDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getMinDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's maxDamage
//--------------------------------------------------------------------------------
Damage_t AR::getMaxDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getMaxDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's range
//--------------------------------------------------------------------------------
Range_t AR::getRange() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getRange();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's ToHit Bonus
//--------------------------------------------------------------------------------
ToHit_t AR::getToHitBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getToHitBonus();

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int AR::getCriticalBonus(void) const
	throw()
{
	__BEGIN_TRY

	return g_pARInfoManager->getItemInfo(m_ItemType)->getCriticalBonus();

	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string ARInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "ARInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",Durability:" << m_Durability
		<< ",minDamage:" << m_MinDamage
		<< ",maxDamage:" << m_MaxDamage
		<< ",ToHitBonus:" << m_ToHitBonus
		<< ",Range:" <<(int)m_Range
		<< ")";
	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void ARInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM ARInfo");

		pResult->next();

		m_InfoCount = pResult->getInt(1);

		m_pItemInfos = new ItemInfo*[m_InfoCount+1];

		for (uint i = 0 ; i <= m_InfoCount ; i ++)
			m_pItemInfos[i] = NULL;

		pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, minDamage, maxDamage, ToHitBonus, `Range`, Speed, ReqAbility, ItemLevel, CriticalBonus, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM ARInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			ARInfo* pARInfo = new ARInfo();

			pARInfo->setItemType(pResult->getInt(++i));
			pARInfo->setName(pResult->getString(++i));
			pARInfo->setEName(pResult->getString(++i));
			pARInfo->setPrice(pResult->getInt(++i));
			pARInfo->setVolumeType(pResult->getInt(++i));
			pARInfo->setWeight(pResult->getInt(++i));
			pARInfo->setRatio(pResult->getInt(++i));
			pARInfo->setDurability(pResult->getInt(++i));
			pARInfo->setMinDamage(pResult->getInt(++i));
			pARInfo->setMaxDamage(pResult->getInt(++i));
			pARInfo->setToHitBonus(pResult->getInt(++i));
			pARInfo->setRange(pResult->getInt(++i));
			pARInfo->setSpeed(pResult->getInt(++i));
			pARInfo->setReqAbility(pResult->getString(++i));
			pARInfo->setItemLevel(pResult->getInt(++i));
			pARInfo->setCriticalBonus(pResult->getInt(++i));
			pARInfo->setDefaultOptions(pResult->getString(++i));
			pARInfo->setUpgradeRatio(pResult->getInt(++i));
			pARInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pARInfo->setNextOptionRatio(pResult->getInt(++i));
			pARInfo->setNextItemType(pResult->getInt(++i));
			pARInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pARInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_DEBUG
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void ARLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, BulletCount, Silver, EnchantLevel FROM ARObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR       << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/
		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, BulletCount, Silver, EnchantLevel, Grade, ItemFlag FROM ARObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());

		while (pResult->next())
		{
			try {
				uint i = 0;

				AR* pAR = new AR();

				pAR->setItemID(pResult->getDWORD(++i));
				pAR->setObjectID(pResult->getDWORD(++i));
				pAR->setItemType(pResult->getDWORD(++i));
	
				if (g_pARInfoManager->getItemInfo(pAR->getItemType())->isUnique())
					pAR->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pAR->setOptionType(optionTypes);

				pAR->setDurability(pResult->getInt(++i));
				pAR->setBulletCount(pResult->getInt(++i));
				pAR->setSilver(pResult->getInt(++i));
				pAR->setEnchantLevel(pResult->getInt(++i));
				pAR->setGrade(pResult->getInt(++i));
				pAR->setCreateType((Item::CreateType)pResult->getInt(++i));

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
						if (storageID != 0 )
						{
							SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
							if (pInventoryItem == NULL )
							{
								processItemBugEx(pCreature, pAR);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pAR))
						{
							pInventory->addItemEx(x, y, pAR);
						}
						else
						{
							processItemBugEx(pCreature, pAR);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pAR);
							}
							else
							{
								processItemBugEx(pCreature, pAR);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pAR);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pAR);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pAR);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pAR);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pAR);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pAR);
						}
						else pStash->insert(x, y, pAR);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pAR);
						break;

					default :
						SAFE_DELETE(pStmt);	// by sigi
						throw Error("invalid storage or OwnerID must be NULL");
				}
			} catch (Error& error) {
				filelog("itemLoadError.txt", "[%s] %s", getItemClassName().c_str(), error.toString().c_str());
				throw;
			} catch (Throwable& t) {
				filelog("itemLoadError.txt", "[%s] %s", getItemClassName().c_str(), t.toString().c_str());
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to zone
//--------------------------------------------------------------------------------
void ARLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, BulletCount, Silver, EnchantLevel, ItemFlag FROM ARObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			AR* pAR = new AR();

			pAR->setItemID(pResult->getInt(++i));
			pAR->setObjectID(pResult->getInt(++i));
			pAR->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pAR->setOptionType(optionTypes);

			pAR->setDurability(pResult->getInt(++i));
			pAR->setBulletCount(pResult->getInt(++i));
			pAR->setSilver(pResult->getInt(++i));
			pAR->setEnchantLevel(pResult->getInt(++i));
			pAR->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pAR);
					}
					break;

				case STORAGE_STASH :
				case STORAGE_CORPSE :
					SAFE_DELETE(pStmt); 	// by sigi
					throw UnsupportedError("상자 및 시체안의 아이템의 저장은 아직 지원되지 않습니다.");

				default :
					SAFE_DELETE(pStmt);	// by sigi
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
void ARLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
	}
	END_DB(pStmt);
	
	__END_CATCH
}


// global variable definition
ARLoader* g_pARLoader = NULL;
