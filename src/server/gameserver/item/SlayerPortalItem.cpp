//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerPortalItem.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SlayerPortalItem.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "SubInventory.h"

ItemID_t SlayerPortalItem::m_ItemIDRegistry = 0;
Mutex    SlayerPortalItem::m_Mutex;

SlayerPortalItemInfoManager* g_pSlayerPortalItemInfoManager = NULL;
SlayerPortalItemLoader*      g_pSlayerPortalItemLoader = NULL;

//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItem member methods
//////////////////////////////////////////////////////////////////////////////

SlayerPortalItem::SlayerPortalItem()
	throw()
{
	m_ItemType = 0;
	m_Charge   = 0;
}

SlayerPortalItem::SlayerPortalItem(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	m_ItemType = itemType;
	m_Charge   = getMaxCharge();

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "SlayerPortalItem::SlayerPortalItem() : Invalid item type or option type");
		throw("SlayerPortalItem::SlayerPortalItem() : Invalid item type or optionType");
	}
}

void SlayerPortalItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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
		StringStream sql;
		sql << "INSERT INTO SlayerPortalItemObject "
			<< "(ItemID,ObjectID,ItemType,OwnerID, Storage,StorageID,X,Y, Charge) VALUES (" 
			<< m_ItemID << "," << m_ObjectID << "," << m_ItemType << ",'" << ownerID << "'," 
			<< (int)storage << "," << storageID << "," << (int)x << "," << (int)y << ","
			<< m_Charge
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
void SlayerPortalItem::tinysave(const char* field) const 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SlayerPortalItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void SlayerPortalItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;
		sql << "UPDATE SlayerPortalItemObject SET "
			<< "ObjectID   = "  << m_ObjectID
			<< ",ItemType  = "  << m_ItemType
			<< ",OwnerID   = '" << ownerID << "'"
			<< ",Storage   = "  <<(int)storage
			<< ",StorageID = "  << storageID
			<< ",X         = "  <<(int)x
			<< ",Y         = "  <<(int)y
			<< ",Charge    = "  << m_Charge
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE SlayerPortalItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Charge=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Charge, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VolumeWidth_t SlayerPortalItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSlayerPortalItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t SlayerPortalItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSlayerPortalItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t SlayerPortalItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSlayerPortalItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

string SlayerPortalItem::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SlayerPortalItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ",Charge:" << m_Charge
		<< ")";

	return msg.toString();

	__END_CATCH
}

