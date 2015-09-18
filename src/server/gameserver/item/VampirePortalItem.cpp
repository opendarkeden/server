//////////////////////////////////////////////////////////////////////////////
// Filename    : VampirePortalItem.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "VampirePortalItem.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"

#include "skill/EffectVampirePortal.h"
#include "SubInventory.h"

ItemID_t VampirePortalItem::m_ItemIDRegistry = 0;
Mutex    VampirePortalItem::m_Mutex;

VampirePortalItemInfoManager* g_pVampirePortalItemInfoManager = NULL;
VampirePortalItemLoader*      g_pVampirePortalItemLoader = NULL;

//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItem member methods
//////////////////////////////////////////////////////////////////////////////

VampirePortalItem::VampirePortalItem()
	throw()
{
	__BEGIN_TRY

	m_ItemType                = 0;
	m_Charge                  = 0;
	m_ZoneID                  = 0;
	m_X                       = 0;
	m_Y                       = 0;
	//m_pEffectVampirePortal[0] = NULL;
	//m_pEffectVampirePortal[1] = NULL;

	__END_CATCH
}

VampirePortalItem::VampirePortalItem(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	__BEGIN_TRY

	m_ItemType = itemType;
	m_Charge   = getMaxCharge();

	switch (m_ItemType)
	{
		case 3:
		case 4:
		case 5:
			m_ZoneID = 1003;
			m_X = 50;
			m_Y = 70;
			break;
		case 6:
		case 7:
		case 8:
			m_ZoneID = 1007;
			m_X = 62;
			m_Y = 65;
			break;
		case 9:
		case 10:
		case 11:
			m_ZoneID = 61;
			m_X = 102;
			m_Y = 220;
			break;
		default:
			m_ZoneID = 0;
			m_X = 0;
			m_Y = 0;
			break;
	}

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "VampirePortalItem::VampirePortalItem() : Invalid item type or option type");
		throw("VampirePortalItem::VampirePortalItem() : Invalid item type or optionType");
	}

	//m_pEffectVampirePortal[0] = NULL;
	//m_pEffectVampirePortal[1] = NULL;

	__END_CATCH
}

VampirePortalItem::~VampirePortalItem()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void VampirePortalItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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
		sql << "INSERT INTO VampirePortalItemObject "
			<< "(ItemID,ObjectID,ItemType,OwnerID, Storage,StorageID,X,Y, Charge,TargetZID,TargetX,TargetY) VALUES (" 
			<< m_ItemID << "," << m_ObjectID << "," << m_ItemType << ",'" << ownerID << "'," 
			<< (int)storage << "," << storageID << "," << (int)x << "," << (int)y << ","
			<< m_Charge << "," << (int)m_ZoneID << "," << (int)m_X << "," << (int)m_Y
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
void VampirePortalItem::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE VampirePortalItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void VampirePortalItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;
		sql << "UPDATE VampirePortalItemObject SET "
			<< "ObjectID   = "  << m_ObjectID
			<< ",ItemType  = "  << m_ItemType
			<< ",OwnerID   = '" << ownerID << "'"
			<< ",Storage   = "  <<(int)storage
			<< ",StorageID = "  << storageID
			<< ",X         = "  <<(int)x
			<< ",Y         = "  <<(int)y
			<< ",Charge    = "  << m_Charge
			<< ",TargetZID = "  << (int)m_ZoneID
			<< ",TargetX   = "  << (int)m_X
			<< ",TargetY   = "  << (int)m_Y
			<< " WHERE ItemID = " << m_ItemID;
		pStmt->executeQuery(sql.toString());
		*/
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE VampirePortalItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Charge=%d, TargetZID=%d, TargetX=%d, TargetY=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Charge, (int)m_ZoneID, (int)m_X, (int)m_Y, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VolumeWidth_t VampirePortalItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampirePortalItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t VampirePortalItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampirePortalItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t VampirePortalItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampirePortalItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

string VampirePortalItem::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "VampirePortalItem("
		<< "ItemID:"     << m_ItemID
		<< ",ItemType:"  <<(int)m_ItemType
		<< ",Charge:"    << m_Charge
		<< ",TargetZID:" << (int)m_ZoneID
		<< ",TargetX:"   << (int)m_X
		<< ",TargetY:"   << (int)m_Y
		<< ")";

	return msg.toString();

	__END_CATCH
}

int VampirePortalItem::getMaxCharge(void) const
	throw()
{
	__BEGIN_TRY

	VampirePortalItemInfo* pInfo = dynamic_cast<VampirePortalItemInfo*>(g_pVampirePortalItemInfoManager->getItemInfo(m_ItemType));
	Assert(pInfo != NULL);
	return pInfo->getMaxCharge();

	__END_CATCH
}

Durability_t VampirePortalItem::getDurability() const 
	throw(Error)
{
	__BEGIN_TRY

	WORD highBits = m_X << 8;
	WORD lowBits  = m_Y;
	return (WORD)(highBits | lowBits);

	__END_CATCH
}

