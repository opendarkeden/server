//////////////////////////////////////////////////////////////////////////////
// Filename    : Necklace.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Necklace.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
NecklaceInfoManager* g_pNecklaceInfoManager = NULL;

ItemID_t Necklace::m_ItemIDRegistry = 0;
Mutex    Necklace::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Necklace::Necklace()
	
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
	setDurability(0);
//	m_EnchantLevel = 0;
}

Necklace::Necklace(ItemType_t itemType, const list<OptionType_t>& optionType)
	
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0)
{
	setItemType(itemType);
	setOptionType(optionType);

//	m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "Necklace::Necklace() : Invalid item type or option type");
		throw ("Necklace::Necklace() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Necklace::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		sql << "INSERT INTO NecklaceObject "
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
void Necklace::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE NecklaceObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Necklace::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE NecklaceObject SET "
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
		pStmt->executeQuery( "UPDATE NecklaceObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(), m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Necklace::toString() const 
	
{
	StringStream msg;

	msg << "Necklace("
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
VolumeWidth_t Necklace::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pNecklaceInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Necklace::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pNecklaceInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Necklace::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pNecklaceInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t Necklace::getDefenseBonus() const 
	
{
	__BEGIN_TRY

	return g_pNecklaceInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t Necklace::getProtectionBonus() const
	
{
	__BEGIN_TRY

	return g_pNecklaceInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string NecklaceInfo::toString() const 
	
{
	StringStream msg;

	msg << "NecklaceInfo("
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
void NecklaceInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM NecklaceInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM NecklaceInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			NecklaceInfo* pNecklaceInfo = new NecklaceInfo();

			pNecklaceInfo->setItemType(pResult->getInt(++i));
			pNecklaceInfo->setName(pResult->getString(++i));
			pNecklaceInfo->setEName(pResult->getString(++i));
			pNecklaceInfo->setPrice(pResult->getInt(++i));
			pNecklaceInfo->setVolumeType(pResult->getInt(++i));
			pNecklaceInfo->setWeight(pResult->getInt(++i));
			pNecklaceInfo->setRatio(pResult->getInt(++i));
			pNecklaceInfo->setDurability(pResult->getInt(++i));
			pNecklaceInfo->setDefenseBonus(pResult->getInt(++i));
			pNecklaceInfo->setProtectionBonus(pResult->getInt(++i));
			pNecklaceInfo->setReqAbility(pResult->getString(++i));
			pNecklaceInfo->setItemLevel(pResult->getInt(++i));
			pNecklaceInfo->setDefaultOptions(pResult->getString(++i));
			pNecklaceInfo->setUpgradeRatio(pResult->getInt(++i));
			pNecklaceInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pNecklaceInfo->setNextOptionRatio(pResult->getInt(++i));
			pNecklaceInfo->setNextItemType(pResult->getInt(++i));
			pNecklaceInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pNecklaceInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void NecklaceLoader::load(Creature* pCreature) 
	
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
			<< "OptionType, Durability, EnchantLevel FROM NecklaceObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQueryString(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM NecklaceObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				Necklace* pNecklace = new Necklace();

				pNecklace->setItemID(pResult->getDWORD(++i));
				pNecklace->setObjectID(pResult->getDWORD(++i));
				pNecklace->setItemType(pResult->getDWORD(++i));
	
				if (g_pNecklaceInfoManager->getItemInfo(pNecklace->getItemType())->isUnique())
					pNecklace->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pNecklace->setOptionType(optionTypes);

				pNecklace->setDurability(pResult->getInt(++i));
				pNecklace->setGrade(pResult->getInt(++i));
				pNecklace->setEnchantLevel(pResult->getInt(++i));
				pNecklace->setCreateType((Item::CreateType)pResult->getInt(++i));

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
						if (pInventory->canAddingEx(x, y, pNecklace))
						{
							pInventory->addItemEx(x, y, pNecklace);
						}
						else
						{
							processItemBugEx(pCreature, pNecklace);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pNecklace);
							}
							else
							{
								processItemBugEx(pCreature, pNecklace);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pNecklace);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pNecklace);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pNecklace);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pNecklace);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pNecklace);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pNecklace);
						}
						else pStash->insert(x, y, pNecklace);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pNecklace);
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
void NecklaceLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM NecklaceObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQueryString(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Necklace* pNecklace = new Necklace();

			pNecklace->setItemID(pResult->getInt(++i));
			pNecklace->setObjectID(pResult->getInt(++i));
			pNecklace->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pNecklace->setOptionType(optionTypes);

			pNecklace->setDurability(pResult->getInt(++i));
			pNecklace->setEnchantLevel(pResult->getInt(++i));
			pNecklace->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pNecklace);
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
void NecklaceLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

NecklaceLoader* g_pNecklaceLoader = NULL;
