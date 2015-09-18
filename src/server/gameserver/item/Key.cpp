//////////////////////////////////////////////////////////////////////////////
// Filename    : Key.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Key.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"
#include "SubInventory.h"

// global variable declaration
KeyInfoManager* g_pKeyInfoManager = NULL;

ItemID_t Key::m_ItemIDRegistry = 0;
Mutex    Key::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Key::Key()
	throw()
: m_ItemType(0), m_Target(0)
{
}

Key::Key(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
: m_ItemType(itemType), m_Target(0)
{
	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "Key::Key() : Invalid item type or option type");
		throw("Key::Key() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Key::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO KeyObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Target)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " << m_Target << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}




//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Key::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE KeyObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Key::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE KeyObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",Target = " << m_Target
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery("UPDATE KeyObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Target=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Target, m_ItemID);
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

ItemID_t Key::setNewMotorcycle(Slayer* pSlayer) throw(Error)
{
	__BEGIN_TRY

	ItemID_t targetID = 0;

	// 타겟이 0이 아니라도 타겟이 없으면 새 모터사이클을 넣어야 된다.
//	Assert(getTarget() == 0);
	Assert(pSlayer != NULL);
	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	KeyInfo* pKeyInfo = dynamic_cast<KeyInfo*>(g_pItemInfoManager->getItemInfo(getItemClass(), getItemType() ));
	Assert(pKeyInfo != NULL);

	list<OptionType_t> option;
	ItemType_t motorcycleType = pKeyInfo->getTargetType();

	if (pKeyInfo->getOptionType() != 0 ) option.push_back(pKeyInfo->getOptionType());

	Item* pMotorcycle = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MOTORCYCLE, motorcycleType, option);
	Assert(pMotorcycle != NULL);
	(pZone->getObjectRegistry()).registerObject(pMotorcycle);

	pMotorcycle->create(pSlayer->getName(), STORAGE_ZONE, pZone->getZoneID(), pSlayer->getX(), pSlayer->getY());
	setTarget(pMotorcycle->getItemID());

	targetID = pMotorcycle->getItemID();

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	// targetID를 DB에도 update시켜야 한다.
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
					"UPDATE KeyObject SET Target=%lu WHERE ItemID=%lu",
								targetID, getItemID());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	// log
	filelog("motorcycle.txt", "[SetTargetID] Owner = %s, KeyID = %lu, Key's targetID = %lu, MotorcycleID = %lu", pSlayer->getName().c_str(), getItemID(), getTarget(), pMotorcycle->getItemID());

	// 밑에서 pMotorcycle을 사용해도 되겠지만, 기존 코드 안 건드릴려고 여기서 지운다.
	SAFE_DELETE(pMotorcycle);

	return targetID;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Key::toString() const 
	throw()
{
	StringStream msg;

	msg << "Key("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ",Target:"   <<(int)m_Target
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Key::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pKeyInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Key::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pKeyInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Key::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pKeyInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string KeyInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "KeyInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void KeyInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM KeyInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, OptionType, TargetType FROM KeyInfo"
//			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM KeyInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			KeyInfo* pKeyInfo = new KeyInfo();

			pKeyInfo->setItemType(pResult->getInt(++i));
			pKeyInfo->setName(pResult->getString(++i));
			pKeyInfo->setEName(pResult->getString(++i));
			pKeyInfo->setPrice(pResult->getInt(++i));
			pKeyInfo->setVolumeType(pResult->getInt(++i));
			pKeyInfo->setWeight(pResult->getInt(++i));
			pKeyInfo->setRatio(pResult->getInt(++i));
			pKeyInfo->setOptionType(pResult->getInt(++i));
			pKeyInfo->setTargetType(pResult->getInt(++i));

			addItemInfo(pKeyInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void KeyLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Target FROM KeyObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Target FROM KeyObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				Key* pKey = new Key();

				pKey->setItemID(pResult->getDWORD(++i));
				pKey->setObjectID(pResult->getDWORD(++i));
				pKey->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pKey->setTarget(pResult->getDWORD(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
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
				else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (storageID != 0 )
						{
							SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
							if (pInventoryItem == NULL )
							{
								processItemBugEx(pCreature, pKey);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pKey))
						{
							pInventory->addItemEx(x, y, pKey);
						}
						else
						{
							processItemBugEx(pCreature, pKey);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pKey);
						break;

					case STORAGE_BELT :
						//processItemBugEx(pCreature, pKey);
						if (pCreature->isSlayer())
						{
							pItem = pSlayer->findBeltIID(storageID);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_BELT)
							{
								pBelt = dynamic_cast<Belt*>(pItem);
								pBeltInventory = pBelt->getInventory();
								if (pBeltInventory->canAddingEx(x, 0, pKey))
								{
									pBeltInventory->addItem(x, 0, pKey);
								}
								else
								{
									processItemBugEx(pCreature, pKey);
								}
							}
							else
							{
								processItemBugEx(pCreature, pKey);
							}
						}
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pKey);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pKey);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pKey);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pKey);
						}
						else pStash->insert(x, y, pKey);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pKey);
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
void KeyLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Target FROM KeyObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Key* pKey = new Key();

			pKey->setItemID(pResult->getInt(++i));
			pKey->setObjectID(pResult->getInt(++i));
			pKey->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pKey->setTarget(pResult->getDWORD(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pKey);
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
void KeyLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

KeyLoader* g_pKeyLoader = NULL;
