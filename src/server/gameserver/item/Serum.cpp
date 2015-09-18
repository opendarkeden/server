//////////////////////////////////////////////////////////////////////////////
// Filename    : Serum.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Serum.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "SubInventory.h"

SerumInfoManager* g_pSerumInfoManager = NULL;

ItemID_t Serum::m_ItemIDRegistry = 0;
Mutex    Serum::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Serum::Serum()
	throw()
{
	m_ItemType = 0;
	m_Num = 1;
}

Serum::Serum(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	m_ItemType = itemType;
	m_Num = 1;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "Serum::Serum() : Invalid item type or option type");
		throw("Serum::Serum() : Invalid item type or optionType");
	}
}


//////////////////////////////////////////////////////////////////////////////
// create item
//////////////////////////////////////////////////////////////////////////////
void Serum::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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
		StringStream sql;
		sql << "INSERT INTO SerumObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num) VALUES (" 
			<< m_ItemID << "," << m_ObjectID << "," 
			<< m_ItemType << ",'" << ownerID << "'," 
			<< (int)storage << ", " << storageID << ", " 
			<< (int)x << "," << (int)y << "," << (int)m_Num
			<< ")";

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Serum::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SerumObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// save item
//////////////////////////////////////////////////////////////////////////////
void Serum::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE SerumObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",Num = " << (int)m_Num
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery("UPDATE SerumObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)m_Num, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string Serum::toString() const 
	throw()
{
	StringStream msg;
	msg << "Serum("
		<< "ItemID:"	<< m_ItemID
		<< ",ItemType:"	<<(int)m_ItemType
		<< ",Num:"		<< (int)m_Num
		<< ")";
	return msg.toString();
}


//////////////////////////////////////////////////////////////////////////////
// get width
//////////////////////////////////////////////////////////////////////////////
VolumeWidth_t Serum::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSerumInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// get height
//////////////////////////////////////////////////////////////////////////////
VolumeHeight_t Serum::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSerumInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// get weight
//////////////////////////////////////////////////////////////////////////////
Weight_t Serum::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSerumInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

int Serum::getHPAmount(void) const 
	throw()
{
	SerumInfo* pInfo = dynamic_cast<SerumInfo*>(g_pSerumInfoManager->getItemInfo(m_ItemType));
	return pInfo->getHPAmount();
}

int Serum::getPeriod(void) const 
	throw()
{
	SerumInfo* pInfo = dynamic_cast<SerumInfo*>(g_pSerumInfoManager->getItemInfo(m_ItemType));
	return pInfo->getPeriod();
}

int Serum::getCount(void) const 
	throw()
{
	SerumInfo* pInfo = dynamic_cast<SerumInfo*>(g_pSerumInfoManager->getItemInfo(m_ItemType));
	return pInfo->getCount();
}




//////////////////////////////////////////////////////////////////////////////
// parse effect string
//////////////////////////////////////////////////////////////////////////////
void SerumInfo::parseEffect(const string& effect)
	throw()
{
	__BEGIN_TRY

	m_HPAmount = 0;
	m_Period   = 0;
	m_Count    = 0;

    size_t a = 0, b = 0, c = 0, d = 0;

	while (d < effect.size() - 1)
	{
		a = effect.find_first_of('(', d);
		b = effect.find_first_of(',', a+1);
		c = effect.find_first_of(',', b+1);
		d = effect.find_first_of(')', c+1);

		if (a > b || b > c || c > d) break;

		string hpamount = trim(effect.substr(a+1, b-a-1));
		string period   = trim(effect.substr(b+1, c-b-1));
		string count    = trim(effect.substr(c+1, d-c-1));

		m_HPAmount = atoi(hpamount.c_str());
		m_Period   = atoi(period.c_str());
		m_Count    = atoi(count.c_str());
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string SerumInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "SerumInfo("
		<< "ItemType:"     << m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       << m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      << m_Weight
		<< ",Description:" << m_Description
		<< ",HPAmount:"    << m_HPAmount
		<< ",Period:"      << m_Period
		<< ",Count:"       << m_Count
		<< ")";
	return msg.toString();
}


//////////////////////////////////////////////////////////////////////////////
// load from DB
//////////////////////////////////////////////////////////////////////////////
void SerumInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SerumInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, SerumEffect FROM SerumInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SerumInfo* pSerumInfo = new SerumInfo();

			pSerumInfo->setItemType(pResult->getInt(++i));
			pSerumInfo->setName(pResult->getString(++i));
			pSerumInfo->setEName(pResult->getString(++i));
			pSerumInfo->setPrice(pResult->getInt(++i));
			pSerumInfo->setVolumeType(pResult->getInt(++i));
			pSerumInfo->setWeight(pResult->getInt(++i));
			pSerumInfo->setRatio(pResult->getInt(++i));
			pSerumInfo->parseEffect(pResult->getString(++i));

			addItemInfo(pSerumInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// load to creature
//////////////////////////////////////////////////////////////////////////////
void SerumLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM SerumObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM SerumObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				Serum* pSerum = new Serum();

				pSerum->setItemID(pResult->getDWORD(++i));
				pSerum->setObjectID(pResult->getDWORD(++i));
				pSerum->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pSerum->setNum(pResult->getBYTE(++i));

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
								processItemBugEx(pCreature, pSerum);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pSerum))
						{
							pInventory->addItemEx(x, y, pSerum);
						}
						else
						{
							processItemBugEx(pCreature, pSerum);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pSerum);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pSerum);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSerum);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSerum);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pSerum);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pSerum);
						}
						else pStash->insert(x, y, pSerum);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pSerum);
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


//////////////////////////////////////////////////////////////////////////////
// load to zone
//////////////////////////////////////////////////////////////////////////////
void SerumLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM SerumObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Serum* pSerum = new Serum();

			pSerum->setItemID(pResult->getInt(++i));
			pSerum->setObjectID(pResult->getInt(++i));
			pSerum->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pSerum->setNum(pResult->getBYTE(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pSerum);
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


//////////////////////////////////////////////////////////////////////////////
// load to inventory
//////////////////////////////////////////////////////////////////////////////
void SerumLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

SerumLoader* g_pSerumLoader = NULL;
