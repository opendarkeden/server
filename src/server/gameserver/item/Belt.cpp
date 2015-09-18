//////////////////////////////////////////////////////////////////////////////
// Filename    : Belt.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Belt.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "PCItemInfo.h"
#include "SubInventory.h"

// global variable declaration
BeltInfoManager* g_pBeltInfoManager = NULL;

ItemID_t Belt::m_ItemIDRegistry = 0;
Mutex    Belt::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Belt::Belt()
	throw()
//: m_ItemType(0), m_Durability(0), m_pInventory(NULL)
{
	setItemType(0);
	setDurability(0);
	m_pInventory = NULL;
//	m_EnchantLevel = 0;
}

Belt::Belt(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw(Error)
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0), m_pInventory(NULL)
{
	__BEGIN_TRY

	setItemType(itemType);
	setOptionType(optionType);

	BeltInfo* pBeltInfo = dynamic_cast<BeltInfo*>(g_pBeltInfoManager->getItemInfo(getItemType()));

	m_pInventory = new Inventory(pBeltInfo->getPocketCount(), 1);

//	m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "Belt::Belt() : Invalid item type or option type");
		throw("Belt::Belt() : Invalid item type or optionType");
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
Belt::~Belt()
	throw()
{
	SAFE_DELETE(m_pInventory);
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Belt::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO BeltObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Durability)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", " <<(int)m_OptionType << ", " << m_Durability << ")";

		pStmt->executeQuery(sql.toString());
		*/

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("INSERT INTO BeltObject (ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability, Grade, ItemFlag) VALUES(%ld, %ld, %d, '%s', %d, %ld, %d, %d, '%s', %d, %d, %d)",
								m_ItemID, m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)m_CreateType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// destroy item
//--------------------------------------------------------------------------------
bool Belt::destroy()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	//-------------------------------------------------------
	// 벨트에 남아있는 아이템이 있다면 안에 있는 아이템들도
	// destroy 해줘야 한다.
	// 벨트 같은 경우는 위에서 delete하면서 아이템을 삭제
	// 하기 때문에 여기서는 delete해주지 않기로 한다...
	// 쓸모가 없다면 위에서 필히 벨트를 지워야 한다.
	//-------------------------------------------------------
	for (int i = 0; i < m_pInventory->getHeight(); i++) 
	{
		for (int j = 0; j < m_pInventory->getWidth(); j++) 
		{
			Item* pItem = m_pInventory->getItem(j, i);
			if (pItem != NULL) 
			{
				pItem->destroy();
			}
		}
	}

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM BeltObject WHERE ItemID = %ld", m_ItemID);

		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH

	return true;
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Belt::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE BeltObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Belt::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE BeltObject SET "
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

		string optionField;
		setOptionTypeToField(getOptionTypeList(), optionField);
		pStmt->executeQuery("UPDATE BeltObject SET ObjectID=%ld, ItemType=%d, OwnerID= '%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(), m_ItemID);

		// 일일이 아이템을 하나씩 꺼내서 바로 UPDATE 하도록 한다.
		for (int i = 0; i < m_pInventory->getHeight(); i++) 
		{
			for (int j = 0; j < m_pInventory->getWidth(); j++) 
			{
				Item* pItem = m_pInventory->getItem(j, 0);
				if (pItem != NULL) {
					pItem->save(ownerID, STORAGE_BELT, m_ItemID, j, 0);
				}
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void Belt::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);

	BYTE SubItemCount = 0;

	// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
	for (int i = 0; i < getPocketCount() ; i++) 
	{
		Item* pBeltItem = getInventory()->getItem(i, 0);
		if (pBeltItem != NULL) 
		{
			SubItemInfo* pSubItemInfo = new SubItemInfo();
			pSubItemInfo->setObjectID(pBeltItem->getObjectID());
			pSubItemInfo->setItemClass(pBeltItem->getItemClass());
			pSubItemInfo->setItemType(pBeltItem->getItemType());
			pSubItemInfo->setItemNum(pBeltItem->getNum());
			pSubItemInfo->setSlotID(i);

			result.addListElement(pSubItemInfo);

			SubItemCount++;
		}
	}

	result.setListNum(SubItemCount);
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Belt::toString() const 
	throw()
{
	StringStream msg;

	msg << "Belt("
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
VolumeWidth_t Belt::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBeltInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Belt::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBeltInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Belt::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pBeltInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/
//--------------------------------------------------------------------------------
// get pocket count
//--------------------------------------------------------------------------------
PocketNum_t Belt::getPocketCount(void) const
	throw()
{
	__BEGIN_TRY

	BeltInfo* pBeltInfo = dynamic_cast<BeltInfo*>(g_pBeltInfoManager->getItemInfo(getItemType()));
	Assert(pBeltInfo != NULL);
	return pBeltInfo->getPocketCount();

	__END_CATCH
}

/*Defense_t Belt::getDefenseBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pBeltInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();
	
	__END_CATCH
}

Protection_t Belt::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pBeltInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/



//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string BeltInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "BeltInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",Durability:" << m_Durability
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void BeltInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM BeltInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, PocketCount, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM BeltInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			BeltInfo* pBeltInfo = new BeltInfo();

			pBeltInfo->setItemType(pResult->getInt(++i));
			pBeltInfo->setName(pResult->getString(++i));
			pBeltInfo->setEName(pResult->getString(++i));
			pBeltInfo->setPrice(pResult->getInt(++i));
			pBeltInfo->setVolumeType(pResult->getInt(++i));
			pBeltInfo->setWeight(pResult->getInt(++i));
			pBeltInfo->setRatio(pResult->getInt(++i));
			pBeltInfo->setDurability(pResult->getInt(++i));
			pBeltInfo->setDefenseBonus(pResult->getInt(++i));
			pBeltInfo->setProtectionBonus(pResult->getInt(++i));
			pBeltInfo->setPocketCount(pResult->getBYTE(++i));
			pBeltInfo->setReqAbility(pResult->getString(++i));
			pBeltInfo->setItemLevel(pResult->getBYTE(++i));
			pBeltInfo->setDefaultOptions(pResult->getString(++i));
			pBeltInfo->setUpgradeRatio(pResult->getInt(++i));
			pBeltInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pBeltInfo->setNextOptionRatio(pResult->getInt(++i));
			pBeltInfo->setNextItemType(pResult->getInt(++i));
			pBeltInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pBeltInfo);
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
void BeltLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, EnchantLevel FROM BeltObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM BeltObject WHERE OwnerID = '%s' AND Storage IN (0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				Belt* pBelt = new Belt();

				pBelt->setItemID(pResult->getDWORD(++i));
				pBelt->setObjectID(pResult->getDWORD(++i));
				pBelt->setItemType(pResult->getDWORD(++i));
	
				if (g_pBeltInfoManager->getItemInfo(pBelt->getItemType())->isUnique())
					pBelt->setUnique();

				BeltInfo* pBeltInfo = dynamic_cast<BeltInfo*>(g_pBeltInfoManager->getItemInfo(pBelt->getItemType()));
				Inventory* pBeltInventory = new Inventory(pBeltInfo->getPocketCount(), 1);

				pBelt->setInventory(pBeltInventory);

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pBelt->setOptionType(optionTypes);

				pBelt->setDurability(pResult->getInt(++i));
				pBelt->setGrade(pResult->getInt(++i));
				pBelt->setEnchantLevel(pResult->getInt(++i));
				pBelt->setCreateType((Item::CreateType)pResult->getInt(++i));
				
				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
				//Item*       pItem           = NULL;
				Stash*      pStash          = NULL;

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
								processItemBugEx(pCreature, pBelt);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pBelt))
						{
							pInventory->addItemEx(x, y, pBelt);
						}
						else 
						{
							processItemBugEx(pCreature, pBelt);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pBelt);
							}
							else
							{
								processItemBugEx(pCreature, pBelt);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pBelt);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pBelt);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pBelt);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pBelt);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pBelt);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pBelt);
						}
						else
						{
							pStash->insert(x, y, pBelt);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pBelt);
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
void BeltLoader::load(Zone* pZone) 
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
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM BeltObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Belt* pBelt = new Belt();

			pBelt->setItemID(pResult->getInt(++i));
			pBelt->setObjectID(pResult->getInt(++i));
			pBelt->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pBelt->setOptionType(optionTypes);

			pBelt->setDurability(pResult->getInt(++i));
			pBelt->setEnchantLevel(pResult->getInt(++i));
			pBelt->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pBelt);
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
void BeltLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

// global variable definition
BeltLoader* g_pBeltLoader = NULL;
