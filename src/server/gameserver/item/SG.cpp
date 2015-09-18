//////////////////////////////////////////////////////////////////////////////
// Filename    : SG.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

// include files
#include "SG.h"
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
SGInfoManager* g_pSGInfoManager = NULL;

ItemID_t SG::m_ItemIDRegistry = 0;
Mutex    SG::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
SG::SG()
	throw()
{
	setItemType(0);
	setDurability(0);
	setEnchantLevel(0);
	setBulletCount(0);
	setBonusDamage(0);
	setSilver(0);
}

SG::SG(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: Gun(itemType, optionType)
{
	setItemType(itemType);
	setOptionType(optionType);
	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "SG::SG() : Invalid item type or option type");
		throw("SG::SG() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
SG::~SG()
	throw()
{
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void SG::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO SGObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Durability, BulletCount, Grade, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', " << getDurability() << ", " <<(int)getBulletCount() << ", " << (int)getGrade() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}




//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SG::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SGObject SET %s, BulletCount=%d WHERE ItemID=%ld",
								field, (int)getBulletCount(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SG::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE SGObject SET "
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
		pStmt->executeQuery("UPDATE SGObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, EnchantLevel=%d, BulletCount=%d, Silver=%d, Grade=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), (int)getEnchantLevel(), (int)getBulletCount(), (int)getSilver(), (int)getGrade(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SG::saveBullet() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SGObject SET BulletCount = %d WHERE ItemID = %d",
								getBulletCount(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void SG::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);
	result.setItemNum(getBulletCount());
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string SG::toString() const 
	throw()
{
	StringStream msg;

	msg << "SG("
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

/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t SG::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t SG::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t SG::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's minDamage
//--------------------------------------------------------------------------------
Damage_t SG::getMinDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getMinDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's maxDamage
//--------------------------------------------------------------------------------
Damage_t SG::getMaxDamage() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getMaxDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's range
//--------------------------------------------------------------------------------
Range_t SG::getRange() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getRange();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's ToHit Bonus
//--------------------------------------------------------------------------------
ToHit_t SG::getToHitBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getToHitBonus();

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int SG::getCriticalBonus(void) const
	throw()
{
	__BEGIN_TRY

	return g_pSGInfoManager->getItemInfo(m_ItemType)->getCriticalBonus();

	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string SGInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "SGInfo("
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
		<< ",ReqAbility:?"
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void SGInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SGInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, minDamage, maxDamage, ToHitBonus, `Range`, Speed, ReqAbility, ItemLevel, CriticalBonus, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM SGInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SGInfo* pSGInfo = new SGInfo();

			pSGInfo->setItemType(pResult->getInt(++i));
			pSGInfo->setName(pResult->getString(++i));
			pSGInfo->setEName(pResult->getString(++i));
			pSGInfo->setPrice(pResult->getInt(++i));
			pSGInfo->setVolumeType(pResult->getInt(++i));
			pSGInfo->setWeight(pResult->getInt(++i));
			pSGInfo->setRatio(pResult->getInt(++i));
			pSGInfo->setDurability(pResult->getInt(++i));
			pSGInfo->setMinDamage(pResult->getInt(++i));
			pSGInfo->setMaxDamage(pResult->getInt(++i));
			pSGInfo->setToHitBonus(pResult->getInt(++i));
			pSGInfo->setRange(pResult->getInt(++i));
			pSGInfo->setSpeed(pResult->getInt(++i));
			pSGInfo->setReqAbility(pResult->getString(++i));
			pSGInfo->setItemLevel(pResult->getInt(++i));
			pSGInfo->setCriticalBonus(pResult->getInt(++i));
			pSGInfo->setDefaultOptions(pResult->getString(++i));
			pSGInfo->setUpgradeRatio(pResult->getInt(++i));
			pSGInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pSGInfo->setNextOptionRatio(pResult->getInt(++i));
			pSGInfo->setNextItemType(pResult->getInt(++i));
			pSGInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pSGInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void SGLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< "OptionType, Durability, EnchantLevel, BulletCount, Silver FROM SGObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,OptionType, Durability, EnchantLevel, BulletCount, Silver, Grade, ItemFlag FROM SGObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				SG* pSG = new SG();

				pSG->setItemID(pResult->getDWORD(++i));
				pSG->setObjectID(pResult->getDWORD(++i));
				pSG->setItemType(pResult->getDWORD(++i));
	
				if (g_pSGInfoManager->getItemInfo(pSG->getItemType())->isUnique())
					pSG->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pSG->setOptionType(optionTypes);

				pSG->setDurability(pResult->getInt(++i));
				pSG->setEnchantLevel(pResult->getInt(++i));
				pSG->setBulletCount(pResult->getInt(++i));
				pSG->setSilver(pResult->getInt(++i));
				pSG->setGrade(pResult->getInt(++i));
				pSG->setCreateType((Item::CreateType)pResult->getInt(++i));

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
								processItemBugEx(pCreature, pSG);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pSG))
						{
							pInventory->addItemEx(x, y, pSG);
						}
						else
						{
							processItemBugEx(pCreature, pSG);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pSG);
							}
							else
							{
								processItemBugEx(pCreature, pSG);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pSG);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pSG);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSG);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSG);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pSG);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pSG);
						}
						else pStash->insert(x, y, pSG);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pSG);
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
void SGLoader::load(Zone* pZone) 
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
			<< " OptionType, Durability, EnchantLevel, BulletCount, Silver, ItemFlag FROM SGObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			SG* pSG = new SG();

			pSG->setItemID(pResult->getInt(++i));
			pSG->setObjectID(pResult->getInt(++i));
			pSG->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pSG->setOptionType(optionTypes);

			pSG->setDurability(pResult->getInt(++i));
			pSG->setEnchantLevel(pResult->getInt(++i));
			pSG->setBulletCount(pResult->getInt(++i));
			pSG->setSilver(pResult->getInt(++i));
			pSG->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pSG);
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
void SGLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

SGLoader* g_pSGLoader = NULL;
