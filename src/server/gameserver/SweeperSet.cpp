#include "SweeperSet.h"
#include "MonsterCorpse.h"

#include "DB.h"
#include "Zone.h"

#include "Item.h"
#include "ItemFactoryManager.h"

#include "SweeperBonus.h"
#include "SweeperBonusManager.h"
#include "EffectKeepSweeper.h"
#include "GlobalItemPosition.h"
#include "CorpseItemPosition.h"
#include "GlobalItemPositionLoader.h"

#include "Utility.h"
#include "ZoneUtil.h"

#include "Gpackets/GCAddEffect.h"

MonsterCorpse* SweeperSet::getSweeperSafes( uint itemType )
{
	map<uint, MonsterCorpse*>::iterator itr = m_SweeperSafes.find( itemType );
	if ( itr == m_SweeperSafes.end() )
		return NULL;
	else 
		return itr->second;
}

bool SweeperSet::isSafe( MonsterCorpse* pCorpse ) const
{
	map<uint, MonsterCorpse*>::const_iterator itr = m_SweeperSafes.begin();
	map<uint, MonsterCorpse*>::const_iterator endItr = m_SweeperSafes.end();

	for ( ; itr != endItr ; itr++ )
	{
		if ( itr->second == pCorpse ) return true;
	}

	return false;
}

int SweeperSet::getType( MonsterCorpse* pCorpse ) const
{
	map<uint, MonsterCorpse*>::const_iterator itr = m_SweeperSafes.begin();
	map<uint, MonsterCorpse*>::const_iterator endItr = m_SweeperSafes.end();

	for ( ; itr != endItr ; itr++ )
	{
		if ( itr->second == pCorpse ) return itr->first;
	}

	return -1;
}

SweeperSetManager::~SweeperSetManager()
{
	map<uint, SweeperSet*>::iterator itr = m_SweeperSets.begin();
	map<uint, SweeperSet*>::iterator endItr = m_SweeperSets.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( itr->second );
	}

	m_SweeperSets.clear();
}

