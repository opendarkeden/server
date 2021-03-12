//////////////////////////////////////////////////////////////////////////////
// Filename    : CodeSheet.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CodeSheet.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"

#include <algorithm>

void setStoneNum( vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y, uint Num ); // CGAddItemToCodeSheetHandler.cpp 에 정의되어있는데. 될라나

// global variable declaration
CodeSheetInfoManager* g_pCodeSheetInfoManager = NULL;

ItemID_t CodeSheet::m_ItemIDRegistry = 0;
Mutex    CodeSheet::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
CodeSheet::CodeSheet()
	
: m_ItemType(0)
{
}

CodeSheet::CodeSheet(ItemType_t itemType, const list<OptionType_t>& optionType)
	
: m_ItemType(itemType), m_OptionType(optionType)
{
	if ( m_OptionType.size() == 0 )
	{
		vector<OptionType_t> OptionType;
		while ( OptionType.size() < 30 )
		{
			OptionType.push_back((OptionType_t)0xff);
		}

		for ( int i=0; i<10; ++i )
			for ( int j=0; j<6; ++j )
				if ( ((i+j)%2) == 0 )
				{
					setStoneNum(OptionType, i, j, (rand()%5)+1);
				}

		copy( OptionType.begin(), OptionType.end(), back_inserter(m_OptionType) );
	}
	else while ( m_OptionType.size() < 30 )
	{
		m_OptionType.push_back((OptionType_t)0xff);
	}

//	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, m_OptionType))
//	{
//		filelog("itembug.log", "CodeSheet::CodeSheet() : Invalid item type or option type");
//		throw ("CodeSheet::CodeSheet() : Invalid item type or optionType");
//	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void CodeSheet::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		string optionField;
		setOptionTypeToField( m_OptionType, optionField );

		sql << "INSERT INTO CodeSheetObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "')";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CodeSheet::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE CodeSheetObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void CodeSheet::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE CodeSheetObject SET "
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

		string optionField;
		setOptionTypeToField( m_OptionType, optionField );
		pStmt->executeQuery( "UPDATE CodeSheetObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s' WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CodeSheet::toString() const 
	
{
	StringStream msg;

	msg << "CodeSheet("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)m_ItemType
		<< ",OptionType:"   <<getOptionTypeToString(m_OptionType).c_str()
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t CodeSheet::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pCodeSheetInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t CodeSheet::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pCodeSheetInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t CodeSheet::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pCodeSheetInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CodeSheetInfo::toString() const 
	
{
	StringStream msg;

	msg << "CodeSheetInfo("
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
void CodeSheetInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM CodeSheetInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight FROM CodeSheetInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			CodeSheetInfo* pCodeSheetInfo = new CodeSheetInfo();

			pCodeSheetInfo->setItemType(pResult->getInt(++i));
			pCodeSheetInfo->setName(pResult->getString(++i));
			pCodeSheetInfo->setEName(pResult->getString(++i));
			pCodeSheetInfo->setPrice(pResult->getInt(++i));
			pCodeSheetInfo->setVolumeType(pResult->getInt(++i));
			pCodeSheetInfo->setWeight(pResult->getInt(++i));

			addItemInfo(pCodeSheetInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void CodeSheetLoader::load(Creature* pCreature) 
	
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
			<< " OptionType, Durability, EnchantLevel FROM CodeSheetObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType FROM CodeSheetObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				CodeSheet* pCodeSheet = new CodeSheet();

				pCodeSheet->setItemID(pResult->getDWORD(++i));
				pCodeSheet->setObjectID(pResult->getDWORD(++i));
				pCodeSheet->setItemType(pResult->getDWORD(++i));
	
				if (g_pCodeSheetInfoManager->getItemInfo(pCodeSheet->getItemType())->isUnique())
					pCodeSheet->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pCodeSheet->setOptionType(optionTypes);

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*    pOusters        = NULL;
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
				else if (pCreature->isOusters())
				{
					pOusters	= dynamic_cast<Ousters*>(pCreature);
					pInventory	= pOusters->getInventory();
					pStash		= pOusters->getStash();
				}
				else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pCodeSheet))
						{
							pInventory->addItemEx(x, y, pCodeSheet);
						}
						else
						{
							processItemBugEx(pCreature, pCodeSheet);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pCodeSheet);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pCodeSheet);
						break;

					case STORAGE_EXTRASLOT :
						processItemBugEx(pCreature, pCodeSheet);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pCodeSheet);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pCodeSheet);
						}
						else pStash->insert(x, y, pCodeSheet);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pCodeSheet);
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
void CodeSheetLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, Durability, EnchantLevel, ItemFlag FROM CodeSheetObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			CodeSheet* pCodeSheet = new CodeSheet();

			pCodeSheet->setItemID(pResult->getInt(++i));
			pCodeSheet->setObjectID(pResult->getInt(++i));
			pCodeSheet->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pCodeSheet->setOptionType(optionTypes);

			pCodeSheet->setDurability(pResult->getInt(++i));
			pCodeSheet->setEnchantLevel(pResult->getInt(++i));
			pCodeSheet->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pCodeSheet);
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
void CodeSheetLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

CodeSheetLoader* g_pCodeSheetLoader = NULL;
