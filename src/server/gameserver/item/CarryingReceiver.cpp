//////////////////////////////////////////////////////////////////////////////
// Filename    : CarryingReceiver.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CarryingReceiver.h"
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
CarryingReceiverInfoManager* g_pCarryingReceiverInfoManager = NULL;

ItemID_t CarryingReceiver::m_ItemIDRegistry = 0;
Mutex    CarryingReceiver::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
CarryingReceiver::CarryingReceiver()
	throw()
{
	setItemType(0);
}

CarryingReceiver::CarryingReceiver(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	setItemType(itemType);
	setOptionType(optionType);

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "CarryingReceiver::CarryingReceiver() : Invalid item type or option type");
		throw("CarryingReceiver::CarryingReceiver() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void CarryingReceiver::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO CarryingReceiverObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Grade, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', " << getGrade() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CarryingReceiver::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE CarryingReceiverObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CarryingReceiver::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("UPDATE CarryingReceiverObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
									m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getGrade(), (int)getEnchantLevel(), m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CarryingReceiver::toString() const 
	throw()
{
	StringStream msg;

	msg << "CarryingReceiver("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CarryingReceiverInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "CarryingReceiverInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",DefenseBonus:" << m_DefenseBonus
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void CarryingReceiverInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM CarryingReceiverInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM CarryingReceiverInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			CarryingReceiverInfo* pCarryingReceiverInfo = new CarryingReceiverInfo();

			pCarryingReceiverInfo->setItemType(pResult->getInt(++i));
			pCarryingReceiverInfo->setName(pResult->getString(++i));
			pCarryingReceiverInfo->setEName(pResult->getString(++i));
			pCarryingReceiverInfo->setPrice(pResult->getInt(++i));
			pCarryingReceiverInfo->setVolumeType(pResult->getInt(++i));
			pCarryingReceiverInfo->setWeight(pResult->getInt(++i));
			pCarryingReceiverInfo->setRatio(pResult->getInt(++i));
			pCarryingReceiverInfo->setDefenseBonus(pResult->getInt(++i));
			pCarryingReceiverInfo->setProtectionBonus(pResult->getInt(++i));
			pCarryingReceiverInfo->setReqAbility(pResult->getString(++i));
			pCarryingReceiverInfo->setItemLevel(pResult->getInt(++i));
			pCarryingReceiverInfo->setDefaultOptions(pResult->getString(++i));
			pCarryingReceiverInfo->setUpgradeRatio(pResult->getInt(++i));
			pCarryingReceiverInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pCarryingReceiverInfo->setNextOptionRatio(pResult->getInt(++i));
			pCarryingReceiverInfo->setNextItemType(pResult->getInt(++i));
			pCarryingReceiverInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pCarryingReceiverInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void CarryingReceiverLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Grade, EnchantLevel, ItemFlag FROM CarryingReceiverObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				CarryingReceiver* pCarryingReceiver = new CarryingReceiver();

				pCarryingReceiver->setItemID(pResult->getDWORD(++i));
				pCarryingReceiver->setObjectID(pResult->getDWORD(++i));
				pCarryingReceiver->setItemType(pResult->getDWORD(++i));
	
				if (g_pCarryingReceiverInfoManager->getItemInfo(pCarryingReceiver->getItemType())->isUnique())
					pCarryingReceiver->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pCarryingReceiver->setOptionType(optionTypes);

				pCarryingReceiver->setGrade(pResult->getInt(++i));
				pCarryingReceiver->setEnchantLevel(pResult->getInt(++i));
				pCarryingReceiver->setCreateType((Item::CreateType)pResult->getInt(++i));

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
								processItemBugEx(pCreature, pCarryingReceiver);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pCarryingReceiver))
						{
							pInventory->addItemEx(x, y, pCarryingReceiver);
						}
						else
						{
							processItemBugEx(pCreature, pCarryingReceiver);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pCarryingReceiver);
							}
							else
							{
								processItemBugEx(pCreature, pCarryingReceiver);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pCarryingReceiver);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pCarryingReceiver);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pCarryingReceiver);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pCarryingReceiver);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pCarryingReceiver);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pCarryingReceiver);
						}
						else pStash->insert(x, y, pCarryingReceiver);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pCarryingReceiver);
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
void CarryingReceiverLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to inventory
//--------------------------------------------------------------------------------
void CarryingReceiverLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

CarryingReceiverLoader* g_pCarryingReceiverLoader = NULL;