void SweeperSetManager::load(int level, Zone* pZone)
{
	m_SweeperSets.clear();

	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;

	m_SweeperSets[0] = new SweeperSet(SweeperSet::SWEEPER_SLAYER);
	m_SweeperSets[1] = new SweeperSet(SweeperSet::SWEEPER_VAMPIRE);
	m_SweeperSets[2] = new SweeperSet(SweeperSet::SWEEPER_OUSTERS);
	m_SweeperSets[3] = new SweeperSet(SweeperSet::SWEEPER_DEFAULT);

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT ItemType, "
				"SlayerX, SlayerY, SlayerMType, "
				"VampireX, VampireY, VampireMType, "
				"OustersX, OustersY, OustersMType, "
				"DefaultX, DefaultY, DefaultMType, "
				"Name "
				"FROM SweeperSetInfo WHERE ZoneID = %d", pZone->getZoneID() );

		while( pResult->next() )
		{
			ItemType_t ItemType = pResult->getInt(1);

			ZoneCoord_t SlayerX = pResult->getInt(2);
			ZoneCoord_t SlayerY = pResult->getInt(3);
			MonsterType_t SlayerMType = pResult->getInt(4);

			ZoneCoord_t VampireX = pResult->getInt(5);
			ZoneCoord_t VampireY = pResult->getInt(6);
			MonsterType_t VampireMType = pResult->getInt(7);

			ZoneCoord_t OustersX = pResult->getInt(8);
			ZoneCoord_t OustersY = pResult->getInt(9);
			MonsterType_t OustersMType = pResult->getInt(10);

			ZoneCoord_t DefaultX = pResult->getInt(11);
			ZoneCoord_t DefaultY = pResult->getInt(12);
			MonsterType_t DefaultMType = pResult->getInt(13);

//			uint OwnerID = pResult->getInt(14);
//			Assert( OwnerID < 4 );

//			SweeperSet::SweeperIndex Owner = (SweeperSet::SweeperIndex)OwnerID;

//			StringStream name;
//			name << "보관대" << (int)ItemType;

			string name = pResult->getString(14);

			MonsterCorpse* SlayerSafe = new MonsterCorpse( SlayerMType, name, 2 );
			MonsterCorpse* VampireSafe = new MonsterCorpse( VampireMType, name, 2 );
			MonsterCorpse* OustersSafe = new MonsterCorpse( OustersMType, name, 2 );
			MonsterCorpse* DefaultSafe = new MonsterCorpse( DefaultMType, name, 2 );
//			Item* Sweeper = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SWEEPER, ItemType, list<OptionType_t>() );

			SlayerSafe->setShrine(true);
			VampireSafe->setShrine(true);
			OustersSafe->setShrine(true);
			DefaultSafe->setShrine(true);

			pZone->registerObject( SlayerSafe );
			pZone->registerObject( VampireSafe );
			pZone->registerObject( OustersSafe );
			pZone->registerObject( DefaultSafe );
//			pZone->registerObject( Sweeper );

			pZone->addItem( SlayerSafe, SlayerX, SlayerY, true );
			pZone->addItem( VampireSafe, VampireX, VampireY, true );
			pZone->addItem( OustersSafe, OustersX, OustersY, true );
			pZone->addItem( DefaultSafe, DefaultX, DefaultY, true );

			forbidDarkness( pZone, SlayerX, SlayerY, 1 );
			forbidDarkness( pZone, VampireX, VampireY, 1 );
			forbidDarkness( pZone, OustersX, OustersY, 1 );
			forbidDarkness( pZone, DefaultX, DefaultY, 1 );

//			Assert( m_SweeperSets[ItemType] == NULL );
//			m_SweeperSets[ItemType] = new SweeperSet( SlayerSafe, VampireSafe, OustersSafe, DefaultSafe, Sweeper );

			m_SweeperSets[0]->addSafe( ItemType, SlayerSafe );
			m_SweeperSets[1]->addSafe( ItemType, VampireSafe );
			m_SweeperSets[2]->addSafe( ItemType, OustersSafe );
			m_SweeperSets[3]->addSafe( ItemType, DefaultSafe );

//			Assert( m_Sweepers[Sweeper->getItemType()] == NULL );
//			m_Sweepers[Sweeper->getItemType()] = Sweeper; 

//			MonsterCorpse* TargetSafe = m_SweeperSets[ItemType]->getSweeperSafes( Owner );
//			MonsterCorpse* TargetSafe = m_SweeperSets[Owner]->getLastSafe();

//			Sweeper->create( itos( pZone->getZoneID() ), STORAGE_CORPSE, TargetSafe->getObjectID(), 0, 0 );
//			TargetSafe->addTreasure( Sweeper );
		}

		pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult2 = pStmt2->executeQuery( "SELECT SweeperType, OwnerRace, SweeperSafeType FROM SweeperOwnerInfo WHERE ZoneID = %d" , pZone->getZoneID() );

		while( pResult2->next() )
		{
			int type = pResult2->getInt(1);
			int race = pResult2->getInt(2);
			Assert( race < 4 );
			int safeType = pResult2->getInt(3);

			Item* Sweeper = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SWEEPER, type, list<OptionType_t>() );
			pZone->registerObject( Sweeper );

			Assert( m_Sweepers[Sweeper->getItemType()] == NULL );
			m_Sweepers[Sweeper->getItemType()] = Sweeper; 

			MonsterCorpse* TargetSafe = m_SweeperSets[race]->getSweeperSafes( safeType );

			Assert( TargetSafe != NULL );

			Sweeper->create( itos( pZone->getZoneID() ), STORAGE_CORPSE, TargetSafe->getObjectID(), 0, 0 );
//			TargetSafe->addTreasure( Sweeper );
			putSweeper(Sweeper, TargetSafe);

		}

	}
	END_DB( pStmt )
}


int SweeperSetManager::getSafeIndex( MonsterCorpse* pSafe ) const
{
	map<uint, SweeperSet*>::const_iterator itr = m_SweeperSets.begin();
	map<uint, SweeperSet*>::const_iterator endItr = m_SweeperSets.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second->isSafe( pSafe ) ) return itr->first;
	}

	return -1;
}


/*bool SweeperSetManager::isFit( Item* pSweeper, MonsterCorpse* pSafe )
{
	map<ItemType_t, SweeperSet*>::iterator itr = m_SweeperSets.find( pSweeper->getItemType() );
	if ( itr == m_SweeperSets.end() ) return false;

	SweeperSet* pSweeperSet = itr->second;
	if ( pSweeperSet->getSweeper() != pSweeper ) return false;

	return pSweeperSet->findSafeIndex( pSafe ) != -1;
}
*/

