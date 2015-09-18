//////////////////////////////////////////////////////////////////////////////
// Filename    : DyePotion.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "DyePotion.h"
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
#include "SubInventory.h"

DyePotionInfoManager* g_pDyePotionInfoManager = NULL;

ItemID_t DyePotion::m_ItemIDRegistry = 0;
Mutex    DyePotion::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class DyePotion member methods
//////////////////////////////////////////////////////////////////////////////

DyePotion::DyePotion()
	throw()
{
	setItemType(0);
}

DyePotion::DyePotion(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
{
	setItemType(itemType);
	setNum(Num);

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "DyePotion::DyePotion() : Invalid item type or option type");
		throw("DyePotion::DyePotion() : Invalid item type or optionType");
	}
}

void DyePotion::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO DyePotionObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)getNum() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void DyePotion::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE DyePotionObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void DyePotion::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE DyePotionObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)getNum(), m_ItemID);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string DyePotion::toString() const 
	throw()
{
	StringStream msg;

	msg << "DyePotion("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)getItemType()
		<< ",Num:"      <<(int)getNum()
		<< ")";

	return msg.toString();
}

/*VolumeWidth_t DyePotion::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pDyePotionInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t DyePotion::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pDyePotionInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t DyePotion::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pDyePotionInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/
//////////////////////////////////////////////////////////////////////////////
// class DyePotionInfo member methods
//////////////////////////////////////////////////////////////////////////////

string DyePotionInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "DyePotionInfo("
		<< "ItemType:"     <<(int)m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       <<(int)m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      <<(int)m_Weight
		<< ",Function:"      <<(int)m_fFunction
		<< ",FunctionValue:" <<(int)m_FunctionValue
		<< ",Description:" << m_Description
		<< ")";
	return msg.toString();
}

void DyePotionInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM DyePotionInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, FunctionFlag, FunctionValue FROM DyePotionInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			DyePotionInfo* pDyePotionInfo = new DyePotionInfo();

			pDyePotionInfo->setItemType(pResult->getInt(++i));
			pDyePotionInfo->setName(pResult->getString(++i));
			pDyePotionInfo->setEName(pResult->getString(++i));
			pDyePotionInfo->setPrice(pResult->getInt(++i));
			pDyePotionInfo->setVolumeType(pResult->getInt(++i));
			pDyePotionInfo->setWeight(pResult->getInt(++i));
			pDyePotionInfo->setRatio(pResult->getInt(++i));
			pDyePotionInfo->setFunctionFlag(pResult->getInt(++i));
			pDyePotionInfo->setFunctionValue(pResult->getInt(++i));

			addItemInfo(pDyePotionInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class DyePotionLoader member methods
//////////////////////////////////////////////////////////////////////////////

void DyePotionLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM DyePotionObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str());

		while (pResult->next())
		{
			try {
				uint i = 0;

				DyePotion* pDyePotion = new DyePotion();

				pDyePotion->setItemID(pResult->getDWORD(++i));
				pDyePotion->setObjectID(pResult->getDWORD(++i));
				pDyePotion->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pDyePotion->setNum(pResult->getBYTE(++i));
				pDyePotion->setCreateType((Item::CreateType)pResult->getInt(++i));

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
							SubInventory* pInventoryItem = dynamic_cast<SubInventory*>(findItemIID(pCreature, storageID ));
							if (pInventoryItem == NULL )
							{
								processItemBugEx(pCreature, pDyePotion);
								break;
							}

							pInventory = pInventoryItem->getInventory();
						}

						if (pInventory->canAddingEx(x, y, pDyePotion))
						{
							pInventory->addItemEx(x, y, pDyePotion);
						}
						else
						{
							processItemBugEx(pCreature, pDyePotion);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pDyePotion);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pDyePotion);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pDyePotion);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pDyePotion);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pDyePotion);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pDyePotion);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pDyePotion);
						}
						else pStash->insert(x, y, pDyePotion);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pDyePotion);
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

void DyePotionLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM DyePotionObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			DyePotion* pDyePotion = new DyePotion();

			pDyePotion->setItemID(pResult->getInt(++i));
			pDyePotion->setObjectID(pResult->getInt(++i));
			pDyePotion->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pDyePotion->setNum(pResult->getBYTE(++i));
			pDyePotion->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pDyePotion);
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

void DyePotionLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

DyePotionLoader* g_pDyePotionLoader = NULL;
