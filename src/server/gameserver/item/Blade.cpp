//////////////////////////////////////////////////////////////////////////////
// Filename    : Blade.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

// include files
#include "Blade.h"
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
BladeInfoManager* g_pBladeInfoManager = NULL;

ItemID_t Blade::m_ItemIDRegistry = 0;
Mutex    Blade::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Blade::Blade()
	throw()
{
	setItemType(0);
	setDurability(0);
	setBonusDamage(0);
	setSilver(0);
}

Blade::Blade(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_OptionType(optionType)
{
	setItemType(itemType);
	setOptionType(optionType);
	setBonusDamage(0);
	setSilver(0);

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "Blade::Blade() : Invalid item type or option type");
		throw("Blade::Blade() : Invalid item type or optionType");
	}
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Blade::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO BladeObject "
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
void Blade::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE BladeObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Blade::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE BladeObject SET "
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
			<< ",Silver = " <<(int)m_Silver
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("UPDATE BladeObject SET ObjectID=%ld, ItemType=%d, OwnerID= '%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, EnchantLevel=%d, Silver=%d, Grade=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), (int)getEnchantLevel(), (int)getSilver(), (int)getGrade(), m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Blade::toString() const 
	throw()
{
	StringStream msg;

	msg << "Blade("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",Durability:"   <<(int)getDurability()
		<< ",Silver:"       <<(int)getSilver()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Blade::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Blade::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Blade::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's minDamage
//--------------------------------------------------------------------------------
Damage_t Blade::getMinDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getMinDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's maxDamage
//--------------------------------------------------------------------------------
Damage_t Blade::getMaxDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getMaxDamage() + m_BonusDamage;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int Blade::getCriticalBonus(void) const
	throw()
{
	__BEGIN_TRY

	return g_pBladeInfoManager->getItemInfo(m_ItemType)->getCriticalBonus();

	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string BladeInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "BladeInfo("
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
void BladeInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM BladeInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType,Name,EName,Price,Volume,Weight,Ratio,Durability,minDamage,maxDamage,MaxSilver,Speed,ReqAbility,ItemLevel, CriticalBonus, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM BladeInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			BladeInfo* pBladeInfo = new BladeInfo();

			pBladeInfo->setItemType(pResult->getInt(++i));
			pBladeInfo->setName(pResult->getString(++i));
			pBladeInfo->setEName(pResult->getString(++i));
			pBladeInfo->setPrice(pResult->getInt(++i));
			pBladeInfo->setVolumeType(pResult->getInt(++i));
			pBladeInfo->setWeight(pResult->getInt(++i));
			pBladeInfo->setRatio(pResult->getInt(++i));
			pBladeInfo->setDurability(pResult->getInt(++i));
			pBladeInfo->setMinDamage(pResult->getInt(++i));
			pBladeInfo->setMaxDamage(pResult->getInt(++i));
			pBladeInfo->setMaxSilver(pResult->getInt(++i));
			pBladeInfo->setSpeed(pResult->getInt(++i));
			pBladeInfo->setReqAbility(pResult->getString(++i));
			pBladeInfo->setItemLevel(pResult->getInt(++i));
			pBladeInfo->setCriticalBonus(pResult->getInt(++i));
			pBladeInfo->setDefaultOptions(pResult->getString(++i));
			pBladeInfo->setUpgradeRatio(pResult->getInt(++i));
			pBladeInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pBladeInfo->setNextOptionRatio(pResult->getInt(++i));
			pBladeInfo->setNextItemType(pResult->getInt(++i));
			pBladeInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pBladeInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void BladeLoader::load(Creature* pCreature) 
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
			<< " OptionType, Durability, EnchantLevel, Silver FROM BladeObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, EnchantLevel, Silver, Grade, ItemFlag FROM BladeObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
													pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				Blade* pBlade = new Blade();

				pBlade->setItemID(pResult->getDWORD(++i));
				pBlade->setObjectID(pResult->getDWORD(++i));
				pBlade->setItemType(pResult->getDWORD(++i));
	
				if (g_pBladeInfoManager->getItemInfo(pBlade->getItemType())->isUnique())
					pBlade->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pBlade->setOptionType(optionTypes);

				pBlade->setDurability(pResult->getInt(++i));
				pBlade->setEnchantLevel(pResult->getInt(++i));
				pBlade->setSilver(pResult->getInt(++i));
				pBlade->setGrade(pResult->getInt(++i));
				pBlade->setCreateType((Item::CreateType)pResult->getInt(++i));

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
								processItemBugEx(pCreature, pBlade);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pBlade))
						{
							pInventory->addItemEx(x, y, pBlade);
						}
						else
						{
							processItemBugEx(pCreature, pBlade);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pBlade);
							}
							else
							{
								processItemBugEx(pCreature, pBlade);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pBlade);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pBlade);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pBlade);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pBlade);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pBlade);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pBlade);
						}
						else
						{
							pStash->insert(x, y, pBlade);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pBlade);
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
void BladeLoader::load(Zone* pZone) 
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
			<< " OptionType, Durability, EnchantLevel, Silver, ItemFlag FROM BladeObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Blade* pBlade = new Blade();

			pBlade->setItemID(pResult->getInt(++i));
			pBlade->setObjectID(pResult->getInt(++i));
			pBlade->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pBlade->setOptionType(optionTypes);

			pBlade->setDurability(pResult->getInt(++i));
			pBlade->setEnchantLevel(pResult->getInt(++i));
			pBlade->setSilver(pResult->getInt(++i));
			pBlade->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pBlade);
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
void BladeLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

BladeLoader* g_pBladeLoader = NULL;