bool SweeperSetManager::putSweeper( Item* pSweeper, MonsterCorpse* pSafe )
{
	Assert( pSweeper != NULL );
	Assert( pSafe != NULL );

	// Sweepr 를 넣는 사용자와 pSafe 의 종족이 같음은 위에서 확인했다고 가정한다
	if ( pSweeper->getItemClass() != Item::ITEM_CLASS_SWEEPER ) return false;
	if ( pSafe->getItemClass() != Item::ITEM_CLASS_CORPSE ) return false;
	if ( getSafeIndex( pSafe ) == -1 ) return false;
	if ( pSafe->isFlag( Effect::EFFECT_CLASS_KEEP_SWEEPER ) ) return false;

	SweeperSet* pSweeperSet = getSweeperSet( getSafeIndex( pSafe ) );
	if ( pSweeperSet == NULL ) return false;

	pSafe->addTreasure( pSweeper );
	pSafe->setFlag( Effect::EFFECT_CLASS_KEEP_SWEEPER );

	int safeType = pSweeperSet->getType( pSafe );
	if ( safeType == -1 ) return false;

	saveSweeperOwner( pSweeper->getItemType(), safeType, getSafeIndex( pSafe ) );

	g_pSweeperBonusManager->getSweeperBonus( pSweeper->getItemType() )->setRace( getSafeIndex( pSafe ) );

	EffectKeepSweeper* pEffect = new EffectKeepSweeper( pSafe );
	pEffect->setPart( pSweeper->getItemType() );
	pSafe->getEffectManager().addEffect( pEffect );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pSafe->getObjectID() );
	gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffect.setDuration( 65535 );

	pSafe->getZone()->broadcastPacket( pSafe->getX(), pSafe->getY(), &gcAddEffect );

	return true;
}

bool SweeperSetManager::returnAllSweeper()
{
	bool bReturned = false;

	map<ItemType_t, Item*>::const_iterator itr = m_Sweepers.begin();
	map<ItemType_t, Item*>::const_iterator endItr = m_Sweepers.end();

	for ( ; itr != endItr ; itr++ )
	{
		Item* pItem = itr->second;
		Assert( pItem != NULL );

		bReturned = returnSweeper( pItem->getItemID(), false ) || bReturned;
	}

	return bReturned;
}

bool SweeperSetManager::returnSweeper( ItemType_t sweeperID, bool bLock )
{
	Item::ItemClass ItemClass = Item::ITEM_CLASS_SWEEPER;

	GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( ItemClass, sweeperID );

	if ( pItemPosition == NULL ) return false;

	Item* pItem = pItemPosition->popItem( bLock );

	if (pItem!=NULL && pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{

		if ( pItemPosition->getType() == GlobalItemPosition::POS_TYPE_CORPSE )
		{
			CorpseItemPosition* pCorpseItemPosition = dynamic_cast<CorpseItemPosition*>(pItemPosition);
			Assert( pCorpseItemPosition != NULL );

			Zone* pZone = pCorpseItemPosition->getZone();
			Assert( pZone != NULL );

			Item* pItem2 = pZone->getItem( pCorpseItemPosition->getCorpseObjectID() );
			Assert( pItem2 != NULL );
				
			MonsterCorpse* pSafe = dynamic_cast<MonsterCorpse*>(pItem2);
			pSafe->addTreasure( pItem );

			return true;
		}

		Sweeper* pSweeper = dynamic_cast<Sweeper*>(pItem);
		Assert(pSweeper != NULL);

		MonsterCorpse* pDefaultSafe = getSweeperSet( 3 )->getSweeperSafes( pSweeper->getItemType() );
		if ( pDefaultSafe == NULL ) return false;

		return putSweeper( pSweeper, pDefaultSafe );

//		return returnSweeper( pZone, pSweeper );
	}

	return false;
}

/*
bool SweeperSetManager::returnSweeper( Zone* pZone, Sweeper* pSweeper ) const
{
	Assert( pZone != NULL );
	Assert( pSweeper != NULL );

	MonsterCorpse* pDefaultSafe = getSweeperSet( 3 )->getSweeperSafes( pSweeper->getItemType() );
	if ( pDefaultSafe == NULL ) return false;

	Zone* pTargetZone = pDefaultSafe->getZone();
	if ( pTargetZone == NULL ) return false;

	ObjectID_t CorpseObjectID = pDefaultSafe->getObjectID();

	// Default Safe 로 옮기고 소유한 종족에 대한 것도 저장해야 한다
//	pZone->transportItemToCorpse( pSweeper, pTargetZone, CorpseObjectID );

	SweeperSet* pSweeperSet = getSweeperSet( 3 );
	Assert(pSweeperSet != NULL );

	MonsterCorpse* pSafe = pSweeperSet->getSweeperSafes( pSweeperSet->getItemType() );

	putSweeper( pSweeper, pSafe );

	return true;
}
*/

void SweeperSetManager::saveSweeperOwner( uint itemType, int safeType, int ownerRace )
{
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE SweeperOwnerInfo SET OwnerRace = %ld, SweeperSafeType = %d WHERE SweeperType = %d", ownerRace, safeType, itemType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
}

