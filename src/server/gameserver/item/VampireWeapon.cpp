//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireWeapon.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

// include files
#include "VampireWeapon.h"
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
VampireWeaponInfoManager* g_pVampireWeaponInfoManager = NULL;

ItemID_t VampireWeapon::m_ItemIDRegistry = 0;
Mutex    VampireWeapon::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
VampireWeapon::VampireWeapon()
	throw()
{
	setItemType(0);
	setDurability(0);
	setBonusDamage(0);
}

VampireWeapon::VampireWeapon(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_OptionType(optionType )
{
	setItemType(itemType);
	setOptionType(optionType);
	setBonusDamage(0);

	//m_EnchantLevel = 0;
	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "VampireWeapon::VampireWeapon() : Invalid item type or option type");
		throw("VampireWeapon::VampireWeapon() : Invalid item type or optionType");
	}
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void VampireWeapon::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);

		sql << "INSERT INTO VampireWeaponObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Durability, Grade, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', " << getDurability() << ", " << getGrade() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireWeapon::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE VampireWeaponObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireWeapon::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE VampireWeaponObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << getItemType()
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)getOptionTypeList()
			<< ",Durability = " << getDurability()
			<< ",EnchantLevel = " <<(int)m_EnchantLevel
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("UPDATE VampireWeaponObject SET ObjectID=%ld, ItemType=%d, OwnerID= '%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(), m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireWeapon::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireWeapon("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",Durability:"   <<(int)getDurability()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t VampireWeapon::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t VampireWeapon::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t VampireWeapon::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's minDamage
//--------------------------------------------------------------------------------
Damage_t VampireWeapon::getMinDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getMinDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's maxDamage
//--------------------------------------------------------------------------------
Damage_t VampireWeapon::getMaxDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getMaxDamage() + m_BonusDamage;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int VampireWeapon::getCriticalBonus(void) const
	throw()
{
	__BEGIN_TRY

	return g_pVampireWeaponInfoManager->getItemInfo(m_ItemType)->getCriticalBonus();

	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireWeaponInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireWeaponInfo("
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
		<< ",ReqAbility:"
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void VampireWeaponInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampireWeaponInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType,Name,EName,Price,Volume,Weight,Ratio,Durability,minDamage,maxDamage,Speed,ReqAbility,ItemLevel, CriticalBonus, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM VampireWeaponInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampireWeaponInfo* pVampireWeaponInfo = new VampireWeaponInfo();

			pVampireWeaponInfo->setItemType(pResult->getInt(++i));
			pVampireWeaponInfo->setName(pResult->getString(++i));
			pVampireWeaponInfo->setEName(pResult->getString(++i));
			pVampireWeaponInfo->setPrice(pResult->getInt(++i));
			pVampireWeaponInfo->setVolumeType(pResult->getInt(++i));
			pVampireWeaponInfo->setWeight(pResult->getInt(++i));
			pVampireWeaponInfo->setRatio(pResult->getInt(++i));
			pVampireWeaponInfo->setDurability(pResult->getInt(++i));
			pVampireWeaponInfo->setMinDamage(pResult->getInt(++i));
			pVampireWeaponInfo->setMaxDamage(pResult->getInt(++i));
			pVampireWeaponInfo->setSpeed(pResult->getInt(++i));
			pVampireWeaponInfo->setReqAbility(pResult->getString(++i));
			pVampireWeaponInfo->setItemLevel(pResult->getInt(++i));
			pVampireWeaponInfo->setCriticalBonus(pResult->getInt(++i));
			pVampireWeaponInfo->setDefaultOptions(pResult->getString(++i));
			pVampireWeaponInfo->setUpgradeRatio(pResult->getInt(++i));
			pVampireWeaponInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pVampireWeaponInfo->setNextOptionRatio(pResult->getInt(++i));
			pVampireWeaponInfo->setNextItemType(pResult->getInt(++i));
			pVampireWeaponInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pVampireWeaponInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void VampireWeaponLoader::load(Creature* pCreature) 
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
			<< " OptionType, Durability, EnchantLevel FROM VampireWeaponObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM VampireWeaponObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
													pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				VampireWeapon* pVampireWeapon = new VampireWeapon();

				pVampireWeapon->setItemID(pResult->getDWORD(++i));
				pVampireWeapon->setObjectID(pResult->getDWORD(++i));
				pVampireWeapon->setItemType(pResult->getDWORD(++i));
	
				if (g_pVampireWeaponInfoManager->getItemInfo(pVampireWeapon->getItemType())->isUnique())
					pVampireWeapon->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pVampireWeapon->setOptionType(optionTypes);

				pVampireWeapon->setDurability(pResult->getInt(++i));
				pVampireWeapon->setGrade(pResult->getInt(++i));
				pVampireWeapon->setEnchantLevel(pResult->getInt(++i));
				pVampireWeapon->setCreateType((Item::CreateType)pResult->getInt(++i));

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
								processItemBugEx(pCreature, pVampireWeapon);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pVampireWeapon))
						{
							pInventory->addItemEx(x, y, pVampireWeapon);
						}
						else
						{
							processItemBugEx(pCreature, pVampireWeapon);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isVampire())
						{
							if (!pVampire->isWear((Vampire::WearPart)x))
							{
								pVampire->wearItem((Vampire::WearPart)x, pVampireWeapon);
							}
							else
							{
								processItemBugEx(pCreature, pVampireWeapon);
							}
						}
						else if (pCreature->isSlayer())
						{
							processItemBugEx(pCreature, pVampireWeapon);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pVampireWeapon);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampireWeapon);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampireWeapon);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pVampireWeapon);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pVampireWeapon);
						}
						else
						{
							pStash->insert(x, y, pVampireWeapon);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pVampireWeapon);
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
void VampireWeaponLoader::load(Zone* pZone) 
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
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM VampireWeaponObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			VampireWeapon* pVampireWeapon = new VampireWeapon();

			pVampireWeapon->setItemID(pResult->getInt(++i));
			pVampireWeapon->setObjectID(pResult->getInt(++i));
			pVampireWeapon->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pVampireWeapon->setOptionType(optionTypes);

			pVampireWeapon->setDurability(pResult->getInt(++i));
			pVampireWeapon->setEnchantLevel(pResult->getInt(++i));
			pVampireWeapon->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pVampireWeapon);
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
void VampireWeaponLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

VampireWeaponLoader* g_pVampireWeaponLoader = NULL;
