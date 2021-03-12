//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCoupleRing.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "VampireCoupleRing.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "PlayerCreature.h"
#include "FlagSet.h"
#include "couple/CoupleManager.h"

#include <stdio.h>

VampireCoupleRingInfoManager* g_pVampireCoupleRingInfoManager = NULL;

ItemID_t VampireCoupleRing::m_ItemIDRegistry = 0;
Mutex    VampireCoupleRing::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRing member methods
//////////////////////////////////////////////////////////////////////////////

VampireCoupleRing::VampireCoupleRing()
	
{
	m_ItemType = 0;
}

VampireCoupleRing::VampireCoupleRing(ItemType_t itemType, const list<OptionType_t>& optionType)
	
: m_ItemType(itemType), m_OptionType( optionType )
{
	__BEGIN_TRY

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "VampireCoupleRing::VampireCoupleRing() : Invalid item type or option type");
		throw ("VampireCoupleRing::VampireCoupleRing() : Invalid item type or optionType");
	}

	__END_CATCH
}

void VampireCoupleRing::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

	    string optionField;
	    setOptionTypeToField( m_OptionType, optionField );

		StringStream sql;
		sql << "INSERT INTO VampireCoupleRingObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Name, PartnerItemID)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', '" << getName().c_str() << "', " << getPartnerItemID() << ")";

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
void VampireCoupleRing::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireCoupleRingObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void VampireCoupleRing::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;

		sql << "UPDATE VampireCoupleRingObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireCoupleRingObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Name='%s', PartnerItemID=%ld WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, getName().c_str(), getPartnerItemID(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string VampireCoupleRing::toString() const 
	
{
	StringStream msg;
	msg << "VampireCoupleRing("
		<< "ItemID:" << m_ItemID
		<< ",ItemType:" << m_ItemType
		<< ")";
	return msg.toString();
}

VolumeWidth_t VampireCoupleRing::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pVampireCoupleRingInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t VampireCoupleRing::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireCoupleRingInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t VampireCoupleRing::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireCoupleRingInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

bool VampireCoupleRing::hasPartnerItem()
	
{
	__BEGIN_TRY

	bool bRet = false;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) from VampireCoupleRingObject where ItemID=%ld and Storage IN(0, 1, 2, 3, 4, 9)", getPartnerItemID() );

		// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()

		if (pResult->next()) 
		{
			int	count = pResult->getInt(1);

			Assert( count >= 0 );
			Assert( count <= 1 );

			if ( count == 1 ) bRet = true;
		}
		else
		{
			bRet = false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bRet;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingInfo member methods
//////////////////////////////////////////////////////////////////////////////

string VampireCoupleRingInfo::toString() const 
	
{
	StringStream msg;
	msg << "VampireCoupleRingInfo("
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

void VampireCoupleRingInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampireCoupleRingInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM VampireCoupleRingInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampireCoupleRingInfo* pVampireCoupleRingInfo = new VampireCoupleRingInfo();

			pVampireCoupleRingInfo->setItemType(pResult->getInt(++i));
			pVampireCoupleRingInfo->setName(pResult->getString(++i));
			pVampireCoupleRingInfo->setEName(pResult->getString(++i));
			pVampireCoupleRingInfo->setPrice(pResult->getInt(++i));
			pVampireCoupleRingInfo->setVolumeType(pResult->getInt(++i));
			pVampireCoupleRingInfo->setWeight(pResult->getInt(++i));
			pVampireCoupleRingInfo->setRatio(pResult->getInt(++i));

			addItemInfo(pVampireCoupleRingInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingLoader member methods
//////////////////////////////////////////////////////////////////////////////

void VampireCoupleRingLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y FROM VampireCoupleRingObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Name, PartnerItemID FROM VampireCoupleRingObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str() );

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature );
		if ( pResult->getRowCount() == 0 && pPC->getFlagSet()->isOn( FLAGSET_IS_COUPLE ) )
		{
			pPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );
			pPC->getFlagSet()->save( pPC->getName() );

			g_pCoupleManager->removeCoupleForce( pPC );
		}

		while (pResult->next())
		{
			try {
				uint i = 0;

				VampireCoupleRing* pVampireCoupleRing = new VampireCoupleRing();

				pVampireCoupleRing->setItemID(pResult->getDWORD(++i));
				pVampireCoupleRing->setObjectID(pResult->getDWORD(++i));
				pVampireCoupleRing->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField( optionTypes, optionField );
				pVampireCoupleRing->setOptionType( optionTypes );

				pVampireCoupleRing->setName( pResult->getString(++i) );
				pVampireCoupleRing->setPartnerItemID( pResult->getDWORD(++i) );

				// 파트너 아이템이 없거나 더 이상 커플이 아니면 아이템을 지워준다.
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
//				if ( !pVampireCoupleRing->hasPartnerItem() )
//				if ( pPC != NULL && !g_pCoupleManager->isCouple( pPC, pVampireCoupleRing->getName() ) )
				if ( pPC != NULL && ( !g_pCoupleManager->isCouple( pPC, pVampireCoupleRing->getName() ) || !pVampireCoupleRing->hasPartnerItem() ) ) 
				{
					g_pCoupleManager->removeCoupleForce( pPC, pVampireCoupleRing->getName() );
					//pVampireCoupleRing->destroy();
					char sql[30];
					sprintf( sql, "Storage = 10" );
					pVampireCoupleRing->tinysave( sql );
					SAFE_DELETE( pVampireCoupleRing );

					// FlagSet 도 날려준다.
					pPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );
					pPC->getFlagSet()->save( pPC->getName() );
					continue;
				}

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
						if (pInventory->canAddingEx(x, y, pVampireCoupleRing))
						{
							pInventory->addItemEx(x, y, pVampireCoupleRing);
						}
						else
						{
							processItemBugEx(pCreature, pVampireCoupleRing);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pVampireCoupleRing);
							}
							else
							{
								processItemBugEx(pCreature, pVampireCoupleRing);
							}
						}
						else if ( pCreature->isVampire() )
						{
							if (!pVampire->isWear((Vampire::WearPart)x))
							{
								pVampire->wearItem((Vampire::WearPart)x, pVampireCoupleRing);
							}
							else
							{
								processItemBugEx(pCreature, pVampireCoupleRing);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pVampireCoupleRing);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampireCoupleRing);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampireCoupleRing);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pVampireCoupleRing);
						break;

					case STORAGE_STASH:
						processItemBugEx(pCreature, pVampireCoupleRing);
				/*		if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pVampireCoupleRing);
						}
						else pStash->insert(x, y, pVampireCoupleRing); */
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pVampireCoupleRing);
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

void VampireCoupleRingLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	cout << "존에 떨어진 아이템 로드는 지원하지 않습니다." << endl;
	Assert( false );

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y FROM VampireCoupleRingObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			VampireCoupleRing* pVampireCoupleRing = new VampireCoupleRing();

			pVampireCoupleRing->setItemID(pResult->getInt(++i));
			pVampireCoupleRing->setObjectID(pResult->getInt(++i));
			pVampireCoupleRing->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pVampireCoupleRing);
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

void VampireCoupleRingLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VampireCoupleRingLoader* g_pVampireCoupleRingLoader = NULL;