int SlayerPortalItem::getMaxCharge(void) const
	throw()
{
	__BEGIN_TRY

	SlayerPortalItemInfo* pInfo = dynamic_cast<SlayerPortalItemInfo*>(g_pSlayerPortalItemInfoManager->getItemInfo(m_ItemType));
	Assert(pInfo != NULL);
	return pInfo->getMaxCharge();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

void SlayerPortalItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SlayerPortalItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, MaxCharge, ReqAbility FROM SlayerPortalItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SlayerPortalItemInfo* pSlayerPortalItemInfo = new SlayerPortalItemInfo();
			pSlayerPortalItemInfo->setItemType(pResult->getInt(++i));
			pSlayerPortalItemInfo->setName(pResult->getString(++i));
			pSlayerPortalItemInfo->setEName(pResult->getString(++i));
			pSlayerPortalItemInfo->setPrice(pResult->getInt(++i));
			pSlayerPortalItemInfo->setVolumeType(pResult->getInt(++i));
			pSlayerPortalItemInfo->setWeight(pResult->getInt(++i));
			pSlayerPortalItemInfo->setRatio(pResult->getInt(++i));
			pSlayerPortalItemInfo->setMaxCharge(pResult->getInt(++i));
			pSlayerPortalItemInfo->setReqAbility(pResult->getString(++i));

			addItemInfo(pSlayerPortalItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string SlayerPortalItemInfo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SlayerPortalItemInfo("
		<< "ItemType:"     << m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       << m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      << m_Weight
		<< ",MaxCharge:"   << m_MaxCharge
		<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void SlayerPortalItemLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB 
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM SlayerPortalItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<< (int)STORAGE_INVENTORY << "," << (int)STORAGE_GEAR       << "," <<(int)STORAGE_BELT << "," 
			<< (int)STORAGE_EXTRASLOT << "," << (int)STORAGE_MOTORCYCLE << "," <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		pResult = pStmt->executeQuery(sql.toString());
		*/

		pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM SlayerPortalItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				ItemID_t     itemID    = pResult->getDWORD(++i);
				ObjectID_t   objectID  = pResult->getDWORD(++i);
				ItemType_t   itemType  = pResult->getDWORD(++i);
				Storage      storage   = (Storage)pResult->getInt(++i);
				StorageID_t  storageID = pResult->getDWORD(++i);
				BYTE         x         = pResult->getBYTE(++i);
				BYTE         y         = pResult->getBYTE(++i);
				int          charge    = pResult->getInt(++i);

				SlayerPortalItem* pSlayerPortalItem = new SlayerPortalItem();
				pSlayerPortalItem->setItemID(itemID);
				pSlayerPortalItem->setObjectID(objectID);
				pSlayerPortalItem->setItemType(itemType);
				pSlayerPortalItem->setCharge(charge);

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

					if (pMotorcycle != NULL) pMotorInventory = pMotorcycle->getInventory();
				}
				else if (pCreature->isVampire()) 
				{
					pVampire   = dynamic_cast<Vampire*>(pCreature);
					pInventory = pVampire->getInventory();
					pStash     = pVampire->getStash();
				}
				else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

				if (storage == STORAGE_INVENTORY)
				{
					if (storageID != 0 )
					{
						SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
						if (pInventoryItem == NULL )
						{
							processItemBugEx(pCreature, pSlayerPortalItem);
							break;
						}

						pInventory = pInventoryItem->getInventory();
					}

					if (pInventory->canAddingEx(x, y, pSlayerPortalItem))
					{
						pInventory->addItemEx(x, y, pSlayerPortalItem);
					}
					else
					{
						processItemBugEx(pCreature, pSlayerPortalItem);
					}
				}
				else if (storage == STORAGE_GEAR)
				{
					processItemBugEx(pCreature, pSlayerPortalItem);
				}
				else if (storage == STORAGE_BELT)
				{
					processItemBugEx(pCreature, pSlayerPortalItem);
				}
				else if (storage == STORAGE_EXTRASLOT)
				{
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSlayerPortalItem);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSlayerPortalItem);
				}
				else if (storage == STORAGE_MOTORCYCLE)
				{
					processItemBugEx(pCreature, pSlayerPortalItem);
				}
				else if (storage == STORAGE_STASH)
				{
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pSlayerPortalItem);
					}
					else pStash->insert(x, y, pSlayerPortalItem);
				}
				else if (storage == STORAGE_GARBAGE)
				{
					processItemBug(pCreature, pSlayerPortalItem);
				}
				else
				{
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

void SlayerPortalItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		StringStream sql;
		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM SlayerPortalItemObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			ItemID_t     itemID    = pResult->getDWORD(++i);
			ObjectID_t   objectID  = pResult->getDWORD(++i);
			ItemType_t   itemType  = pResult->getDWORD(++i);
			Storage      storage   = (Storage)pResult->getInt(++i);
			StorageID_t  storageID = pResult->getDWORD(++i);
			BYTE         x         = pResult->getBYTE(++i);
			BYTE         y         = pResult->getBYTE(++i);
			int          charge    = pResult->getInt(++i);

			SlayerPortalItem* pSlayerPortalItem = new SlayerPortalItem();
			pSlayerPortalItem->setItemID(itemID);
			pSlayerPortalItem->setObjectID(objectID);
			pSlayerPortalItem->setItemType(itemType);
			pSlayerPortalItem->setCharge(charge);

			if (storage == STORAGE_ZONE)
			{
				Tile & pTile = pZone->getTile(x,y);
				Assert(!pTile.hasItem());
				pTile.addItem(pSlayerPortalItem);
			}
			else
			{
				throw Error("Storage must be STORAGE_ZONE");
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void SlayerPortalItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

