//////////////////////////////////////////////////////////////////////////////
// Filename    : EventItem.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EventItem.h"
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
#include "Party.h"
#include "SubInventory.h"
#include "BalloonHeadbandUtil.h"

EventItemInfoManager* g_pEventItemInfoManager = NULL;

ItemID_t EventItem::m_ItemIDRegistry = 0;
Mutex    EventItem::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class EventItem member methods
//////////////////////////////////////////////////////////////////////////////

EventItem::EventItem()
	throw()
{
	m_ItemType = 0;
}

EventItem::EventItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
{
	m_ItemType = itemType;
	m_Num      = Num;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "EventItem::EventItem() : Invalid item type or option type");
		throw("EventItem::EventItem() : Invalid item type or optionType");
	}
}

void EventItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO EventItemObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)m_Num << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void EventItem::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE EventItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EventItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;

		sql << "UPDATE EventItemObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",Num = " <<(int)m_Num
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE EventItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)m_Num, m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EventItem::toString() const 
	throw()
{
	StringStream msg;

	msg << "EventItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ",Num:"      <<(int)m_Num
		<< ")";

	return msg.toString();
}

VolumeWidth_t EventItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pEventItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t EventItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pEventItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t EventItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pEventItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

void EventItem::whenPCTake(PlayerCreature* pPC )
{
}

//////////////////////////////////////////////////////////////////////////////
// class EventItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

string EventItemInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "EventItemInfo("
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

void EventItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM EventItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM EventItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			EventItemInfo* pEventItemInfo = new EventItemInfo();

			pEventItemInfo->setItemType(pResult->getInt(++i));
			pEventItemInfo->setName(pResult->getString(++i));
			pEventItemInfo->setEName(pResult->getString(++i));
			pEventItemInfo->setPrice(pResult->getInt(++i));
			pEventItemInfo->setVolumeType(pResult->getInt(++i));
			pEventItemInfo->setWeight(pResult->getInt(++i));
			pEventItemInfo->setRatio(pResult->getInt(++i));

			addItemInfo(pEventItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class EventItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void EventItemLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM EventItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM EventItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				EventItem* pEventItem = new EventItem();
				pEventItem->setQuestItem();

				pEventItem->setItemID(pResult->getDWORD(++i));
				pEventItem->setObjectID(pResult->getDWORD(++i));
				pEventItem->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pEventItem->setNum(pResult->getBYTE(++i));
				pEventItem->setCreateType((Item::CreateType)pResult->getInt(++i));

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

				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

				if (pEventItem->getItemType() == 27 )
				{
					// 깃발은 나오면 안 된다. -_-
					processItemBug(pCreature, pEventItem);
				}
				else switch(storage)
				{
					case STORAGE_INVENTORY:
						{
							if (storageID != 0 )
							{
								SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
								if (pInventoryItem == NULL )
								{
									processItemBugEx(pCreature, pEventItem);
									break;
								}

								pInventory = pInventoryItem->getInventory();
							}

							if (pInventory->canAddingEx(x, y, pEventItem))
							{
								pInventory->addItemEx(x, y, pEventItem);

								ItemType_t itemType = pEventItem->getItemType();

								if (itemType == 30 ) 
								{
									pPC->setBaseLuck(10);
								}
								else if (itemType >= 32 && itemType <= 36 )
								{
									// 풍선 머리띠 옵션 적용
									applyBalloonHeadbandDefaultOption(pPC, itemType);
								}
							}
							else
							{
								processItemBugEx(pCreature, pEventItem);
							}
							break;
						}

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pEventItem);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pEventItem);
						break;

					case STORAGE_EXTRASLOT :
						{
							ItemType_t itemType = pEventItem->getItemType();

							if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pEventItem);
							else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pEventItem);
							else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pEventItem);

							if (itemType == 30 )
							{
								pPC->setBaseLuck(10);
							}
							else if (itemType >= 32 && itemType <= 36 )
							{
								// 풍선 머리띠 옵션 적용
								applyBalloonHeadbandDefaultOption(pPC, itemType);
							}

							break;
						}

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pEventItem);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pEventItem);
						}
						else
						{
							pStash->insert(x, y, pEventItem);
							if (pEventItem->getItemType() == 30 ) pPC->setBaseLuck(10);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pEventItem);
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

void EventItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM EventItemObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			EventItem* pEventItem = new EventItem();

			pEventItem->setItemID(pResult->getInt(++i));
			pEventItem->setObjectID(pResult->getInt(++i));
			pEventItem->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pEventItem->setNum(pResult->getBYTE(++i));
			pEventItem->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pEventItem);
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

void EventItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

EventItemLoader* g_pEventItemLoader = NULL;