Silver_t VampirePortalItem::getSilver() const 
	throw() 
{ 
	__BEGIN_TRY

	return m_ZoneID; 

	__END_CATCH
}

EnchantLevel_t VampirePortalItem::getEnchantLevel() const 
	throw() 
{ 
	__BEGIN_TRY

	return m_Charge; 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

void VampirePortalItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampirePortalItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, MaxCharge, ReqAbility FROM VampirePortalItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampirePortalItemInfo* pVampirePortalItemInfo = new VampirePortalItemInfo();
			pVampirePortalItemInfo->setItemType(pResult->getInt(++i));
			pVampirePortalItemInfo->setName(pResult->getString(++i));
			pVampirePortalItemInfo->setEName(pResult->getString(++i));
			pVampirePortalItemInfo->setPrice(pResult->getInt(++i));
			pVampirePortalItemInfo->setVolumeType(pResult->getInt(++i));
			pVampirePortalItemInfo->setWeight(pResult->getInt(++i));
			pVampirePortalItemInfo->setRatio(pResult->getInt(++i));
			pVampirePortalItemInfo->setMaxCharge(pResult->getInt(++i));
			pVampirePortalItemInfo->setReqAbility(pResult->getString(++i));

			addItemInfo(pVampirePortalItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string VampirePortalItemInfo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "VampirePortalItemInfo("
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
// class VampirePortalItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void VampirePortalItemLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge, TargetZID, TargetX, TargetY FROM VampirePortalItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<< (int)STORAGE_INVENTORY << "," << (int)STORAGE_GEAR       << "," <<(int)STORAGE_BELT << "," 
			<< (int)STORAGE_EXTRASLOT << "," << (int)STORAGE_MOTORCYCLE << "," <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		pResult = pStmt->executeQuery(sql.toString());
		*/

		pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge, TargetZID, TargetX, TargetY FROM VampirePortalItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
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
				ZoneID_t     TargetZID = pResult->getWORD(++i);
				ZoneCoord_t  TargetX   = pResult->getWORD(++i);
				ZoneCoord_t  TargetY   = pResult->getWORD(++i);

				VampirePortalItem* pVampirePortalItem = new VampirePortalItem();
				pVampirePortalItem->setItemID(itemID);
				pVampirePortalItem->setObjectID(objectID);
				pVampirePortalItem->setItemType(itemType);
				pVampirePortalItem->setCharge(charge);
				pVampirePortalItem->setZoneID(TargetZID);
				pVampirePortalItem->setX(TargetX);
				pVampirePortalItem->setY(TargetY);

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
							processItemBugEx(pCreature, pVampirePortalItem);
							break;
						}

						pInventory = pInventoryItem->getInventory();
					}

					if (pInventory->canAddingEx(x, y, pVampirePortalItem))
					{
						pInventory->addItemEx(x, y, pVampirePortalItem);
					}
					else
					{
						processItemBugEx(pCreature, pVampirePortalItem);
					}
				}
				else if (storage == STORAGE_GEAR)
				{
					processItemBugEx(pCreature, pVampirePortalItem);
				}
				else if (storage == STORAGE_BELT)
				{
					processItemBugEx(pCreature, pVampirePortalItem);
				}
				else if (storage == STORAGE_EXTRASLOT)
				{
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampirePortalItem);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampirePortalItem);
				}
				else if (storage == STORAGE_MOTORCYCLE)
				{
					processItemBugEx(pCreature, pVampirePortalItem);
				}
				else if (storage == STORAGE_STASH)
				{
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pVampirePortalItem);
					}
					else pStash->insert(x, y, pVampirePortalItem);
				}
				else if (storage == STORAGE_GARBAGE)
				{
					processItemBug(pCreature, pVampirePortalItem);
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

void VampirePortalItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB 
	{
		StringStream sql;
		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Charge FROM VampirePortalItemObject"
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
			ZoneID_t     TargetZID = pResult->getWORD(++i);
			ZoneCoord_t  TargetX   = pResult->getWORD(++i);
			ZoneCoord_t  TargetY   = pResult->getWORD(++i);

			VampirePortalItem* pVampirePortalItem = new VampirePortalItem();
			pVampirePortalItem->setItemID(itemID);
			pVampirePortalItem->setObjectID(objectID);
			pVampirePortalItem->setItemType(itemType);
			pVampirePortalItem->setCharge(charge);
			pVampirePortalItem->setZoneID(TargetZID);
			pVampirePortalItem->setX(TargetX);
			pVampirePortalItem->setY(TargetY);

			if (storage == STORAGE_ZONE)
			{
				Tile & pTile = pZone->getTile(x,y);
				Assert(!pTile.hasItem());
				pTile.addItem(pVampirePortalItem);
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

void VampirePortalItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

