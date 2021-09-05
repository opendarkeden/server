//////////////////////////////////////////////////////////////////////////////
// Filename    : Ring.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Ring.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
RingInfoManager* g_pRingInfoManager = NULL;

ItemID_t Ring::m_ItemIDRegistry = 0;
Mutex    Ring::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Ring::Ring()
	
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
	setDurability(0);
	//m_EnchantLevel = 0;
}

Ring::Ring(ItemType_t itemType, const list<OptionType_t>& optionType)
	
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0)
{
	setItemType(itemType);
	setOptionType(optionType);
	//m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "Ring::Ring() : Invalid item type or option type");
		throw ("Ring::Ring() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Ring::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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
		setOptionTypeToField( getOptionTypeList(), optionField );

		sql << "INSERT INTO RingObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Durability, Grade, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', " << getDurability() << ", " << getGrade() << ", " << (int)m_CreateType << ")";

		pStmt->executeQueryString(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Ring::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE RingObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Ring::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE RingObject SET "
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

		pStmt->executeQueryString(sql.toString());
		*/

		string optionField;
		setOptionTypeToField( getOptionTypeList(), optionField );
		pStmt->executeQuery( "UPDATE RingObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
									m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Ring::toString() const 
	
{
	StringStream msg;

	msg << "Ring("
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
VolumeWidth_t Ring::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pRingInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Ring::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pRingInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Ring::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pRingInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t Ring::getDefenseBonus() const 
	
{
	__BEGIN_TRY

	return g_pRingInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t Ring::getProtectionBonus() const
	
{
	__BEGIN_TRY

	return g_pRingInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string RingInfo::toString() const 
	
{
	StringStream msg;

	msg << "RingInfo("
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
void RingInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM RingInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM RingInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			RingInfo* pRingInfo = new RingInfo();

			pRingInfo->setItemType(pResult->getInt(++i));
			pRingInfo->setName(pResult->getString(++i));
			pRingInfo->setEName(pResult->getString(++i));
			pRingInfo->setPrice(pResult->getInt(++i));
			pRingInfo->setVolumeType(pResult->getInt(++i));
			pRingInfo->setWeight(pResult->getInt(++i));
			pRingInfo->setRatio(pResult->getInt(++i));
			pRingInfo->setDurability(pResult->getInt(++i));
			pRingInfo->setDefenseBonus(pResult->getInt(++i));
			pRingInfo->setProtectionBonus(pResult->getInt(++i));
			pRingInfo->setReqAbility(pResult->getString(++i));
			pRingInfo->setItemLevel(pResult->getInt(++i));
			pRingInfo->setDefaultOptions(pResult->getString(++i));
			pRingInfo->setUpgradeRatio(pResult->getInt(++i));
			pRingInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pRingInfo->setNextOptionRatio(pResult->getInt(++i));
			pRingInfo->setNextItemType(pResult->getInt(++i));
			pRingInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pRingInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void RingLoader::load(Creature* pCreature) 
	
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
			<< " OptionType, Durability, EnchantLevel FROM RingObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQueryString(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM RingObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				Ring* pRing = new Ring();

				pRing->setItemID(pResult->getDWORD(++i));
				pRing->setObjectID(pResult->getDWORD(++i));
				pRing->setItemType(pResult->getDWORD(++i));
	
				if (g_pRingInfoManager->getItemInfo(pRing->getItemType())->isUnique())
					pRing->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pRing->setOptionType(optionTypes);

				pRing->setDurability(pResult->getInt(++i));
				pRing->setGrade(pResult->getInt(++i));
				pRing->setEnchantLevel(pResult->getInt(++i));
				pRing->setCreateType((Item::CreateType)pResult->getInt(++i));

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
				else throw UnsupportedError("Monster,NPC �κ��丮�� ������ ���� �������� �ʽ��ϴ�.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pRing))
						{
							pInventory->addItemEx(x, y, pRing);
						}
						else
						{
							processItemBugEx(pCreature, pRing);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pRing);
							}
							else
							{
								processItemBugEx(pCreature, pRing);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pRing);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pRing);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pRing);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pRing);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pRing);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pRing);
						}
						else pStash->insert(x, y, pRing);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pRing);
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
void RingLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM RingObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQueryString(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Ring* pRing = new Ring();

			pRing->setItemID(pResult->getInt(++i));
			pRing->setObjectID(pResult->getInt(++i));
			pRing->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pRing->setOptionType(optionTypes);

			pRing->setDurability(pResult->getInt(++i));
			pRing->setEnchantLevel(pResult->getInt(++i));
			pRing->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pRing);
					}
					break;

				case STORAGE_STASH :
				case STORAGE_CORPSE :
					throw UnsupportedError("���� �� ��ü���� �������� ������ ���� �������� �ʽ��ϴ�.");

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
void RingLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

RingLoader* g_pRingLoader = NULL;
