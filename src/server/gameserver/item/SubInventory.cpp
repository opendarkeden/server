//////////////////////////////////////////////////////////////////////////////
// Filename    : SubInventory.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SubInventory.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "Utility.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"

SubInventoryInfoManager* g_pSubInventoryInfoManager = NULL;

ItemID_t SubInventory::m_ItemIDRegistry = 0;
Mutex    SubInventory::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class SubInventory member methods
//////////////////////////////////////////////////////////////////////////////

SubInventory::SubInventory()
	throw()
{
	m_ItemType = 0;
	m_pInventory = NULL;
}

SubInventory::SubInventory(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	m_ItemType = itemType;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "SubInventory::SubInventory() : Invalid item type or option type");
		throw("SubInventory::SubInventory() : Invalid item type or optionType");
	}

	SubInventoryInfo* pInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(itemType));
	m_pInventory = new Inventory(pInfo->getWidth(), pInfo->getHeight());
}

SubInventory::~SubInventory() { SAFE_DELETE(m_pInventory); }

void SubInventory::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

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

		sql << "INSERT INTO SubInventoryObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SubInventory::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SubInventoryObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void SubInventory::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;

		sql << "UPDATE SubInventoryObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SubInventoryObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string SubInventory::toString() const 
	throw()
{
	StringStream msg;

	msg << "SubInventory("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ")";

	return msg.toString();
}

VolumeWidth_t SubInventory::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t SubInventory::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
		
Weight_t SubInventory::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

void SubInventory::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);
	result.setEnchantLevel(m_pInventory->getItemNum());
}

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfo member methods
//////////////////////////////////////////////////////////////////////////////

string SubInventoryInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "SubInventoryInfo("
		<< "ItemType:"     <<(int)m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       <<(int)m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      <<(int)m_Weight
		<< ",Description:" << m_Description
		<< ")";
	return msg.toString();
}

void SubInventoryInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SubInventoryInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Width, Height FROM SubInventoryInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SubInventoryInfo* pSubInventoryInfo = new SubInventoryInfo();

			pSubInventoryInfo->setItemType(pResult->getInt(++i));
			pSubInventoryInfo->setName(pResult->getString(++i));
			pSubInventoryInfo->setEName(pResult->getString(++i));
			pSubInventoryInfo->setPrice(pResult->getInt(++i));
			pSubInventoryInfo->setVolumeType(pResult->getInt(++i));
			pSubInventoryInfo->setWeight(pResult->getInt(++i));
			pSubInventoryInfo->setRatio(pResult->getInt(++i));
			pSubInventoryInfo->setWidth(pResult->getInt(++i));
			pSubInventoryInfo->setHeight(pResult->getInt(++i));

			addItemInfo(pSubInventoryInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryLoader member methods
//////////////////////////////////////////////////////////////////////////////

void SubInventoryLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y FROM SubInventoryObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM SubInventoryObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				SubInventory* pSubInventory = new SubInventory();

				pSubInventory->setItemID(pResult->getDWORD(++i));
				pSubInventory->setObjectID(pResult->getDWORD(++i));
				pSubInventory->setItemType(pResult->getDWORD(++i));

				SubInventoryInfo* pInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(pSubInventory->getItemType()));
				pSubInventory->setInventory(new Inventory(pInfo->getWidth(), pInfo->getHeight() ));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pSubInventory->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*    pOusters        = NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
				Item*       pItem           = NULL;
				Stash*      pStash          = NULL;
				Belt*       pBelt           = NULL;
				Inventory*  pBeltInventory  = NULL;

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
							processItemBugEx(pCreature, pSubInventory);
							break;
						}

						if (pInventory->canAddingEx(x, y, pSubInventory))
						{
							pInventory->addItemEx(x, y, pSubInventory);
						}
						else
						{
							processItemBugEx(pCreature, pSubInventory);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pSubInventory);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pSubInventory);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSubInventory);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSubInventory);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pSubInventory);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pSubInventory);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pSubInventory);
						}
						else pStash->insert(x, y, pSubInventory);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pSubInventory);
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

void SubInventoryLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM SubInventoryObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			SubInventory* pSubInventory = new SubInventory();

			pSubInventory->setItemID(pResult->getInt(++i));
			pSubInventory->setObjectID(pResult->getInt(++i));
			pSubInventory->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pSubInventory->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pSubInventory);
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

void SubInventoryLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

SubInventoryLoader* g_pSubInventoryLoader = NULL;
