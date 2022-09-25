//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayerCreature.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PlayerCreature.h"
#include "Stash.h"
#include "DB.h"
#include "StringStream.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Belt.h"
#include "Inventory.h"
#include "GoodsInventory.h"
#include "Zone.h"
#include "FlagSet.h"
#include "ParkingCenter.h"
#include "Key.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GCRankBonusInfo.h"
#include "GCTimeLimitItemInfo.h"
#include "GCModifyInformation.h"
#include "GCOtherModifyInfo.h"
#include "GCNoticeEvent.h"
#include "GCMonsterKillQuestInfo.h"
#include "GCPetStashList.h"
#include "GCModifyNickname.h"
#include "GCSystemMessage.h"
#include "Player.h"
#include "RankBonusInfo.h"
#include "GamePlayer.h"
#include "TimeLimitItemManager.h"
#include "mission/QuestManager.h"
#include "Properties.h"
#include "PKZoneInfoManager.h"
#include "RankExpTable.h"
#include "EventKick.h"
#include "GameServerInfoManager.h"
//#include "QuestManager.h"
//#include "QuestEvent.h"
//#include "Quest.h"
//#include "SimpleQuestLoader.h"
#include <list>
#include "DefaultOptionSetInfo.h"
#include "Pet.h"
#include "SMSAddressBook.h"
#include "NicknameBook.h"
#include "GQuestManager.h"
#include "VariableManager.h"
#include "CreatureUtil.h"
#include "BloodBibleSignInfo.h"
#include "Store.h"
#include "mofus/Mofus.h"
#include "AdvancementClassExpTable.h"

const int MAX_GOODS_INVENTORY_SIZE = 10;

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
PlayerCreature::PlayerCreature(ObjectID_t OID, Player* pPlayer)
	
