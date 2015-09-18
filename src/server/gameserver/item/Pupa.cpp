//////////////////////////////////////////////////////////////////////////////
// Filename    : Pupa.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Pupa.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "OustersArmsband.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "Utility.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "ZoneGroupManager.h"
#include "SubInventory.h"

// global variable declaration
PupaInfoManager* g_pPupaInfoManager = NULL;

ItemID_t Pupa::m_ItemIDRegistry = 0;
Mutex    Pupa::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Pupa::Pupa()
	throw()
: m_ItemType(0)
{
}

Pupa::Pupa(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
: m_ItemType(itemType), m_Num(Num)
{
	//cout << "Pupa::Pupa(" << getOptionTypeToString(optionType).c_str() << ")" << endl;
	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "Pupa::Pupa() : Invalid item type or option type");
		throw("Pupa::Pupa() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Pupa::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO PupaObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)m_Num << ")";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.13
		pStmt->executeQuery("INSERT INTO PupaObject (ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num) VALUES(%ld, %ld, %d, '%s', %d, %ld, %d, %d, %d)",
								m_ItemID, m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, x, y, (int)m_Num);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// destroy
//--------------------------------------------------------------------------------
bool Pupa::destroy() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
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
void Pupa::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE PupaObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Pupa::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE PupaObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)m_Num, m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Pupa::toString() const 
	throw()
{
	StringStream msg;

	msg << "Pupa("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ",Num:"      <<(int)m_Num
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Pupa::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPupaInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Pupa::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPupaInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Pupa::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPupaInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

int Pupa::getHPAmount(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getHPAmount();

	__END_CATCH
}

int Pupa::getMPAmount(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getMPAmount();

	__END_CATCH
}

int Pupa::getHPDelay(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getHPDelay();

	__END_CATCH
}

int Pupa::getMPDelay(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getMPDelay();

	__END_CATCH
}

int Pupa::getHPQuantity(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getHPQuantity();

	__END_CATCH
}

int Pupa::getMPQuantity(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getMPQuantity();

	__END_CATCH
}

int Pupa::getHPRecoveryUnit(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getHPRecoveryUnit();

	__END_CATCH
}

int Pupa::getMPRecoveryUnit(void) const
	throw()
{
	__BEGIN_TRY

	PupaInfo* pInfo = dynamic_cast<PupaInfo*>(g_pPupaInfoManager->getItemInfo(m_ItemType));
	return pInfo->getMPRecoveryUnit();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// parse effect string
//--------------------------------------------------------------------------------
void PupaInfo::parseEffect(const string& effect)
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
string PupaInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "PupaInfo("
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
void PupaInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM PupaInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Effect FROM PupaInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			PupaInfo* pPupaInfo = new PupaInfo();

			pPupaInfo->setItemType(pResult->getInt(++i));
			pPupaInfo->setName(pResult->getString(++i));
			pPupaInfo->setEName(pResult->getString(++i));
			pPupaInfo->setPrice(pResult->getInt(++i));
			pPupaInfo->setVolumeType(pResult->getInt(++i));
			pPupaInfo->setWeight(pResult->getInt(++i));
			pPupaInfo->setRatio(pResult->getInt(++i));
			pPupaInfo->parseEffect(pResult->getString(++i));

			addItemInfo(pPupaInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void PupaLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PupaObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());

		while (pResult->next())
		{
			try {
				uint i = 0;

				Pupa* pPupa = new Pupa();

				pPupa->setItemID(pResult->getDWORD(++i));
				pPupa->setObjectID(pResult->getDWORD(++i));
				pPupa->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pPupa->setNum(pResult->getBYTE(++i));

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

				OustersArmsband* pOustersArmsband = NULL;
				Inventory* pArmsbandInventory = NULL;

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
							SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
							if (pInventoryItem == NULL )
							{
								processItemBugEx(pCreature, pPupa);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pPupa))
						{
							pInventory->addItemEx(x, y, pPupa);
						}
						else
						{
							processItemBugEx(pCreature, pPupa);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pPupa);
						break;

					case STORAGE_BELT :
						if (pCreature->isSlayer())
						{
							pItem = pSlayer->findBeltIID(storageID);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_BELT)
							{
								pBelt = dynamic_cast<Belt*>(pItem);
								pBeltInventory = pBelt->getInventory();
								if (pBeltInventory->canAddingEx(x, 0, pPupa))
								{
									pBeltInventory->addItem(x, 0, pPupa);
								}
								else
								{
									processItemBugEx(pCreature, pPupa);
								}
							}
							else
							{
								processItemBugEx(pCreature, pPupa);
							}
						}
						else if (pCreature->isVampire())
						{
							pItem = pVampire->findBeltIID(storageID);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_BELT)
							{
								pBelt = dynamic_cast<Belt*>(pItem);
								pBeltInventory = pBelt->getInventory();
								if (pBeltInventory->canAddingEx(x, 0, pPupa))
								{
									pBeltInventory->addItemEx(x, 0, pPupa);
								}
								else
								{
									processItemBugEx(pCreature, pPupa);
								}
							}
							else
							{
								processItemBugEx(pCreature, pPupa);
							}
						}
						else if (pCreature->isOusters())
						{
							pItem = findItemIID(pOusters, storageID, Item::ITEM_CLASS_OUSTERS_ARMSBAND);
							if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND)
							{
								pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
								pArmsbandInventory = pOustersArmsband->getInventory();
								if (pArmsbandInventory->canAddingEx(x, 0, pPupa))
								{
									pArmsbandInventory->addItemEx(x, 0, pPupa);
								}
								else
								{
									processItemBugEx(pCreature, pPupa);
								}
							}
							else
							{
								processItemBugEx(pCreature, pPupa);
							}
						}
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pPupa);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pPupa);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pPupa);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pPupa);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pPupa);
						}
						else pStash->insert(x, y, pPupa);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pPupa);
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
void PupaLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PupaObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Pupa* pPupa = new Pupa();

			pPupa->setItemID(pResult->getInt(++i));
			pPupa->setObjectID(pResult->getInt(++i));
			pPupa->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pPupa->setNum(pResult->getBYTE(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pPupa);
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
void PupaLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

PupaLoader* g_pPupaLoader = NULL;
