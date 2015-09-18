//////////////////////////////////////////////////////////////////////////////
// Filename    : Potion.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Potion.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "Utility.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "ZoneGroupManager.h"
#include "SubInventory.h"

// global variable declaration
PotionInfoManager* g_pPotionInfoManager = NULL;

ItemID_t Potion::m_ItemIDRegistry = 0;
Mutex    Potion::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Potion::Potion()
	throw()
//: m_ItemType(0)
{
	setItemType(0);
}

Potion::Potion(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
//: m_ItemType(itemType), m_Num(Num)
{
	setItemType(itemType);
	setNum(Num);

	//cout << "Potion::Potion(" << getOptionTypeToString(optionType).c_str() << ")" << endl;
	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), optionType))
	{
		filelog("itembug.log", "Potion::Potion() : Invalid item type or option type");
		throw("Potion::Potion() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Potion::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "INSERT INTO PotionObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)m_Num << ")";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.13
		pStmt->executeQuery("INSERT INTO PotionObject (ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num) VALUES(%ld, %ld, %d, '%s', %d, %ld, %d, %d, %d)",
								m_ItemID, m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, x, y, (int)getNum());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// destroy
//--------------------------------------------------------------------------------
bool Potion::destroy() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		// 만약 포션이라면 다른 Database에 연결해서 지우도록 한다.
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM %s WHERE ItemID = %ld", getObjectTableName().c_str(), m_ItemID);

		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH

	return true;
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Potion::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE PotionObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Potion::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE PotionObject SET "
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

		pStmt->executeQuery("UPDATE PotionObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)getNum(), m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Potion::toString() const 
	throw()
{
	StringStream msg;

	msg << "Potion("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)getItemType()
		<< ",Num:"      <<(int)getNum()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Potion::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPotionInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Potion::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPotionInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Potion::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPotionInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/
int Potion::getHPAmount(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getHPAmount();

	__END_CATCH
}

int Potion::getMPAmount(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getMPAmount();

	__END_CATCH
}



int Potion::getHPDelay(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getHPDelay();

	__END_CATCH
}

int Potion::getMPDelay(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getMPDelay();

	__END_CATCH
}



int Potion::getHPQuantity(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getHPQuantity();

	__END_CATCH
}

int Potion::getMPQuantity(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getMPQuantity();

	__END_CATCH
}


int Potion::getHPRecoveryUnit(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getHPRecoveryUnit();

	__END_CATCH
}

int Potion::getMPRecoveryUnit(void) const
	throw()
{
	__BEGIN_TRY

	PotionInfo* pInfo = dynamic_cast<PotionInfo*>(g_pPotionInfoManager->getItemInfo(getItemType()));
	return pInfo->getMPRecoveryUnit();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// parse effect string
//--------------------------------------------------------------------------------
void PotionInfo::parseEffect(const string& effect)
	throw()
{
	__BEGIN_TRY

	m_HPAmount       = 0;
	m_HPDelay        = 0;
	m_HPRecoveryUnit = 0;
	m_MPAmount       = 0;
	m_MPDelay        = 0;
	m_MPRecoveryUnit = 0;

	if (effect.size() < 5) return;

    size_t a = 0, b = 0, c = 0, d = 0, e = 0;
	
	while (e < effect.size() - 1)
	{
		////////////////////////////////////////////////////////////	
		//(HP,+50,2,1)(MP+10)
		// a  b   ca
		////////////////////////////////////////////////////////////	
		a = effect.find_first_of('(', e);
		b = effect.find_first_of(',', a+1);
		c = effect.find_first_of(',', b+1);
		d = effect.find_first_of(',', c+1);
		e = effect.find_first_of(')', d+1);

		if (a > b || b > c || c > d || d > e) break;

		string recover = trim(effect.substr(a+1, b-a-1));
		uint   amount  = atoi(effect.substr(b+1, c-b-1).c_str());
		uint   delay   = atoi(effect.substr(c+1, d-c-1).c_str());
		uint   unit    = atoi(effect.substr(d+1, e-d-1).c_str());

		if (recover == "HP")
		{
			m_HPAmount       =(int)amount;
			m_HPDelay        =(int)delay;
			m_HPRecoveryUnit =(int)unit;
		}
		else if (recover == "MP")
		{
			m_MPAmount       =(int)amount;
			m_MPDelay        =(int)delay;
			m_MPRecoveryUnit =(int)unit;
		}
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string PotionInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "PotionInfo("
		<< "ItemType:"     <<(int)m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       <<(int)m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      <<(int)m_Weight
		<< ",Description:" << m_Description
		<< ",HPAmount:"    <<(int)m_HPAmount
		<< ",MPAmount:"    <<(int)m_MPAmount
		<< ")";
	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void PotionInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM PotionInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, ItemLevel, Effect FROM PotionInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			PotionInfo* pPotionInfo = new PotionInfo();

			pPotionInfo->setItemType(pResult->getInt(++i));
			pPotionInfo->setName(pResult->getString(++i));
			pPotionInfo->setEName(pResult->getString(++i));
			pPotionInfo->setPrice(pResult->getInt(++i));
			pPotionInfo->setVolumeType(pResult->getInt(++i));
			pPotionInfo->setWeight(pResult->getInt(++i));
			pPotionInfo->setRatio(pResult->getInt(++i));
			pPotionInfo->setItemLevel(pResult->getInt(++i));
			pPotionInfo->parseEffect(pResult->getString(++i));

			addItemInfo(pPotionInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void PotionLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PotionObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PotionObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());



		while (pResult->next())
		{
			try {
				uint i = 0;

				Potion* pPotion = new Potion();

				pPotion->setItemID(pResult->getDWORD(++i));
				pPotion->setObjectID(pResult->getDWORD(++i));
				pPotion->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pPotion->setNum(pResult->getBYTE(++i));

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
								processItemBugEx(pCreature, pPotion);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pPotion))
						{
							pInventory->addItemEx(x, y, pPotion);
						}
						else
						{
							processItemBugEx(pCreature, pPotion);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pPotion);
						break;

					case STORAGE_BELT :
						if (pCreature->isSlayer())
						{
							pItem = pSlayer->findBeltIID(storageID);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_BELT)
							{
								pBelt = dynamic_cast<Belt*>(pItem);
								pBeltInventory = pBelt->getInventory();
								if (pBeltInventory->canAddingEx(x, 0, pPotion))
								{
									pBeltInventory->addItem(x, 0, pPotion);
								}
								else
								{
									processItemBugEx(pCreature, pPotion);
								}
							}
							else
							{
								processItemBugEx(pCreature, pPotion);
							}
						}
						else if (pCreature->isVampire())
						{
							pItem = pVampire->findBeltIID(storageID);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_BELT)
							{
								pBelt = dynamic_cast<Belt*>(pItem);
								pBeltInventory = pBelt->getInventory();
								if (pBeltInventory->canAddingEx(x, 0, pPotion))
								{
									pBeltInventory->addItemEx(x, 0, pPotion);
								}
								else
								{
									processItemBugEx(pCreature, pPotion);
								}
							}
							else
							{
								processItemBugEx(pCreature, pPotion);
							}
						}
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pPotion);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pPotion);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pPotion);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pPotion);
						}
						else pStash->insert(x, y, pPotion);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pPotion);
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
void PotionLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PotionObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Potion* pPotion = new Potion();

			pPotion->setItemID(pResult->getInt(++i));
			pPotion->setObjectID(pResult->getInt(++i));
			pPotion->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pPotion->setNum(pResult->getBYTE(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pPotion);
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
void PotionLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

PotionLoader* g_pPotionLoader = NULL;
