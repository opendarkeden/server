//////////////////////////////////////////////////////////////////////////////
// Filename    : Money.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Money.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"

// global variable declaration
MoneyInfoManager* g_pMoneyInfoManager = NULL;

ItemID_t Money::m_ItemIDRegistry = 0;
Mutex    Money::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Money::Money()
	
: m_ItemType(0), m_Amount(0)
{
}

Money::Money(ItemType_t itemType, const list<OptionType_t>& optionType ,ItemNum_t Num)
	
: m_ItemType(itemType), m_Amount(0)
{
	m_Num      = Num;
	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "Money::Money() : Invalid item type or option type");
		throw ("Money::Money() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Money::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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
/*
		sql << "INSERT INTO MoneyObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Amount )"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " << m_Amount << ")";
*/
		sql << "INSERT INTO MoneyObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Amount, Num )"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " << m_Amount << ", " << (int)m_Num << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Money::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE MoneyObject SET %s, Amount=%ld WHERE ItemID=%ld",
								field, m_Amount, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Money::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE MoneyObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",Amount = " << m_Amount
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE MoneyObject SET ObjectID=%ld ,ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Amount=%ld,Num=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Amount, (int)m_Num ,m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Money::toString() const 
	
{
	StringStream msg;

	msg << "Money("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(uint)m_ItemType
		<< ",Amount:"   <<(uint)m_Amount
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Money::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pMoneyInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Money::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pMoneyInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Money::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pMoneyInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string MoneyInfo::toString() const 
	
{
	StringStream msg;

	msg << "MoneyInfo("
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
void MoneyInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM MoneyInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM MoneyInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			MoneyInfo* pMoneyInfo = new MoneyInfo();

			pMoneyInfo->setItemType(pResult->getInt(++i));
			pMoneyInfo->setName(pResult->getString(++i));
			pMoneyInfo->setEName(pResult->getString(++i));
			pMoneyInfo->setPrice(pResult->getInt(++i));
			pMoneyInfo->setVolumeType(pResult->getInt(++i));
			pMoneyInfo->setWeight(pResult->getInt(++i));
			pMoneyInfo->setRatio(pResult->getInt(++i));

			addItemInfo(pMoneyInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void MoneyLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Amount FROM MoneyObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Amount, Num FROM MoneyObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str() );



		while (pResult->next())
		{
			try {
				uint i = 0;

				Money* pMoney = new Money();

				pMoney->setItemID(pResult->getDWORD(++i));
				pMoney->setObjectID(pResult->getDWORD(++i));
				pMoney->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pMoney->setAmount(pResult->getDWORD(++i));
				pMoney->setNum(pResult->getBYTE(++i));

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
						if (pInventory->canAddingEx(x, y, pMoney))
						{
							pInventory->addItemEx(x, y, pMoney);
						}
						else
						{
							processItemBugEx(pCreature, pMoney);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pMoney);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pMoney);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pMoney);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pMoney);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pMoney);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pMoney);
						}
						else pStash->insert(x, y, pMoney);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pMoney);
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
void MoneyLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Amount FROM MoneyObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Money* pMoney = new Money();

			pMoney->setItemID(pResult->getInt(++i));
			pMoney->setObjectID(pResult->getInt(++i));
			pMoney->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pMoney->setAmount(pResult->getDWORD(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pMoney);
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
void MoneyLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

MoneyLoader* g_pMoneyLoader = NULL;
