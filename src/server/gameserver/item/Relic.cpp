//////////////////////////////////////////////////////////////////////////////
// Filename    : Relic.cpp
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Relic.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

// global variable declaration
RelicInfoManager* g_pRelicInfoManager = NULL;

ItemID_t Relic::m_ItemIDRegistry = 0;
Mutex    Relic::m_Mutex;


const string RelicType2String[] =
{
	"RELIC_TYPE_SLAYER",
	"RELIC_TYPE_VAMPIRE"
};


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Relic::Relic()
	throw()
: m_ItemType(0), m_Durability(0)
{
	m_EnchantLevel = 0;
}

Relic::Relic(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
: m_ItemType(itemType), m_Durability(0)
{
	try {
		m_EnchantLevel = 0;

		m_Durability = computeMaxDurability(this);

		if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
		{
			filelog("itembug.log", "Relic::Relic() : Invalid item type or option type");
			throw ("Relic::Relic() : Invalid item type or optionType");
		}
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		Assert(false);
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void Relic::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO RelicObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, Durability)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", " << m_Durability << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Relic::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE RelicObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void Relic::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE RelicObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)m_OptionType
			<< ",Durability = " << m_Durability
			<< ",EnchantLevel = " <<(int)m_EnchantLevel
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE RelicObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Durability=%d, EnchantLevel=%d  WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Durability, (int)m_EnchantLevel, m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Relic::toString() const 
	throw()
{
	StringStream msg;

	msg << "Relic("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)m_ItemType
		<< ",Durability:"   <<(int)m_Durability
		<< ",EnchantLevel:" <<(int)m_EnchantLevel
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t Relic::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pRelicInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t Relic::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pRelicInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t Relic::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pRelicInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t Relic::getDefenseBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pRelicInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t Relic::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pRelicInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string RelicInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "RelicInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",Durability:" << m_Durability
		<< ",DefenseBonus:" << m_DefenseBonus
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void RelicInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM RelicInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, RelicType, ZoneID, XCoord, YCoord, MonsterType FROM RelicInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			RelicInfo* pRelicInfo = new RelicInfo();

			pRelicInfo->setItemType(pResult->getInt(++i));
			pRelicInfo->setName(pResult->getString(++i));
			pRelicInfo->setEName(pResult->getString(++i));
			pRelicInfo->setPrice(pResult->getInt(++i));
			pRelicInfo->setVolumeType(pResult->getInt(++i));
			pRelicInfo->setWeight(pResult->getInt(++i));
			pRelicInfo->setRatio(pResult->getInt(++i));
			pRelicInfo->setDurability(pResult->getInt(++i));
			pRelicInfo->setDefenseBonus(pResult->getInt(++i));
			pRelicInfo->setProtectionBonus(pResult->getInt(++i));
			pRelicInfo->setReqAbility(pResult->getString(++i));
			pRelicInfo->setItemLevel(pResult->getInt(++i));

			pRelicInfo->setRelicType(pResult->getString(++i));
			pRelicInfo->zoneID = pResult->getInt(++i);
			pRelicInfo->x = pResult->getInt(++i);
			pRelicInfo->y = pResult->getInt(++i);
			pRelicInfo->monsterType = pResult->getInt(++i);

			addItemInfo(pRelicInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void RelicLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, "
			<< " OptionType, Durability, EnchantLevel FROM RelicObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// Relic load할게 있다는것은..
		// 현재로서는 이전에 서버다운이 되었다는 의미이다.
		// 그래서, 지운다. by sigi
		pStmt->executeQuery( 
				"DELETE FROM RelicObject WHERE OwnerID = '%s'", 
				pCreature->getName().c_str() );

		/*
		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Durability, EnchantLevel FROM RelicObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			uint i = 0;

			Relic* pRelic = new Relic();

			pRelic->setItemID(pResult->getDWORD(++i));
			pRelic->setObjectID(pResult->getDWORD(++i));
			pRelic->setItemType(pResult->getDWORD(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getDWORD(++i);
			BYTE x = pResult->getBYTE(++i);
			BYTE y = pResult->getBYTE(++i);

			pRelic->setOptionType(pResult->getInt(++i));
			pRelic->setDurability(pResult->getInt(++i));
			pRelic->setEnchantLevel(pResult->getInt(++i));

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
					if (pInventory->canAddingEx(x, y, pRelic))
					{
						pInventory->addItemEx(x, y, pRelic);
					}
					else
					{
						processItemBugEx(pCreature, pRelic);
					}
					break;

				case STORAGE_GEAR:
					if (pCreature->isSlayer())
					{
						if (!pSlayer->isWear((Slayer::WearPart)x))
						{
							pSlayer->wearItem((Slayer::WearPart)x, pRelic);
						}
						else
						{
							processItemBugEx(pCreature, pRelic);
						}
					}
					else if (pCreature->isVampire())
					{
						processItemBugEx(pCreature, pRelic);
					}
					break;

				case STORAGE_BELT :
					processItemBugEx(pCreature, pRelic);
					break;

				case STORAGE_EXTRASLOT :
					if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pRelic);
					else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pRelic);
					break;

				case STORAGE_MOTORCYCLE:
					processItemBugEx(pCreature, pRelic);
					break;

				case STORAGE_STASH:
					if (pStash->isExist(x, y))
					{
						processItemBugEx(pCreature, pRelic);
					}
					else pStash->insert(x, y, pRelic);
					break;

				case STORAGE_GARBAGE:
					processItemBug(pCreature, pRelic);
					break;

				default :
					SAFE_DELETE(pStmt);	// by sigi
					throw Error("invalid storage or OwnerID must be NULL");
			}
		}
		*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to zone
//--------------------------------------------------------------------------------
void RelicLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " Durability, EnchantLevel FROM RelicObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			Relic* pRelic = new Relic();

			pRelic->setItemID(pResult->getInt(++i));
			pRelic->setObjectID(pResult->getInt(++i));
			pRelic->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pRelic->setDurability(pResult->getInt(++i));
			pRelic->setEnchantLevel(pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pRelic);
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
void RelicLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

RelicLoader* g_pRelicLoader = NULL;
