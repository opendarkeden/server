//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersChakram.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

// include files
#include "OustersChakram.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
OustersChakramInfoManager* g_pOustersChakramInfoManager = NULL;

ItemID_t OustersChakram::m_ItemIDRegistry = 0;
Mutex    OustersChakram::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
OustersChakram::OustersChakram()
	
{
	setItemType(0);
	setDurability(0);
	setBonusDamage(0);
}

OustersChakram::OustersChakram(ItemType_t itemType, const list<OptionType_t>& optionType)
	
//: m_OptionType( optionType )
{
	setItemType(itemType);
	setOptionType(optionType);

	//m_EnchantLevel = 0;
	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "OustersChakram::OustersChakram() : Invalid item type or option type");
		throw ("OustersChakram::OustersChakram() : Invalid item type or optionType");
	}
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void OustersChakram::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		sql << "INSERT INTO OustersChakramObject "
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
void OustersChakram::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE OustersChakramObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void OustersChakram::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE OustersChakramObject SET "
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
		pStmt->executeQuery("UPDATE OustersChakramObject SET ObjectID=%ld, ItemType=%d, OwnerID= '%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Durability=%d, Grade=%d, EnchantLevel=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(), m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string OustersChakram::toString() const 
	
{
	StringStream msg;

	msg << "OustersChakram("
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
VolumeWidth_t OustersChakram::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t OustersChakram::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t OustersChakram::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's minDamage
//--------------------------------------------------------------------------------
Damage_t OustersChakram::getMinDamage() const 
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getMinDamage() + m_BonusDamage;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set weapon's maxDamage
//--------------------------------------------------------------------------------
Damage_t OustersChakram::getMaxDamage() const 
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getMaxDamage() + m_BonusDamage;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int OustersChakram::getCriticalBonus(void) const
	
{
	__BEGIN_TRY

	return g_pOustersChakramInfoManager->getItemInfo(m_ItemType)->getCriticalBonus();

	__END_CATCH
}

*/
//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string OustersChakramInfo::toString() const 
	
{
	StringStream msg;

	msg << "OustersChakramInfo("
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
void OustersChakramInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM OustersChakramInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType,Name,EName,Price,Volume,Weight,Ratio,Durability,minDamage,maxDamage,Speed,ReqAbility,ItemLevel, CriticalBonus, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM OustersChakramInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			OustersChakramInfo* pOustersChakramInfo = new OustersChakramInfo();

			pOustersChakramInfo->setItemType(pResult->getInt(++i));
			pOustersChakramInfo->setName(pResult->getString(++i));
			pOustersChakramInfo->setEName(pResult->getString(++i));
			pOustersChakramInfo->setPrice(pResult->getInt(++i));
			pOustersChakramInfo->setVolumeType(pResult->getInt(++i));
			pOustersChakramInfo->setWeight(pResult->getInt(++i));
			pOustersChakramInfo->setRatio(pResult->getInt(++i));
			pOustersChakramInfo->setDurability(pResult->getInt(++i));
			pOustersChakramInfo->setMinDamage(pResult->getInt(++i));
			pOustersChakramInfo->setMaxDamage(pResult->getInt(++i));
			pOustersChakramInfo->setSpeed(pResult->getInt(++i));
			pOustersChakramInfo->setReqAbility(pResult->getString(++i));
			pOustersChakramInfo->setItemLevel(pResult->getInt(++i));
			pOustersChakramInfo->setCriticalBonus(pResult->getInt(++i));
			pOustersChakramInfo->setDefaultOptions(pResult->getString(++i));
			pOustersChakramInfo->setUpgradeRatio(pResult->getInt(++i));
			pOustersChakramInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pOustersChakramInfo->setNextOptionRatio(pResult->getInt(++i));
			pOustersChakramInfo->setNextItemType(pResult->getInt(++i));
			pOustersChakramInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pOustersChakramInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void OustersChakramLoader::load(Creature* pCreature) 
	
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
			<< " OptionType, Durability, EnchantLevel FROM OustersChakramObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQueryString(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, Grade, EnchantLevel, ItemFlag FROM OustersChakramObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
													pCreature->getName().c_str());


		while (pResult->next())
		{
			try {
				uint i = 0;

				OustersChakram* pOustersChakram = new OustersChakram();

				pOustersChakram->setItemID(pResult->getDWORD(++i));
				pOustersChakram->setObjectID(pResult->getDWORD(++i));
				pOustersChakram->setItemType(pResult->getDWORD(++i));
	
				if (g_pOustersChakramInfoManager->getItemInfo(pOustersChakram->getItemType())->isUnique())
					pOustersChakram->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pOustersChakram->setOptionType(optionTypes);

				pOustersChakram->setDurability(pResult->getInt(++i));
				pOustersChakram->setGrade(pResult->getInt(++i));
				pOustersChakram->setEnchantLevel(pResult->getInt(++i));
				pOustersChakram->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*    pOusters        = NULL;
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
				else if (pCreature->isOusters())
				{
					pOusters   = dynamic_cast<Ousters*>(pCreature);
					pInventory = pOusters->getInventory();
					pStash     = pOusters->getStash();
				}
				else throw UnsupportedError("Monster,NPC �κ��丮�� ������ ���� �������� �ʽ��ϴ�.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pOustersChakram))
						{
							pInventory->addItemEx(x, y, pOustersChakram);
						}
						else
						{
							processItemBugEx(pCreature, pOustersChakram);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer() || pCreature->isVampire())
						{
							processItemBugEx(pCreature, pOustersChakram);
						}
						else if (pCreature->isOusters())
						{
							if (!pOusters->isWear((Ousters::WearPart)x))
							{
								pOusters->wearItem((Ousters::WearPart)x, pOustersChakram);
							}
							else
							{
								processItemBugEx(pCreature, pOustersChakram);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pOustersChakram);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pOustersChakram);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pOustersChakram);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pOustersChakram);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pOustersChakram);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pOustersChakram);
						}
						else
						{
							pStash->insert(x, y, pOustersChakram);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pOustersChakram);
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
void OustersChakramLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM OustersChakramObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQueryString(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			OustersChakram* pOustersChakram = new OustersChakram();

			pOustersChakram->setItemID(pResult->getInt(++i));
			pOustersChakram->setObjectID(pResult->getInt(++i));
			pOustersChakram->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pOustersChakram->setOptionType(optionTypes);

			pOustersChakram->setDurability(pResult->getInt(++i));
			pOustersChakram->setEnchantLevel(pResult->getInt(++i));
			pOustersChakram->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pOustersChakram);
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
void OustersChakramLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

OustersChakramLoader* g_pOustersChakramLoader = NULL;
