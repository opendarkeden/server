//////////////////////////////////////////////////////////////////////////////
// Filename    : WarItem.cpp
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "WarItem.h"
#include "ItemInfoManager.h"
#include "DB.h"

// global variable declaration
WarItemInfoManager* g_pWarItemInfoManager = NULL;

ItemID_t WarItem::m_ItemIDRegistry = 0;
Mutex    WarItem::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
WarItem::WarItem()
	throw()
: m_ItemType(0)
{
}

WarItem::WarItem(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
: m_ItemType(itemType)
{
	try
	{
		if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
		{
			filelog("itembug.log", "WarItem::WarItem() : Invalid item type or option type");
			throw ("WarItem::WarItem() : Invalid item type or optionType");
		}
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		Assert(false);
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void WarItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO WarItemObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ")";

		pStmt->executeQuery(sql.toString());
		filelog( "WarLog.txt", "%s", sql.toString().c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void WarItem::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	char query[255];

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		sprintf( query, "UPDATE WarItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);
		pStmt->executeQuery( query );
		filelog( "WarLog.txt", "%s", query );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void WarItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE WarItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string WarItem::toString() const 
	throw()
{
	StringStream msg;

	msg << "WarItem("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)m_ItemType
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t WarItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pWarItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t WarItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pWarItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t WarItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pWarItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string WarItemInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "WarItemInfo("
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
void WarItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM WarItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM WarItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			WarItemInfo* pWarItemInfo = new WarItemInfo();

			pWarItemInfo->setItemType(pResult->getInt(++i));
			pWarItemInfo->setName(pResult->getString(++i));
			pWarItemInfo->setEName(pResult->getString(++i));
			pWarItemInfo->setPrice(pResult->getInt(++i));
			pWarItemInfo->setVolumeType(pResult->getInt(++i));
			pWarItemInfo->setWeight(pResult->getInt(++i));
			pWarItemInfo->setRatio(pResult->getInt(++i));

			addItemInfo(pWarItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void WarItemLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to zone
//--------------------------------------------------------------------------------
void WarItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to inventory
//--------------------------------------------------------------------------------
void WarItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

WarItemLoader* g_pWarItemLoader = NULL;
