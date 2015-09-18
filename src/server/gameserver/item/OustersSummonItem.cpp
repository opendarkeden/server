//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersSummonItem.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "OustersSummonItem.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "SubInventory.h"

ItemID_t OustersSummonItem::m_ItemIDRegistry = 0;
Mutex    OustersSummonItem::m_Mutex;

OustersSummonItemInfoManager* g_pOustersSummonItemInfoManager = NULL;
OustersSummonItemLoader*      g_pOustersSummonItemLoader = NULL;

//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItem member methods
//////////////////////////////////////////////////////////////////////////////

OustersSummonItem::OustersSummonItem()
	throw()
{
	m_ItemType = 0;
	m_Charge   = 0;
}

OustersSummonItem::OustersSummonItem(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	m_ItemType = itemType;
	m_Charge   = getMaxCharge();

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "OustersSummonItem::OustersSummonItem() : Invalid item type or option type");
		throw("OustersSummonItem::OustersSummonItem() : Invalid item type or optionType");
	}
}

void OustersSummonItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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
		sql << "INSERT INTO OustersSummonItemObject "
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
void OustersSummonItem::tinysave(const char* field) const 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE OustersSummonItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void OustersSummonItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;
		sql << "UPDATE OustersSummonItemObject SET "
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

		pStmt->executeQuery("UPDATE OustersSummonItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Charge=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Charge, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VolumeWidth_t OustersSummonItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersSummonItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t OustersSummonItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersSummonItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t OustersSummonItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersSummonItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

string OustersSummonItem::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "OustersSummonItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ",Charge:" << m_Charge
		<< ")";

	return msg.toString();

	__END_CATCH
}

int OustersSummonItem::getMaxCharge(void) const
	throw()
{
	__BEGIN_TRY

	OustersSummonItemInfo* pInfo = dynamic_cast<OustersSummonItemInfo*>(g_pOustersSummonItemInfoManager->getItemInfo(m_ItemType));
	Assert(pInfo != NULL);
	return pInfo->getMaxCharge();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

void OustersSummonItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM OustersSummonItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, MaxCharge, Effect FROM OustersSummonItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			OustersSummonItemInfo* pOustersSummonItemInfo = new OustersSummonItemInfo();
			pOustersSummonItemInfo->setItemType(pResult->getInt(++i));
			pOustersSummonItemInfo->setName(pResult->getString(++i));
			pOustersSummonItemInfo->setEName(pResult->getString(++i));
			pOustersSummonItemInfo->setPrice(pResult->getInt(++i));
			pOustersSummonItemInfo->setVolumeType(pResult->getInt(++i));
			pOustersSummonItemInfo->setWeight(pResult->getInt(++i));
			pOustersSummonItemInfo->setMaxCharge(pResult->getInt(++i));
			pOustersSummonItemInfo->setEffectID(pResult->getInt(++i));

			addItemInfo(pOustersSummonItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string OustersSummonItemInfo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "OustersSummonItemInfo("
		<< "ItemType:"     << m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       << m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      << m_Weight
		<< ",MaxCharge:"   << m_MaxCharge
		<< ",EffectID:"   << m_EffectID
		<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void OustersSummonItemLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM OustersSummonItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<< (int)STORAGE_INVENTORY << "," << (int)STORAGE_GEAR       << "," <<(int)STORAGE_BELT << "," 
			<< (int)STORAGE_EXTRASLOT << "," << (int)STORAGE_MOTORCYCLE << "," <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		pResult = pStmt->executeQuery(sql.toString());
		*/

		pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM OustersSummonItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
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

				OustersSummonItem* pOustersSummonItem = new OustersSummonItem();
				pOustersSummonItem->setItemID(itemID);
				pOustersSummonItem->setObjectID(objectID);
				pOustersSummonItem->setItemType(itemType);
				pOustersSummonItem->setCharge(charge);

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*	pOusters		= NULL;
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
				else if (pCreature->isOusters())
				{
					pOusters	= dynamic_cast<Ousters*>(pCreature);
					pInventory	= pOusters->getInventory();
					pStash		= pOusters->getStash();
				}
				else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

				if (storage == STORAGE_INVENTORY)
				{
					if (storageID != 0 )
					{
						SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
						if (pInventoryItem == NULL )
						{
							processItemBugEx(pCreature, pOustersSummonItem);
							break;
						}

						pInventory = pInventoryItem->getInventory();
					}

					if (pInventory->canAddingEx(x, y, pOustersSummonItem))
					{
						pInventory->addItemEx(x, y, pOustersSummonItem);
					}
					else
					{
						processItemBugEx(pCreature, pOustersSummonItem);
					}
				}
				else if (storage == STORAGE_GEAR)
				{
					processItemBugEx(pCreature, pOustersSummonItem);
				}
				else if (storage == STORAGE_BELT)
				{
					processItemBugEx(pCreature, pOustersSummonItem);
				}
				else if (storage == STORAGE_EXTRASLOT)
				{
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pOustersSummonItem);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pOustersSummonItem);
					else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pOustersSummonItem);
				}
				else if (storage == STORAGE_MOTORCYCLE)
				{
					processItemBugEx(pCreature, pOustersSummonItem);
				}
				else if (storage == STORAGE_STASH)
				{
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pOustersSummonItem);
					}
					else pStash->insert(x, y, pOustersSummonItem);
				}
				else if (storage == STORAGE_GARBAGE)
				{
					processItemBug(pCreature, pOustersSummonItem);
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

void OustersSummonItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		StringStream sql;
		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM OustersSummonItemObject"
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

			OustersSummonItem* pOustersSummonItem = new OustersSummonItem();
			pOustersSummonItem->setItemID(itemID);
			pOustersSummonItem->setObjectID(objectID);
			pOustersSummonItem->setItemType(itemType);
			pOustersSummonItem->setCharge(charge);

			if (storage == STORAGE_ZONE)
			{
				Tile & pTile = pZone->getTile(x,y);
				Assert(!pTile.hasItem());
				pTile.addItem(pOustersSummonItem);
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

void OustersSummonItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

