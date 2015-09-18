//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersArmsband.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "OustersArmsband.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "SubInventory.h"

// global variable declaration
OustersArmsbandInfoManager* g_pOustersArmsbandInfoManager = NULL;

ItemID_t OustersArmsband::m_ItemIDRegistry = 0;
Mutex    OustersArmsband::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
OustersArmsband::OustersArmsband()
	throw()
//: m_ItemType(0), m_Durability(0), m_pInventory(NULL)
{
	setItemType(0);
	setDurability(0);
	m_pInventory = NULL;
//	m_EnchantLevel = 0;
}

OustersArmsband::OustersArmsband(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0), m_pInventory(NULL)
{
	setItemType(itemType);
	setOptionType(optionType);
	OustersArmsbandInfo* pOustersArmsbandInfo = dynamic_cast<OustersArmsbandInfo*>(g_pOustersArmsbandInfoManager->getItemInfo(getItemType() ));

	m_pInventory = new Inventory(pOustersArmsbandInfo->getPocketCount(), 1);

//	m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "OustersArmsband::OustersArmsband() : Invalid item type or option type");
		throw("OustersArmsband::OustersArmsband() : Invalid item type or optionType");
	}
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
OustersArmsband::~OustersArmsband()
	throw()
{
	SAFE_DELETE(m_pInventory);
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void OustersArmsband::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO OustersArmsbandObject "
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
// destroy item
//--------------------------------------------------------------------------------
bool OustersArmsband::destroy()
    throw(Error)
{
    __BEGIN_TRY

    Statement* pStmt;

    //-------------------------------------------------------
    // 암스밴드에 남아있는 아이템이 있다면 안에 있는 아이템들도
    // destroy 해줘야 한다.
    // 암스밴드 같은 경우는 위에서 delete하면서 아이템을 삭제
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
        pStmt->executeQuery("DELETE FROM OustersArmsbandObject WHERE ItemID = %ld", m_ItemID);

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
void OustersArmsband::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE OustersArmsbandObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void OustersArmsband::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE OustersArmsbandObject SET "
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
		pStmt->executeQuery("UPDATE OustersArmsbandObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
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

void OustersArmsband::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);

	BYTE SubItemCount = 0;

	// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
	for (int i = 0; i < getPocketCount(); i++) 
	{
		Item* pOustersArmsbandItem = getInventory()->getItem(i, 0);

		if (pOustersArmsbandItem != NULL) 
		{
			SubItemInfo* pSubItemInfo = new SubItemInfo();
			pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
			pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
			pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
			pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
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
string OustersArmsband::toString() const 
	throw()
{
	StringStream msg;

	msg << "OustersArmsband("
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
VolumeWidth_t OustersArmsband::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersArmsbandInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t OustersArmsband::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersArmsbandInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t OustersArmsband::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersArmsbandInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get pocket count
//--------------------------------------------------------------------------------
PocketNum_t OustersArmsband::getPocketCount(void) const
	throw()
{
	__BEGIN_TRY

	OustersArmsbandInfo* pOustersArmsbandInfo = dynamic_cast<OustersArmsbandInfo*>(g_pOustersArmsbandInfoManager->getItemInfo(getItemType()));
	Assert(pOustersArmsbandInfo != NULL);
	return pOustersArmsbandInfo->getPocketCount();

	__END_CATCH
}
/*
//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t OustersArmsband::getDefenseBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersArmsbandInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t OustersArmsband::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersArmsbandInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}

*/
//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string OustersArmsbandInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "OustersArmsbandInfo("
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
void OustersArmsbandInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM OustersArmsbandInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, PocketCount,ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM OustersArmsbandInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			OustersArmsbandInfo* pOustersArmsbandInfo = new OustersArmsbandInfo();

			pOustersArmsbandInfo->setItemType(pResult->getInt(++i));
			pOustersArmsbandInfo->setName(pResult->getString(++i));
			pOustersArmsbandInfo->setEName(pResult->getString(++i));
			pOustersArmsbandInfo->setPrice(pResult->getInt(++i));
			pOustersArmsbandInfo->setVolumeType(pResult->getInt(++i));
			pOustersArmsbandInfo->setWeight(pResult->getInt(++i));
			pOustersArmsbandInfo->setRatio(pResult->getInt(++i));
			pOustersArmsbandInfo->setDurability(pResult->getInt(++i));
			pOustersArmsbandInfo->setDefenseBonus(pResult->getInt(++i));
			pOustersArmsbandInfo->setProtectionBonus(pResult->getInt(++i));
			pOustersArmsbandInfo->setPocketCount(pResult->getInt(++i));
			pOustersArmsbandInfo->setReqAbility(pResult->getString(++i));
			pOustersArmsbandInfo->setItemLevel(pResult->getInt(++i));
			pOustersArmsbandInfo->setDefaultOptions(pResult->getString(++i));
			pOustersArmsbandInfo->setUpgradeRatio(pResult->getInt(++i));
			pOustersArmsbandInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pOustersArmsbandInfo->setNextOptionRatio(pResult->getInt(++i));
			pOustersArmsbandInfo->setNextItemType(pResult->getInt(++i));
			pOustersArmsbandInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pOustersArmsbandInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void OustersArmsbandLoader::load(Creature* pCreature) 
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
			<< "OptionType, Durability, EnchantLevel FROM OustersArmsbandObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM OustersArmsbandObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				OustersArmsband* pOustersArmsband = new OustersArmsband();

				pOustersArmsband->setItemID(pResult->getDWORD(++i));
				pOustersArmsband->setObjectID(pResult->getDWORD(++i));
				pOustersArmsband->setItemType(pResult->getDWORD(++i));
	
				if (g_pOustersArmsbandInfoManager->getItemInfo(pOustersArmsband->getItemType())->isUnique())
					pOustersArmsband->setUnique();

				OustersArmsbandInfo* pOustersArmsbandInfo = dynamic_cast<OustersArmsbandInfo*>(g_pOustersArmsbandInfoManager->getItemInfo(pOustersArmsband->getItemType() ));
				Inventory* pOustersArmsbandInventory = new Inventory(pOustersArmsbandInfo->getPocketCount(), 1);

				pOustersArmsband->setInventory(pOustersArmsbandInventory);

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pOustersArmsband->setOptionType(optionTypes);

				pOustersArmsband->setDurability(pResult->getInt(++i));
				pOustersArmsband->setGrade(pResult->getInt(++i));
				pOustersArmsband->setEnchantLevel(pResult->getInt(++i));
				pOustersArmsband->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*	pOusters		= NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
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
				else if (pCreature->isOusters())
				{
					pOusters   = dynamic_cast<Ousters*>(pCreature);
					pInventory = pOusters->getInventory();
					pStash     = pOusters->getStash();
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
								processItemBugEx(pCreature, pOustersArmsband);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pOustersArmsband))
						{
							pInventory->addItemEx(x, y, pOustersArmsband);
						}
						else
						{
							processItemBugEx(pCreature, pOustersArmsband);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer() || pCreature->isVampire())
						{
							processItemBugEx(pCreature, pOustersArmsband);
						}
						else if (pCreature->isOusters())
						{
							if (!pOusters->isWear((Ousters::WearPart)x))
							{
								pOusters->wearItem((Ousters::WearPart)x, pOustersArmsband);
							}
							else
							{
								processItemBugEx(pCreature, pOustersArmsband);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pOustersArmsband);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pOustersArmsband);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pOustersArmsband);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pOustersArmsband);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pOustersArmsband);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pOustersArmsband);
						}
						else pStash->insert(x, y, pOustersArmsband);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pOustersArmsband);
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
void OustersArmsbandLoader::load(Zone* pZone) 
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
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM OustersArmsbandObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			OustersArmsband* pOustersArmsband = new OustersArmsband();

			pOustersArmsband->setItemID(pResult->getInt(++i));
			pOustersArmsband->setObjectID(pResult->getInt(++i));
			pOustersArmsband->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pOustersArmsband->setOptionType(optionTypes);

			pOustersArmsband->setDurability(pResult->getInt(++i));
			pOustersArmsband->setEnchantLevel(pResult->getInt(++i));
			pOustersArmsband->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pOustersArmsband);
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
void OustersArmsbandLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

OustersArmsbandLoader* g_pOustersArmsbandLoader = NULL;