: Creature(OID, pPlayer), m_pAdvancementClass( NULL )
{
	__BEGIN_TRY

	m_pInventory          = new Inventory(10, 6);
	m_pExtraInventorySlot = new InventorySlot();

	m_pGoodsInventory     = new GoodsInventory();

	m_pStash              = new Stash;
	m_StashNum            = 0;
	m_StashGold           = 0;
	m_bStashStatus        = false;

	m_pFlagSet            = new FlagSet;
	m_isPK				  = false;
	m_GuildID			  = 0;

	m_pQuestManager		  = new QuestManager(this);
	m_pTimeLimitItemManager = new TimeLimitItemManager( this );

	m_bLotto			  = false;
	m_pQuestItem		= NULL;
	m_pPetInfo			= NULL;

	m_RankExpSaveCount   = 0;
	m_pRank = NULL;
	m_pPet = NULL;
//	m_pSMSAddressBook = NULL;
	m_pSMSAddressBook = new SMSAddressBook( this );
	m_SMSCharge = 0;
//	m_pNicknameBook = NULL;
	m_pNicknameBook = new NicknameBook( this );
	m_pNickname = NULL;
	
	m_PetStash.reserve( MAX_PET_STASH );
	for ( int i=0; i<MAX_PET_STASH; ++i ) m_PetStash.push_back(NULL);

	m_pGQuestManager = new GQuestManager( this );
	m_pBloodBibleSign = new BloodBibleSignInfo;
	m_BaseLuck = 0;
	m_pStore = new Store;
	m_bAdvanced = false;
	m_AdvancementClassExpSaveCount = 0;

	m_AdvancedAttrBonus = 0;
	m_AdvancedSTR = 0;
	m_AdvancedDEX = 0;
	m_AdvancedINT = 0;
	m_MasterEffectColor = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
PlayerCreature::~PlayerCreature()
	
{
	__BEGIN_TRY

	// ÀÎº¥Åä¸® »èÁ¦
	SAFE_DELETE(m_pInventory);

	SAFE_DELETE(m_pGoodsInventory);

	// ¸¶¿ì½º Æ÷ÀÎÅÍ¿Í ´Þ·ÁÀÖ´Â ¾ÆÀÌÅÛÀ» »èÁ¦ÇÑ´Ù.
	if (m_pExtraInventorySlot != NULL)
	{
		Item* pItem = m_pExtraInventorySlot->getItem();
		if (pItem != NULL)
		{
			if (pItem->getItemClass() == Item::ITEM_CLASS_KEY)
			{
				Key* pKey = dynamic_cast<Key*>(pItem);
				// °Á °£´ÜÇÏ°Ô ÀÌ¾È¿¡¼­ ¾Ë¾Æ¼­ Á¸¿¡¼­ Áö¿ö ÁÖµµ·Ï ÇÏÀÚ.
				if (g_pParkingCenter->hasMotorcycleBox(pKey->getTarget()))
				{
					g_pParkingCenter->deleteMotorcycleBox(pKey->getTarget());
				}
			}

			m_pExtraInventorySlot->deleteItem();
			SAFE_DELETE(pItem);
		}

		SAFE_DELETE(m_pExtraInventorySlot);
	}

	// º¸°üÇÔ »èÁ¦
	SAFE_DELETE(m_pStash);

	// ÇÃ·¡±× ¼Â »èÁ¦
	SAFE_DELETE(m_pFlagSet);

	// RankBonus unordered_map »èÁ¦
	for ( HashMapRankBonusItor itr = m_RankBonuses.begin(); itr != m_RankBonuses.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}
	m_RankBonuses.clear();

	if ( m_pTimeLimitItemManager != NULL )
		SAFE_DELETE( m_pTimeLimitItemManager );

	if ( m_pQuestManager != NULL )
		SAFE_DELETE( m_pQuestManager );

/*	for ( list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin(); itr != m_ItemNameInfoList.end(); itr++ )
	{
		ItemNameInfo* pInfo = *itr;
		SAFE_DELETE( pInfo );
	}
	m_ItemNameInfoList.clear();*/

	if ( m_pQuestItem != NULL )
		SAFE_DELETE( m_pQuestItem );

	SAFE_DELETE( m_pRank );

	for ( int i=0; i<MAX_PET_STASH; ++i )
	{
		SAFE_DELETE( m_PetStash[i] );
	}

	SAFE_DELETE( m_pSMSAddressBook );
	SAFE_DELETE( m_pNicknameBook );
	SAFE_DELETE( m_pGQuestManager );
	SAFE_DELETE( m_pBloodBibleSign );
	SAFE_DELETE( m_pStore );
	SAFE_DELETE( m_pAdvancementClass );

	__END_CATCH
}

bool PlayerCreature::load()
{
	__BEGIN_TRY

	m_pSMSAddressBook->load();

	m_PowerPoint = loadPowerPoint( getName() );

	return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¾ÆÀÌÅÛ ÇÏ³ª µî·ÏÇÏ±â
// *** ÁÖÀÇ ***
// ÀÌ ÇÔ¼ö¸¦ ºÎ¸£±â Àü¿¡ ¹Ýµå½Ã OR¿¡´Ù ¶ôÀ» °É¾î¾ß ÇÑ´Ù.
// ³»ºÎÀûÀ¸·Î´Â ¶ôÀ» °ÉÁö ¾Ê±â ¶§¹®ÀÌ´Ù.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerItem(Item* pItem, ObjectRegistry& OR)
    
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	// Item ÀÚÃ¼¿¡ ObjectID ÇÒ´ç
	OR.registerObject_NOLOCKED(pItem);
	// ½Ã°£Á¦ÇÑ ¾ÆÀÌÅÛ ¸Å´ÏÀú¿¡ OID °¡ ¹Ù²î¾ú´Ù°í ¾Ë·ÁÁØ´Ù.
	m_pTimeLimitItemManager->registerItem( pItem );

	// º§Æ®¶ó¸é ¾È¿¡ ÀÖ´Â ¾ÆÀÌÅÛµéµµ OID¸¦ ¹Þ¾Æ³õ¾Æ¾ß ÇÑ´Ù.
	if (pItem->getItemClass() == Item::ITEM_CLASS_BELT)
	{
		Belt*       pBelt       = dynamic_cast<Belt*>(pItem);
		PocketNum_t PocketCount = pBelt->getPocketCount();
		Inventory*  pInventory  = pBelt->getInventory();

		for (int k=0; k<PocketCount; k++)
		{
			Item* pBeltItem = pInventory->getItem(k, 0);
			if (pBeltItem != NULL)
			{
				OR.registerObject_NOLOCKED(pBeltItem);
				// ½Ã°£Á¦ÇÑ ¾ÆÀÌÅÛ ¸Å´ÏÀú¿¡ OID °¡ ¹Ù²î¾ú´Ù°í ¾Ë·ÁÁØ´Ù.
				m_pTimeLimitItemManager->registerItem( pBeltItem );
			}
		}
	} 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ÀÎº¥Åä¸® ¾È¿¡ ÀÖ´Â ¾ÆÀÌÅÛ µî·ÏÇÏ±â
// *** ÁÖÀÇ ***
// ÀÌ ÇÔ¼ö¸¦ ºÎ¸£±â Àü¿¡ ¹Ýµå½Ã OR¿¡´Ù ¶ôÀ» °É¾î¾ß ÇÑ´Ù.
// ³»ºÎÀûÀ¸·Î´Â ¶ôÀ» °ÉÁö ¾Ê±â ¶§¹®ÀÌ´Ù.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerInventory(ObjectRegistry& OR)
    
{
	__BEGIN_TRY

	list<Item*> ItemList;
	int height = m_pInventory->getHeight();
	int width  = m_pInventory->getWidth();

	for (int j=0; j<height; j++)
	{
		for (int i=0; i<width; i++)
		{
			Item* pItem = m_pInventory->getItem(i, j);
			if (pItem != NULL)
			{
				// µî·ÏµÈ ¾ÆÀÌÅÛÀÇ ¸®½ºÆ®¿¡¼­ ÇöÀç ¾ÆÀÌÅÛÀ» Ã£´Â´Ù.
				list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

				if (itr == ItemList.end())
				{
					// °°Àº ¾ÆÀÌÅÛÀ» µÎ¹ø µî·ÏÇÏÁö ¾Ê±â À§ÇØ¼­
					// ¸®½ºÆ®¿¡´Ù°¡ ¾ÆÀÌÅÛÀ» Áý¾î³Ö´Â´Ù.
					ItemList.push_back(pItem);

					// ¾ÆÀÌÅÛÀÇ OID¸¦ ÇÒ´ç¹Þ´Â´Ù.
					registerItem(pItem, OR);

					i += pItem->getVolumeWidth() - 1;
				}
			}
		}
	}

	__END_CATCH
}

void PlayerCreature::registerInitInventory(ObjectRegistry& OR)
    
{
	__BEGIN_TRY

	list<Item*> ItemList;
	int height = m_pInventory->getHeight();
	int width  = m_pInventory->getWidth();

	for (int j=0; j<height; j++)
	{
		for (int i=0; i<width; i++)
		{
			Item* pItem = m_pInventory->getItem(i, j);
			if (pItem != NULL)
			{
				// µî·ÏµÈ ¾ÆÀÌÅÛÀÇ ¸®½ºÆ®¿¡¼­ ÇöÀç ¾ÆÀÌÅÛÀ» Ã£´Â´Ù.
				list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

				if (itr == ItemList.end())
				{
					// °°Àº ¾ÆÀÌÅÛÀ» µÎ¹ø µî·ÏÇÏÁö ¾Ê±â À§ÇØ¼­
					// ¸®½ºÆ®¿¡´Ù°¡ ¾ÆÀÌÅÛÀ» Áý¾î³Ö´Â´Ù.
					ItemList.push_back(pItem);

					// ItemTrace ¸¦ ³²±æ °ÍÀÎÁö °áÁ¤
					pItem->setTraceItem( bTraceLog( pItem ) );

					// ¾ÆÀÌÅÛÀÇ OID¸¦ ÇÒ´ç¹Þ´Â´Ù.
					registerItem(pItem, OR);

					i += pItem->getVolumeWidth() - 1;
				}
			}
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ ¾È¿¡ µé¾îÀÖ´Â ¾ÆÀÌÅÛ µî·ÏÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerStash(void)
	
{
	__BEGIN_TRY

	Zone* pZone = getZone();
	ObjectRegistry& OR = pZone->getObjectRegistry();

	__ENTER_CRITICAL_SECTION(OR)

	for (int r=0; r<STASH_RACK_MAX; r++)
	{
		for (int i=0; i<STASH_INDEX_MAX; i++)
		{
			Item* pStashItem = m_pStash->get(r, i);
			if (pStashItem != NULL) registerItem(pStashItem, OR);
		}
	}

	__LEAVE_CRITICAL_SECTION(OR)

	m_bStashStatus = true;

	__END_CATCH
}

void PlayerCreature::registerGoodsInventory(ObjectRegistry& OR)
    
{
	__BEGIN_TRY

	GoodsInventory::ListItem& goods = m_pGoodsInventory->getGoods();
	GoodsInventory::ListItemItr itr = goods.begin();

	for ( ; itr != goods.end(); itr++ )
	{
		registerItem( (*itr).m_pItem, OR);
	}

	__END_CATCH
}


void PlayerCreature::loadTimeLimitItem() 
{
	__BEGIN_TRY

	Assert( m_pTimeLimitItemManager != NULL );

	m_pTimeLimitItemManager->load();

	__END_CATCH
}

void PlayerCreature::loadItem()
	
{
	__BEGIN_TRY

	loadTimeLimitItem();

	m_pNicknameBook->load();
	m_pGQuestManager->init();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT ItemType FROM BloodBibleSignObject WHERE OwnerID='%s' ORDER BY ItemType", getName().c_str());

		while ( pResult->next() )
		{
			m_pBloodBibleSign->getList().push_back( pResult->getInt(1) );
		}
	}
	END_DB( pStmt );

	__END_CATCH
}

bool PlayerCreature::wasteIfTimeLimitExpired(Item* pItem)
	
{
	__BEGIN_TRY

	if ( pItem == NULL ) return false;

	if ( m_pTimeLimitItemManager->wasteIfTimeOver( pItem ) )
	{
		pItem->waste( STORAGE_TIMEOVER );
		return true;
	}

	return false;

	__END_CATCH
}

void PlayerCreature::sendTimeLimitItemInfo()
	
{
	__BEGIN_TRY

	GCTimeLimitItemInfo gcTimeLimitItemInfo;

	if ( m_pTimeLimitItemManager->makeTimeLimitItemInfo( gcTimeLimitItemInfo ) )
	{
		getPlayer()->sendPacket( &gcTimeLimitItemInfo );
	}

	__END_CATCH
}

void PlayerCreature::addTimeLimitItem(Item* pItem, DWORD time) 
{
	m_pTimeLimitItemManager->addTimeLimitItem( pItem, time );
} 

void PlayerCreature::sellItem( Item* pItem ) 
{
	__BEGIN_TRY

	if ( pItem->isTimeLimitItem() ) m_pTimeLimitItemManager->itemSold( pItem );

	__END_CATCH
}

void PlayerCreature::deleteItemByMorph( Item* pItem ) 
{
	__BEGIN_TRY

	if ( pItem->isTimeLimitItem() ) m_pTimeLimitItemManager->deleteItemByMorph( pItem );

	__END_CATCH
}

void PlayerCreature::updateItemTimeLimit( Item* pItem, DWORD time ) 
{
	__BEGIN_TRY

	if ( pItem->isTimeLimitItem() ) m_pTimeLimitItemManager->updateItemTimeLimit( pItem, time );

	__END_CATCH
}

void PlayerCreature::sendCurrentQuestInfo() const 
{
	m_pQuestManager->sendQuestInfo();
}

void PlayerCreature::whenQuestLevelUpgrade()
{
	static bool bNonPK = g_pGameServerInfoManager->getGameServerInfo( 1, g_pConfig->getPropertyInt( "ServerID" ), g_pConfig->getPropertyInt( "WorldID" ) )->isNonPKServer();

	if ( bNonPK && getLevel() > 80 )
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
		Assert(pGamePlayer!=NULL);

		GCSystemMessage gcSM;
		gcSM.setMessage( "µ±Ç°µÈ¼¶ÒÑ³¬³öµÇÂ½½ûÖ¹PKµÄ·þÎñÆ÷ÏÞÖÆ.10Ãëºó½«ÍË³ö." );
		pGamePlayer->sendPacket( &gcSM );

		bool newEvent = false;
		EventKick* pEvent = dynamic_cast<EventKick*>(pGamePlayer->getEvent(Event::EVENT_CLASS_KICK));
		if ( pEvent == NULL )
		{
			pEvent = new EventKick( pGamePlayer );
			newEvent = true;
		}

		pEvent->setDeadline(100);
		if ( newEvent ) pGamePlayer->addEvent( pEvent );
	}

	if ( g_pVariableManager->getVariable( CHOBO_EVENT ) )
	{
		Level_t level = getLevel();
		if ( level < 40 && (level%5) == 0 )
		{
			getGQuestManager()->getGQuestInventory().saveOne( getName(), 13+(level/5) );
			getPlayer()->sendPacket( getGQuestManager()->getGQuestInventory().getInventoryPacket() );

			GCNoticeEvent gcNE;
			gcNE.setCode( NOTICE_EVENT_GIVE_PRESENT_1 + (level/5) );
			getPlayer()->sendPacket( &gcNE );
		}
		if ( level == 40 )
		{
			GCNoticeEvent gcNE;
			gcNE.setCode( NOTICE_EVENT_CAN_OPEN_PRESENT_8 );
			getPlayer()->sendPacket( &gcNE );
		}
	}

	m_pGQuestManager->levelUp();

	if ( getQuestLevel() == 40 )
	{
		GCNoticeEvent gcNE;
		gcNE.setCode( NOTICE_EVENT_CAN_PET_QUEST );
		getPlayer()->sendPacket(&gcNE);
	}

	if ( getLevel() >= 10 )
	{
		NicknameInfo* pLevelNickInfo = m_pNicknameBook->getNicknameInfo(1);
		if ( pLevelNickInfo == NULL )
		{
			pLevelNickInfo = new NicknameInfo;
			pLevelNickInfo->setNicknameID( 1 );
			pLevelNickInfo->setNicknameType( NicknameInfo::NICK_BUILT_IN );
			pLevelNickInfo->setNicknameIndex( 0 );
			m_pNicknameBook->setNicknameInfo( 1, pLevelNickInfo );
		}

		if ( pLevelNickInfo->getNicknameType() == NicknameInfo::NICK_BUILT_IN
				&& pLevelNickInfo->getNicknameIndex() != getLevel()/10 )
		{
			pLevelNickInfo->setNicknameIndex( getLevel()/10 );

			Packet* pNicknamePacket = m_pNicknameBook->getNicknameBookListPacket();
			getPlayer()->sendPacket( pNicknamePacket );
			SAFE_DELETE( pNicknamePacket );

			if ( pLevelNickInfo == m_pNickname )
			{
				GCModifyNickname gcMN;
				gcMN.setObjectID( getObjectID() );
				gcMN.setNicknameInfo( m_pNickname );
				getZone()->broadcastPacket( getX(), getY(), &gcMN );
			}
		}
	}

#ifdef __TEST_SERVER__
	if ( getLevel() >= 150 )
	{
		increaseAdvancementClassExp(1);
		GCModifyInformation gcMI;
		gcMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel());
		gcMI.addLongData(MODIFY_ADVANCEMENT_CLASS_GOAL_EXP, getAdvancementClassGoalExp());
		getPlayer()->sendPacket( &gcMI );

		GCOtherModifyInfo gcOMI;
		gcOMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel());
		getZone()->broadcastPacket(getX(), getY(), &gcOMI, this);
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ °¹¼ö ¼¼ÆÃÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::setStashNumEx(BYTE num)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	setStashNum(num);

	BEGIN_DB
	{
		StringStream sqlSlayer;
		StringStream sqlVampire;
		StringStream sqlOusters;

		sqlSlayer << "UPDATE Slayer set StashNum = " << (int)num
			<< " WHERE Name = '" << getName() << "'";
		sqlVampire << "UPDATE Vampire set StashNum = " << (int)num
			<< " WHERE Name = '" << getName() << "'";
		sqlOusters << "UPDATE Ousters set StashNum = " << (int)num
			<< " WHERE Name = '" << getName() << "'";

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQueryString(sqlSlayer.toString());
		if ( !isOusters() )
			pStmt->executeQueryString(sqlVampire.toString());
		else
			pStmt->executeQueryString(sqlOusters.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ¿¡ µé¾îÀÖ´Â µ· ¼¼ÆÃÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::setStashGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY

	//cout << "setStashGoldEx Called" << "Name:" << getName() << " Gold: " << (int)gold << endl;
	Statement* pStmt = NULL;

	setStashGold(gold);

	BEGIN_DB
	{
		StringStream sqlSlayer;
		StringStream sqlVampire;
		StringStream sqlOusters;

		sqlSlayer << "UPDATE Slayer set StashGold = " << (int)gold
			<< " WHERE Name = '" << getName() << "'";
		sqlVampire << "UPDATE Vampire set StashGold = " << (int)gold
			<< " WHERE Name = '" << getName() << "'";
		sqlOusters << "UPDATE Ousters set StashGold = " << (int)gold
			<< " WHERE Name = '" << getName() << "'";

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQueryString(sqlSlayer.toString());
		if ( !isOusters() )
			pStmt->executeQueryString(sqlVampire.toString());
		else
			pStmt->executeQueryString(sqlOusters.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ¿¡ µé¾îÀÖ´Â µ· ¼¼ÆÃÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::increaseStashGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	setStashGold(m_StashGold + gold);

	BEGIN_DB
	{
		StringStream sqlSlayer;
		StringStream sqlVampire;
		StringStream sqlOusters;

		sqlSlayer << "UPDATE Slayer set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";
		sqlVampire << "UPDATE Vampire set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";
		sqlOusters << "UPDATE Ousters set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQueryString(sqlSlayer.toString());
		if ( !isOusters() )
			pStmt->executeQueryString(sqlVampire.toString());
		else
			pStmt->executeQueryString(sqlOusters.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ¿¡ µé¾îÀÖ´Â µ· ¼¼ÆÃÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::decreaseStashGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	setStashGold(m_StashGold - gold);

	BEGIN_DB
	{
		StringStream sqlSlayer;
		StringStream sqlVampire;
		StringStream sqlOusters;

		sqlSlayer << "UPDATE Slayer set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";
		sqlVampire << "UPDATE Vampire set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";
		sqlOusters << "UPDATE Ousters set StashGold = " << (int)m_StashGold
			<< " WHERE Name = '" << getName() << "'";

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQueryString(sqlSlayer.toString());
		if ( !isOusters() )
			pStmt->executeQueryString(sqlVampire.toString());
		else
			pStmt->executeQueryString(sqlOusters.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// º¸°üÇÔ ¸Þ¸ð¸®¿¡¼­ »èÁ¦ÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::deleteStash(void)
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pStash);
	m_StashNum = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ÇÃ·¡±×¼Â ¸Þ¸ð¸®¿¡¼­ »èÁ¦ÇÏ±â
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::deleteFlagSet(void)
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pFlagSet);

	__END_CATCH
}

//----------------------------------------------------------------------
// ¼±°øÀÚÀÇ ¸®½ºÆ®¿¡ ¼±°øÀÚ¸¦ Ãß°¡ÇÏ´Â ÇÔ¼ö
//----------------------------------------------------------------------
void PlayerCreature::addEnemy(const string& Name)
	
{
	__BEGIN_DEBUG

	list<string>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , Name);

	// ¾ø´Ù¸é Ãß°¡ÇÏÀÚ
	if (itr == m_Enemies.end()) 
	{
		m_Enemies.push_back(Name);
		//cout << "¼±°øÀÚ¸¦ Ãß°¡ÇÑ´Ù : " << Name << endl;
	}

	__END_DEBUG
}

//----------------------------------------------------------------------
// ¼±°øÀÚÀÇ ¸®½ºÆ®¿¡ ¼±°øÀÚ¸¦ »èÁ¦ÇÏ´Â ÇÔ¼ö
//----------------------------------------------------------------------
void PlayerCreature::deleteEnemy(const string& Name)
	
{
	__BEGIN_DEBUG

    list<string>::iterator itr = find(m_Enemies.begin(), m_Enemies.end() , Name);
	if (itr != m_Enemies.end()) 
	{
		m_Enemies.erase(itr);
		//cout << "¼±°øÀÚ¸¦ Áö¿î´Ù : " << Name << endl;
	}

	__END_DEBUG
}

//----------------------------------------------------------------------
// Æ¯Á¤ ÀÌ¸§À» °¡Áø ¼±°øÀÚ°¡ ÀÌ¹Ì ÀÖ´ÂÁö ¾ø´ÂÁö È®ÀÎÇÏ´Â ÇÔ¼ö.
//----------------------------------------------------------------------
bool PlayerCreature::hasEnemy(const string& Name)
	const 
{
	__BEGIN_DEBUG

    list<string>::const_iterator itr = find(m_Enemies.begin(), m_Enemies.end() , Name);
	if (itr != m_Enemies.end()) 
	{
		//cout << "¼±°øÀÚ·Î ÀÌ¹Ì ¼³Á¤ÀÌ µÇ¾îÀÖ´Ù : " << Name << endl;
		return true;
	} 
	else 
	{
		return false;
	}

	__END_DEBUG
}

//----------------------------------------------------------------------
// ±æµå ÀÌ¸§À» °¡Á®¿À´Â ÇÔ¼ö
//----------------------------------------------------------------------
string PlayerCreature::getGuildName() const
	
{
	Guild* pGuild = g_pGuildManager->getGuild( m_GuildID );
	
	if ( pGuild != NULL )
		return pGuild->getName();

	return "";
}

//----------------------------------------------------------------------
// ±æµå ¸â¹ö ·©Å©¸¦ °¡Á®¿À´Â ÇÔ¼ö
//----------------------------------------------------------------------
GuildMemberRank_t PlayerCreature::getGuildMemberRank() const
	
{
	Guild* pGuild = g_pGuildManager->getGuild( m_GuildID );

	if ( pGuild != NULL )
	{
		GuildMember* pGuildMember = pGuild->getMember( getName() );
		if ( pGuildMember != NULL )
		{
			return pGuildMember->getRank();
		}
	}

	return GuildMember::GUILDMEMBER_RANK_DENY;
}

Rank_t PlayerCreature::getRank() const  { return m_pRank->getLevel(); }
RankExp_t PlayerCreature::getRankExp() const  { return m_pRank->getTotalExp(); }
RankExp_t PlayerCreature::getRankGoalExp() const  { return m_pRank->getGoalExp(); }

RankBonus* PlayerCreature::getRankBonus( RankBonus::RankBonusType type ) const
	
{
	__BEGIN_TRY
	
	HashMapRankBonusConstItor itr = m_RankBonuses.find( type );

	if ( itr == m_RankBonuses.end() )
	{
		return NULL;
	}
	
	return itr->second;

	__END_CATCH
}

void PlayerCreature::addRankBonus( RankBonus* rankBonus )
	
{
	__BEGIN_TRY

	HashMapRankBonusItor itr = m_RankBonuses.find( rankBonus->getType() );

	if ( itr == m_RankBonuses.end() )
	{
		m_RankBonuses[rankBonus->getType()] = rankBonus;
		m_RankBonusFlag.set( rankBonus->getType() );
	}
	else
	{
		SAFE_DELETE( rankBonus );
	}

	__END_CATCH
}

void PlayerCreature::clearRankBonus()
	
{
	__BEGIN_TRY

	HashMapRankBonusItor itr = m_RankBonuses.begin();
	for ( ; itr != m_RankBonuses.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_RankBonuses.clear();
	m_RankBonusFlag.reset();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "DELETE FROM RankBonusData WHERE OwnerID = '%s'", getName().c_str() );
	}
	END_DB( pStmt )

	__END_CATCH
}

RankBonus* PlayerCreature::getRankBonusByRank( Rank_t rank ) const
	
{
	__BEGIN_TRY

	HashMapRankBonusConstItor itr = m_RankBonuses.begin();

	for ( ; itr != m_RankBonuses.end(); itr++ )
	{
		RankBonus* pLearnedRankBonus = itr->second;

		if ( rank == pLearnedRankBonus->getRank() )
		{
			return pLearnedRankBonus;
		}
	}

	return NULL;

	__END_CATCH
}

void PlayerCreature::clearRankBonus( Rank_t rank )
	
{
	__BEGIN_TRY

	RankBonus* pRankBonus = getRankBonusByRank( rank );
	if ( pRankBonus == NULL )
		return;

	DWORD rankBonusType = pRankBonus->getType();

	HashMapRankBonusItor itr = m_RankBonuses.find( rankBonusType );
	if ( itr != m_RankBonuses.end() )
	{
		m_RankBonusFlag.reset( rankBonusType );
		SAFE_DELETE( itr->second );
		m_RankBonuses.erase( itr );
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "DELETE FROM RankBonusData WHERE OwnerID = '%s' AND Type = %d", getName().c_str(), (int)rankBonusType );
	}
	END_DB( pStmt )

	__END_CATCH
}

bool PlayerCreature::learnRankBonus( DWORD type )
	
{
	//__BEGIN_TRY
	try
	{
	// °°Àº Rank ÀÇ Bonus °¡ ÀÖ´Ù¸é ¹è¿ï ¼ö ¾ø´Ù.
	HashMapRankBonusConstItor itr = m_RankBonuses.begin();

	RankBonusInfo* pRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo( type );

	// Á¾Á· °Ë»ç. 0ÀÌ ½½·¹ÀÌ¾î. 1ÀÌ ¹ìÆÄÀÌ¾î
	bool bValidRace = isSlayer() && pRankBonusInfo->getRace() == 0
						|| isVampire() && pRankBonusInfo->getRace() == 1
						|| isOusters() && pRankBonusInfo->getRace() == 2;

	// °è±Þ °Ë»ç
	if ( getRank() < pRankBonusInfo->getRank() )
		return false;

	if (!bValidRace)
		return false;

	for ( ; itr != m_RankBonuses.end(); itr++ )
	{
		RankBonus* pLearnedRankBonus = itr->second;

		if ( pRankBonusInfo->getRank() == pLearnedRankBonus->getRank() )
		{
			DWORD type = pLearnedRankBonus->getType();

			RankBonusInfo* pLearnedRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo( type );

			// °°Àº Á¾Á·ÀÇ °°Àº ¼öÁØÀÇ ±â¼úÀº ¸ø ¹è¿î´Ù.
			if ( pRankBonusInfo->getRace()==pLearnedRankBonusInfo->getRace())
			{
				return false;
			}
		}
	}
	
	RankBonus* rankBonus = new RankBonus( pRankBonusInfo->getType(), pRankBonusInfo->getPoint(), pRankBonusInfo->getRank() );

	addRankBonus( rankBonus );

	// DB ¿¡ Ãß°¡
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "INSERT INTO RankBonusData ( OwnerID, Type )  VALUES ( '%s', %d )", getName().c_str(), type );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return true;
	}
	catch (Throwable & t) 
	{ 
		filelog("PlayerCreature.txt","PlayerCreature.cpp INSERT INTO RankBonusData error!");
		return false;
	}
	
	//__END_CATCH
}

void PlayerCreature::sendRankBonusInfo()
	
{
	__BEGIN_TRY

	HashMapRankBonusConstItor itr = m_RankBonuses.begin();

	GCRankBonusInfo gcRankBonusInfo;

	for ( ; itr != m_RankBonuses.end(); itr++ )
	{
		gcRankBonusInfo.addListElement( itr->second->getType() );
	}

	m_pPlayer->sendPacket( &gcRankBonusInfo );

	__END_CATCH
}

void PlayerCreature::loadRankBonus()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT Type FROM RankBonusData WHERE OwnerID ='%s'", getName().c_str() );

		while ( pResult->next() )
		{
			DWORD rankBonusType = pResult->getInt(1);

			RankBonusInfo* pRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo( rankBonusType );

			if ( getRace() == pRankBonusInfo->getRace() )
			{
				RankBonus* pRankBonus = new RankBonus();

				pRankBonus->setType( rankBonusType );
				pRankBonus->setPoint( pRankBonusInfo->getPoint() );
				pRankBonus->setRank( pRankBonusInfo->getRank() );

				addRankBonus( pRankBonus );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		
	__END_CATCH
}

void PlayerCreature::increaseRankExp(RankExp_t Point)
{
	if (Point <= 0) return;

	// PK Á¸ ¾È¿¡¼­´Â °æÇèÄ¡¸¦ ÁÖÁö ¾Ê´Â´Ù.
	if ( g_pPKZoneInfoManager->isPKZone( getZoneID() ) )
		return;

	// ´ÙÀÌ³ª¹Í Á¸ ¾È¿¡¼­´Â °æÇèÄ¡¸¦ ÁÖÁö ¾Ê´Â´Ù.
	if ( m_pZone != NULL && m_pZone->isDynamicZone() )
		return;

	if ( isFlag( Effect::EFFECT_CLASS_BONUS_EXP ) ) Point*=2;

	if ( m_pRank->increaseExp(Point) )
	{
		char pField[80];
		sprintf(pField, "`Rank`=%u, RankExp=%lu, RankGoalExp=%lu",
				getRank(), getRankExp(), getRankGoalExp());
		tinysave(pField);
		setRankExpSaveCount(0);

		GCModifyInformation gcModifyInformation;
		gcModifyInformation.addLongData(MODIFY_RANK, getRank());
		m_pPlayer->sendPacket(&gcModifyInformation);

		if (m_pZone != NULL)
		{
			GCOtherModifyInfo gcOtherModifyInfo;
			gcOtherModifyInfo.setObjectID(getObjectID());
			gcOtherModifyInfo.addShortData(MODIFY_RANK, getRank());

			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}
	else
	{
		WORD rankExpSaveCount = getRankExpSaveCount();
		if (rankExpSaveCount > RANK_EXP_SAVE_PERIOD)
		{
			char pField[80];
			sprintf(pField, "RankExp=%lu, RankGoalExp=%lu", getRankExp(), getRankGoalExp());
			tinysave(pField);

			rankExpSaveCount = 0;
		}
		else rankExpSaveCount++;
		setRankExpSaveCount(rankExpSaveCount);

		// °è±Þ °æÇèÄ¡¸¦ º¸³»ÁØ´Ù. by sigi. 2002.9.13
		GCModifyInformation gcModifyInformation;
		gcModifyInformation.addLongData(MODIFY_RANK_EXP, getRankGoalExp());
		m_pPlayer->sendPacket(&gcModifyInformation);
	}
}

bool PlayerCreature::isBillingPlayAvaiable() 
	
{
	__BEGIN_TRY

	if (m_pPlayer==NULL)
		return false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
	Assert(pGamePlayer!=NULL);

	return pGamePlayer->isBillingPlayAvaiable();

	__END_CATCH
}


bool PlayerCreature::isPayPlayAvaiable() 
	
{
	__BEGIN_TRY

	if (m_pPlayer==NULL)
		return false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
	return pGamePlayer->isPayPlaying();

	__END_CATCH
}


bool PlayerCreature::canPlayFree()
	
{
	return false;
}

void PlayerCreature::loadGoods()
	
{
	__BEGIN_TRY
	
	Statement* pStmt = NULL;
	Result* pResult = NULL;

	if ( m_pGoodsInventory->getNum() != 0 )
	{
		filelog("GoodsReload.log", "¸¶ÄÏ¾ÆÅÛ ¸®·Îµå Çß³Ä? : %s", getName().c_str() );
		m_pGoodsInventory->clear();
	}

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

		pResult = pStmt->executeQuery( "SELECT ID, GoodsID, Num FROM GoodsListObject WHERE World = %d AND PlayerID = '%s' AND Name = '%s' AND Status = 'NOT'",
										g_pConfig->getPropertyInt("WorldID"),
										getPlayer()->getID().c_str(),
										getName().c_str() );

		while ( pResult->next() )
		{
			string ID = pResult->getString(1);
			DWORD goodsID = pResult->getInt(2);
			int num = pResult->getInt(3);

			for ( int i = 0; i < max(1,min(50,num)) ; i++ )
			{
				Item* pItem = createItemByGoodsID( goodsID );
				if ( pItem != NULL )
				{
					m_pGoodsInventory->addItem( ID, pItem );
				}
			}
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}


/*void	PlayerCreature::loadQuest() 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__

	SimpleQuestLoader::getInstance()->load( this );
	
#endif

	__END_CATCH
}

bool    PlayerCreature::addQuest(Quest* pQuest) 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__
	if (m_pQuestManager==NULL)
	{
		m_pQuestManager = new QuestManager;
	}

	if (m_pQuestManager->addQuest( pQuest ))
	{
		return true;
	}

#endif
	__END_CATCH

	SAFE_DELETE(pQuest);

	return false;
}

bool    PlayerCreature::checkEvent(QuestEvent* pQuestEvent) 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__

	if (m_pQuestManager!=NULL)
	{
		Quest* pCompleteQuest = m_pQuestManager->checkEvent( pQuestEvent );

		if (pCompleteQuest!=NULL)
		{
			//cout << "[Complete] " << pCompleteQuest->toString().c_str() << endl;
			return true;
		}
	}

#endif

	return false;

	__END_CATCH
}

Quest*  PlayerCreature::removeCompleteQuest() 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__

	if (m_pQuestManager!=NULL)
	{
		Quest* pQuest = m_pQuestManager->removeCompleteQuest();

		return pQuest;
	}

#endif

	__END_CATCH

	return NULL;
}*/
/*
bool PlayerCreature::deleteItemNameInfoList( ObjectID_t objectID ) 
	
{
	__BEGIN_TRY

	list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin();
	
	for( ; itr != m_ItemNameInfoList.end() ; itr++ )
	{
		ItemNameInfo* pInfo = *itr;
		if( pInfo->getObjectID() == objectID )
		{
			SAFE_DELETE( pInfo );
			m_ItemNameInfoList.erase( itr );

			return true;
		}
	}

	return false;

	__END_CATCH
}

string PlayerCreature::getItemName( ObjectID_t objectID ) 
	
{
	__BEGIN_TRY

	list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin();
	
	for( ; itr != m_ItemNameInfoList.end() ; itr++ )
	{
		ItemNameInfo* pInfo = *itr;
		if( pInfo->getObjectID() == objectID )
		{
			return pInfo->getName();
		}
	}

	return NULL;

	__END_CATCH
}
*/

void PlayerCreature::addDefaultOptionSet( DefaultOptionSetType_t type )
	
{
	// ÀÌ¹Ì ÀÖ´Â °ÍÀÎÁö È®ÀÎÇÑ´Ù.
	forward_list<DefaultOptionSetType_t>::iterator itr = m_DefaultOptionSet.begin();
	for ( ; itr != m_DefaultOptionSet.end(); itr++ )
	{
		if ( (*itr) == type )
			return;
	}

	m_DefaultOptionSet.push_front( type );
}

void PlayerCreature::removeDefaultOptionSet( DefaultOptionSetType_t type )
	
{
	forward_list<DefaultOptionSetType_t>::iterator before = m_DefaultOptionSet.end();
	forward_list<DefaultOptionSetType_t>::iterator current = m_DefaultOptionSet.begin();

	for ( ; current != m_DefaultOptionSet.end(); before = current++ )
	{
		if ( (*current) == type )
		{
			// ¹ß°ßÇß´Ù.
			if ( before == m_DefaultOptionSet.end() )
			{
				// delete first node
				m_DefaultOptionSet.pop_front();
			}
			else
			{
				m_DefaultOptionSet.erase_after(before);
			}

			return;
		}
	}

	// ¹ß°ß¸øÇß´Ù.
}

PetInfo* PlayerCreature::getPetInfo() const
{
	return m_pPetInfo;
}

void PlayerCreature::setPetInfo(PetInfo* pPetInfo)
{
	m_pPetInfo = pPetInfo;
	SAFE_DELETE( m_pPet );
	m_pPet = Pet::makePet(this, m_pPetInfo);
}

void PlayerCreature::heartbeat(const Timeval& currentTime) 
{
	if ( m_pPet != NULL ) m_pPet->heartbeat( currentTime );
	m_pGQuestManager->heartbeat();
}


GCMonsterKillQuestInfo::QuestInfo*	PlayerCreature::getPetQuestInfo() const
{
	GCMonsterKillQuestInfo::QuestInfo* pQI = new GCMonsterKillQuestInfo::QuestInfo;

	pQI->questID = PET_QUEST_ID;
	pQI->sType = m_TargetMonster;
	pQI->goal = m_TargetNum;
	pQI->timeLimit = m_TimeLimit;

	return pQI;
}

void	PlayerCreature::addPetStashItem(int idx, Item* pPetItem)
{
	Assert( pPetItem == NULL || pPetItem->getItemClass() == Item::ITEM_CLASS_PET_ITEM );
	Assert( idx >= 0 && idx <= MAX_PET_STASH );
	m_PetStash[idx] = pPetItem;
}

Item*	PlayerCreature::getPetStashItem(int idx)
{
	Assert( idx >= 0 && idx <= MAX_PET_STASH );
	return m_PetStash[idx];
}

bool PlayerCreature::canSee( Object* pObject ) const
{
	if ( pObject->getObjectClass() == OBJECT_CLASS_CREATURE )
	{
		return ::canSee( this, dynamic_cast<Creature*>(pObject) );
	}
	else
	{
		return true;
	}
}

Level_t PlayerCreature::getAdvancementClassLevel() const { return m_pAdvancementClass->getLevel(); }
Exp_t PlayerCreature::getAdvancementClassGoalExp() const { return m_pAdvancementClass->getGoalExp(); }
bool PlayerCreature::increaseAdvancementClassExp(Exp_t exp, bool bApplyExpBonus)
{
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
	if ( pGamePlayer != NULL )
	{
		if ( bApplyExpBonus
			&& (pGamePlayer->isPremiumPlay() || pGamePlayer->isFamilyFreePass())
			)
		{
			exp = getPercentValue( exp, g_pVariableManager->getPremiumExpBonusPercent() );
		}

		if( bApplyExpBonus
			&& g_pVariableManager->getExpRatio() > 100
			&& g_pVariableManager->getEventActivate() == 1)
		{
			exp = getPercentValue(exp, g_pVariableManager->getExpRatio());
		}

		if ( bApplyExpBonus && isAffectExp2X() )
		{
			// °æÇèÄ¡ µÎ¹è
			//exp <<= 1;
			exp=2*exp;
		}
		//chengh modify 2006 07 21 ,ÐÞ¸ÄÉ³Â©Ë«±¶ÎÞÐ§´íÎó
		if ( isFlag( Effect::EFFECT_CLASS_BONUS_EXP ) ) 
		{
			exp*= 2;
		}
	}

	cout << getName() << "¿¡°Ô ½ÂÁ÷ °æÇèÄ¡ " << (int)exp << "¸¸Å­ ÁÝ´Ï´Ù." << endl;
	Level_t prevLevel = getAdvancementClassLevel();
	bool ret = m_pAdvancementClass->increaseExp( exp, true, true );
	if ( getAdvancementClassLevel() > 0 ) m_bAdvanced = true;
	Level_t nextLevel = getAdvancementClassLevel();
	cout << getName() << "ÀÌ " << (int)prevLevel << " ¿¡¼­ " << (int)nextLevel << " ÀÌ µÇ¾ú½À´Ï´Ù." << endl;

	if ( prevLevel != nextLevel )
	{
		Bonus_t bonus = getBonus();
		Level_t _4pointstart = min((int)prevLevel, 50);
		Level_t _4pointend = min((int)nextLevel, 50);
		Level_t _5pointstart = max((int)prevLevel, 50);
		Level_t _5pointend = max((int)nextLevel, 50);

		Bonus_t bonusdiff = (( _4pointend - _4pointstart ) * 4) + (( _5pointend - _5pointstart ) * 5);
		cout << getName() << "¿¡°Ô " << (int)bonusdiff << "¸¸Å­ ´É·ÂÄ¡ ÁÝ´Ï´Ù." << endl;
		bonus += bonusdiff;
		setBonus( bonus );

		StringStream sav;
		sav << "AdvancementClass = " << (int)nextLevel 
			<< ",AdvancementGoalExp = " << (int)getAdvancementClassGoalExp() 
			<< ",Bonus = " << (int)getBonus();

		tinysave( sav.toString() );
		initAllStatAndSend();
	}
	else
	{
		m_AdvancementClassExpSaveCount++;
		if ( m_AdvancementClassExpSaveCount > 100 )
		{
			StringStream sav;
			sav << "AdvancementClass = " << (int)getAdvancementClassLevel() 
				<< ",AdvancementGoalExp = " << (int)getAdvancementClassGoalExp();
			tinysave( sav.toString() );
			m_AdvancementClassExpSaveCount = 0;
		}
	}

	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_ADVANCEMENT_CLASS_GOAL_EXP, getAdvancementClassGoalExp() );
	if ( ret )
	{
		gcMI.addShortData( MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel() );
		gcMI.addShortData( MODIFY_BONUS_POINT, getBonus() );
		m_pGQuestManager->advancementClassLevelUp();
	}

	getPlayer()->sendPacket( &gcMI );

	return ret;
}

bool PlayerCreature::putAdvancedBonusToSTR()
{
	if ( m_AdvancedAttrBonus <= 0 ) return false;
	m_AdvancedAttrBonus--;
	m_AdvancedSTR++;
	return true;
}

bool PlayerCreature::putAdvancedBonusToDEX()
{
	if ( m_AdvancedAttrBonus <= 0 ) return false;
	m_AdvancedAttrBonus--;
	m_AdvancedDEX++;
	return true;
}

bool PlayerCreature::putAdvancedBonusToINT()
{
	if ( m_AdvancedAttrBonus <= 0 ) return false;
	m_AdvancedAttrBonus--;
	m_AdvancedINT++;
	return true;
}
bool PlayerCreature::canChangeMasterEffectColor()
{
	// MasterEffectColor 5 ´Â ±æµåÀü ¿ì½ÂÀÚµéÇÑÅ× ÁÖ´Â ¸¶½ºÅÍ ÀÌÆåÆ®´Ù
	// »óÁ¡ÀÇ ¸¶½ºÅÍ ÀÌÆåÆ® º¯È¯ ¾ÆÀÌÅÛÀ¸·Î ÀÌ ÀÌÆåÆ®¿¡¼­ ´Ù¸¥ ÀÌÆåÆ®·Î º¯°æÇÒ ¼ö ¾ø´Ù.
	// 2005.05.17 by bezz
	return m_MasterEffectColor != 5;
}
