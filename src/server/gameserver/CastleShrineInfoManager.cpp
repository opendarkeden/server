#include <stdio.h>
#include "CastleShrineInfoManager.h"
#include "StringStream.h"
#include "DB.h"
#include "ZoneItemPosition.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "MonsterCorpse.h"
#include "Item.h"
#include "ItemFactoryManager.h"
#include "EffectShrineGuard.h"
#include "EffectShrineHoly.h"
#include "EffectShrineShield.h"
#include "War.h"
#include "WarSystem.h"
#include "RelicUtil.h"
#include "CastleInfoManager.h"
#include "GlobalItemPosition.h"
#include "GlobalItemPositionLoader.h"
#include "ZoneGroupManager.h"
#include "Player.h"
#include "GuildWar.h"
#include "PlayerCreature.h"
#include "CreatureUtil.h"
#include "StringPool.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteInventoryItem.h"

#include "CastleSymbol.h"

string CastleShrineSet::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ShrineSet("
		<< "ShrineID:" << (int)m_ShrineID
		<< ","
		<< m_GuardShrine.toString()
		<< ","
		<< m_HolyShrine.toString()
		<< ",ItemType:" << (int)m_ItemType
		<< ")";

	return msg.toString();

	__END_CATCH
}

CastleShrineInfoManager::~CastleShrineInfoManager()
{
	clear();
}

void CastleShrineInfoManager::clear()
{
	HashMapShrineSetItor itr = m_ShrineSets.begin();
	for ( ; itr != m_ShrineSets.end() ; itr++ )
	{
		SAFE_DELETE( itr->second );
	}
	m_ShrineSets.clear();
}

void CastleShrineInfoManager::init()
	
{ 
	__BEGIN_TRY

	load();

	addAllShrineToZone();

	__END_CATCH
}

void CastleShrineInfoManager::load()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pResult = pStmt->executeQuery( "SELECT ID, Name, ItemType, GuardZoneID, GuardX, GuardY, GuardMType, HolyZoneID, HolyX, HolyY, HolyMType FROM CastleShrineInfo" );

		while ( pResult->next() )
		{
			int i = 0;

			CastleShrineSet* pShrineSet = new CastleShrineSet();

			pShrineSet->m_ShrineID = pResult->getInt( ++i );
			pShrineSet->m_GuardShrine.setName( pResult->getString( ++i ) );
			pShrineSet->m_HolyShrine.setName( pShrineSet->m_GuardShrine.getName() );
			pShrineSet->m_ItemType = pResult->getInt( ++i );
			pShrineSet->m_GuardShrine.setZoneID( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setX( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setY( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setMonsterType( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setZoneID( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setX( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setY( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setMonsterType( pResult->getInt( ++i ) );

			pShrineSet->m_GuardShrine.setShrineType( ShrineInfo::SHRINE_GUARD );
			pShrineSet->m_HolyShrine.setShrineType( ShrineInfo::SHRINE_HOLY );

			// ItemType과 Shrine ID는 같아야 한다. 같지 않을 경우 DB설정 오류로 로딩과정에서 막는다.
			if ( pShrineSet->m_ItemType != pShrineSet->m_ShrineID )
			{
				cout << "ShrineID 와 ItemType이 맞지 않습니다. DB설정을 점검하세요." << endl;
				Assert( false );
			}

			addShrineSet( pShrineSet );
		}
	}
	END_DB( pStmt )

	__END_CATCH
}

ZoneID_t CastleShrineInfoManager::getGuardShrineZoneID( ZoneID_t castleZoneID ) const 
	
{
	__BEGIN_TRY

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	// castleZoneID의 shrineID를 검색할수가 없어서 하나하나 비교한다. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
		ZoneID_t guardCastleZoneID;

		if (g_pCastleInfoManager->getCastleZoneID(guardZoneID, guardCastleZoneID))
		{
			if (castleZoneID==guardCastleZoneID)
			{
				return guardZoneID;
			}
		}
	}

	StringStream msg;
	msg << "CastleZoneID와 관련된 GuardZoneID가 없다[" << (int)castleZoneID  << "]";
	throw Error(msg.toString());

	__END_CATCH
}

void CastleShrineInfoManager::addAllShrineToZone()
	
{
	__BEGIN_TRY

	HashMapShrineSetItor itr = m_ShrineSets.begin();
	for ( ; itr != m_ShrineSets.end() ; itr++ )
	{
		CastleShrineSet* pShrineSet = itr->second;

		if ( pShrineSet == NULL ) continue;

		Item* pItem = addShrineToZone( pShrineSet->m_GuardShrine, pShrineSet->m_ItemType );
		
		if (pItem==NULL)
		{
			pShrineSet->setCastleSymbolItemID( 0 );
		}
		else
		{
			pShrineSet->setCastleSymbolItemID( pItem->getItemID() );
		}

		addShrineToZone( pShrineSet->m_HolyShrine, pShrineSet->m_ItemType );
	}

	__END_CATCH
}

Item* CastleShrineInfoManager::addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType )
	
{
	__BEGIN_TRY

	// 성단을 넣을 존을 가져온다.
	Zone* pZone = getZoneByZoneID( shrineInfo.getZoneID() );
	Assert( pZone != NULL );

	MonsterCorpse* pShrine = new MonsterCorpse( shrineInfo.getMonsterType(), shrineInfo.getName(), 2 );
	Assert( pShrine != NULL );

	pShrine->setShrine( true );
	pShrine->setZone( pZone );

	pZone->getObjectRegistry().registerObject( pShrine );
	shrineInfo.setObjectID( pShrine->getObjectID() );

	cout << "AddShrine[" << (int)shrineInfo.getZoneID() << "] " 
			<< (shrineInfo.getShrineType()==ShrineInfo::SHRINE_GUARD? "Guard":"Holy")
			<< ", mtype=" << shrineInfo.getMonsterType()
			<< ", oid=" << pShrine->getObjectID() << endl;

	Item* pItem =  NULL;

/*	if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_GUARD )
	{
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_GUARD );

		EffectShrineGuard* pEffect = new EffectShrineGuard(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}
	else if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_HOLY )
	{
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_HOLY );

		EffectShrineHoly* pEffect = new EffectShrineHoly(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}*/

	TPOINT tp = pZone->addItem( pShrine, shrineInfo.getX(), shrineInfo.getY(), true );
	Assert( tp.x != -1 );

	// 성의 상징을 추가할 필요가 있다면 추가한다.
	if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_GUARD )
	{
		//if ( AddBible[ itemType ] )
		{
			list<OptionType_t> optionNULL;
			pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_CASTLE_SYMBOL, itemType, optionNULL );
			Assert( pItem != NULL );

			char strZoneID[10];
			sprintf(strZoneID, "%d", (int)pZone->getZoneID());

			pZone->registerObject( pItem );
			pItem->create( strZoneID, STORAGE_CORPSE, pShrine->getObjectID(), 0, 0 );

			pShrine->addTreasure( pItem );
		}

		// 수호성단이라는걸 표시해둔다.
		pShrine->setFlag( Effect::EFFECT_CLASS_CASTLE_SHRINE_GUARD );

		// 모든 수호성단에 Shield Effect 붙인다
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_SHIELD );

		EffectShrineShield* pEffect = new EffectShrineShield(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}
	else
	{
		// 성지성단이라는걸 표시해둔다.
		pShrine->setFlag( Effect::EFFECT_CLASS_CASTLE_SHRINE_HOLY );
	}

	// 성단 좌표를 새로 세팅한다.
	shrineInfo.setX( tp.x );
	shrineInfo.setY( tp.y );

	return pItem;

	__END_CATCH
}

void CastleShrineInfoManager::addShrineSet( CastleShrineSet* pShrineSet )
	
{
	__BEGIN_TRY

	if ( pShrineSet == NULL ) return;

	ShrineID_t shrineID = pShrineSet->m_ShrineID;

	HashMapShrineSetItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		filelog( "ShrineInfoError.log", "CastleShrineInfoManager::addShrineSet DuplicatedException : %d", (int)shrineID );
		return;
	}

	m_ShrineSets[ shrineID ] = pShrineSet;

	__END_CATCH
}

void CastleShrineInfoManager::deleteShrineSet( ShrineID_t shrineID )
	
{
	__BEGIN_TRY

	HashMapShrineSetItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		SAFE_DELETE( itr->second );
		m_ShrineSets.erase( shrineID );
	}
	
	__END_CATCH
}

CastleShrineSet* CastleShrineInfoManager::getShrineSet( ShrineID_t shrineID ) const
	
{
	__BEGIN_TRY

	HashMapShrineSetConstItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		return itr->second;
	}

	return NULL;

	__END_CATCH
}

bool CastleShrineInfoManager::isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) const
	
{
	__BEGIN_TRY

	if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL )
		return false;
	
	ItemType_t itemType = pItem->getItemType();
	ShrineID_t shrineID = itemType;					// ShrineID = ItemType(of CastleSymbol)

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );

	if( pShrineSet == NULL )
	{
		// 이 성의 상징에 해당하는 Shrine Set이 없다.
		return false;
	}

	// 이 성의 상징에 해당하는 Shrine set의 성지성단의 MonsterType이
	// 넘어온 MonsterCorpse의 MonsterType과 같고 ObjectID도 같으면 true
	return pShrineSet->m_HolyShrine.getMonsterType() == pMonsterCorpse->getMonsterType()
		&& pShrineSet->m_HolyShrine.getObjectID() == pMonsterCorpse->getObjectID();

	__END_CATCH
}

bool CastleShrineInfoManager::isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) const
	
{
	__BEGIN_TRY

	Zone* pZone = pShrine->getZone();
	Assert( pZone != NULL );

	// 성이 아니면 삑~
	/*
	if ( !pZone->isCastle() )
	{
		return false;
	}
	*/


	ZoneID_t guardZoneID = pZone->getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

	War* pWar = g_pWarSystem->getActiveWar( castleZoneID );
	if ( pWar == NULL )
		return false;

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
	if ( pCastleInfo == NULL )
		return false;

	/*
	if ( pWar->getWarType() == WAR_RACE )
	{
		// 종족 전쟁 중에는 성의 소유 종족과 같은 종족이면 defender 이다.
		if ( pPC->getRace() == pCastleInfo->getRace() )
			return true;
	}
	else 
	*/
	if ( pWar->getWarType() == WAR_GUILD )
	{
		GuildWar* pGuildWar = dynamic_cast<GuildWar*>(pWar);
		Assert(pGuildWar!=NULL);

		if ( pCastleInfo->isCommon() )
		{
			// 공용성인 경우는 공격길드만 아니면 defender이다.
			return pPC->getGuildID()!=pGuildWar->getChallangerGuildID();
		}
		else
		{
			// 동족 전쟁 중에는 공용성이 아닐 경우 성의 소유 길드가 defender 이다.
			if ( pPC->getGuildID() == pCastleInfo->getGuildID() )
				return true;
		}
	}

	return false;

	__END_CATCH
}

// 이 종족이 성의 상징 조각을 들 수 있는가?
bool CastleShrineInfoManager::canPickupCastleSymbol( Race_t race, CastleSymbol* pCastleSymbol ) const
	
{
	__BEGIN_TRY

	// 일단 이 성의 상징 조각이 어느 전쟁에 소속되어 있는지 알아온다.
	CastleShrineSet* pShrineSet = getShrineSet( pCastleSymbol->getItemType() );

	if ( pShrineSet == NULL )
	{
		return false;
	}

	ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

	War* pWar = g_pWarSystem->getActiveWar( castleZoneID );

	if ( pWar == NULL )
	{
		// 아싸 삑사리다~
		filelog( "WarError.log", "전쟁도 안하는데 성의 상징조각을 주울려고 한다. ItemType: %u", (int)pCastleSymbol->getItemType() );
		return false;
	}

	/*
	if ( pWar->getWarType() == WAR_RACE )
	{
		// 종족 전쟁이면 지나개나 다 줏는다.
		return true;
	}
	else 
	*/
	if ( pWar->getWarType() == WAR_GUILD )
	{
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );

		if ( pCastleInfo == NULL )
		{
			// 아싸 삑사리다~
			filelog( "WarError.log", "성이 아니다. ItemType: %u, ZoneID : %u", (int)pCastleSymbol->getItemType(), (int)castleZoneID );
			return false;
		}

		return ( race == pCastleInfo->getRace() );
	}

	// 아싸 삑사리다~
	filelog( "WarError.log", "이상한 전쟁이다. WarType : %u", (int)pWar->getWarType() );

	return false;
	__END_CATCH
}

bool CastleShrineInfoManager::getMatchGuardShrinePosition( Item* pItem, ZoneItemPosition& zip ) const
	
{
	__BEGIN_TRY

	if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL )
		return false;
	
	ItemType_t itemType = pItem->getItemType();
	ShrineID_t shrineID = itemType;					// ShrineID = ItemType(of CastleSymbol)

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );

	if ( pShrineSet == NULL )
	{
		// 이 성의 상징에 해당하는 Shrine Set이 없다.
		return false;
	}

	zip.setZoneID( pShrineSet->m_GuardShrine.getZoneID() );
	zip.setZoneX( pShrineSet->m_GuardShrine.getX() );
	zip.setZoneY( pShrineSet->m_GuardShrine.getY() );

	return true;

	__END_CATCH
}

// putCastleSymbol ( 누군가 성지성단에 성의 상징을 놓았을때 ) 이 불려지면 bLock = false
// returnAllCastleSymbol ( 시간이 다 되었을 때 ) 이 불려지면 bLock = true
// true일 경우 다른 스레드 (WarSystem이 돌아가는 스레드)에서 불려지므로 내부에서 락을 걸어줘야 하고
// false일 경우 성지성단이 있는 존과 같은 존그룹스레드에서 돌아가므로 내부에서 락을 걸어주지 않아야 한다.
// 2003. 2. 5. by Sequoia
bool CastleShrineInfoManager::returnCastleSymbol( ShrineID_t shrineID, bool bLock ) const
	
{
	__BEGIN_TRY

	// shrineID와 관련된 CastleSymbol을 DB정보를 이용해서 찾는다.
	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	
	if (pShrineSet==NULL) return false;

	Item::ItemClass ItemClass 	= Item::ITEM_CLASS_CASTLE_SYMBOL;
	ItemID_t 		ItemID 		= pShrineSet->getCastleSymbolItemID();

	if (ItemID==0) return false;

	GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( ItemClass, ItemID );

	if (pItemPosition==NULL) return false;

	Item* pItem = pItemPosition->popItem( bLock );

	if (pItem!=NULL && pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		Zone* pZone = pItemPosition->getZone();
		Assert(pZone!=NULL);

		CastleSymbol* pCastleSymbol = dynamic_cast<CastleSymbol*>(pItem);
		Assert(pCastleSymbol!=NULL);

		return returnCastleSymbol(pZone, pCastleSymbol);
	}

	return false;

	__END_CATCH
}

// WarSystem에서만 부른다.
bool CastleShrineInfoManager::returnAllCastleSymbol( ZoneID_t castleZoneID ) const 
	
{
	__BEGIN_TRY

	bool bReturned = false;

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	// castleZoneID의 shrineID를 검색할수가 없어서 하나하나 비교한다. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
		ZoneID_t guardCastleZoneID;

		if (g_pCastleInfoManager->getCastleZoneID(guardZoneID, guardCastleZoneID))
		{
			if (castleZoneID==guardCastleZoneID)
			{
				bReturned = returnCastleSymbol( pShrineSet->m_ShrineID ) || bReturned;
			}
		}
	}
	
	return bReturned;

	__END_CATCH
}


bool CastleShrineInfoManager::returnCastleSymbol(Zone* pZone, CastleSymbol* pCastleSymbol) const
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);
	Assert(pCastleSymbol!=NULL);

	// TargetZone, Shrine을 찾는다.
	ShrineID_t shrineID = pCastleSymbol->getItemType();
	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	
	if (pShrineSet==NULL) return false;

	ShrineInfo& GuardShrine = pShrineSet->m_GuardShrine;

	Zone* pTargetZone = getZoneByZoneID( GuardShrine.getZoneID() );
	Assert( pTargetZone!=NULL );

	ObjectID_t CorpseObjectID = GuardShrine.getObjectID();

	pZone->transportItemToCorpse( pCastleSymbol, pTargetZone, CorpseObjectID );

//	StringStream msg;
//	msg << "성의 상징 조각(" << GuardShrine.getName() << ")이 수호성단(" << GuardShrine.getName() << ")으로 돌아갔습니다.";

	char msg[200];
	sprintf( msg, g_pStringPool->c_str( STRID_RETURN_TO_GUARD_SHRINE_CASTLE_SYMBOL ),
					GuardShrine.getName().c_str(), GuardShrine.getName().c_str() );

	GCSystemMessage msgPkt;
	msgPkt.setMessage( msg );

	g_pCastleInfoManager->broadcastShrinePacket( shrineID, &msgPkt );

	return true;
		
	__END_CATCH
}

bool CastleShrineInfoManager::putCastleSymbol(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) const
	
{
	__BEGIN_TRY

	Assert(pPC!=NULL);
	Assert(pItem!=NULL);
	Assert(pCorpse!=NULL);

	ShrineID_t shrineID = pItem->getItemType();

	filelog( "WarLog.txt", "%s가 성의 상징[%u]을 성지 성단[%s]에 넣었습니다.",
			pPC->getName().c_str(), (uint)shrineID, pCorpse->getName().c_str() );

	// 성의 상징이 들어간 성단으로부터 성의 상징이 날아서 돌아감을 나타내는 이펙트를 붙여준다.
//	sendCastleSymbolEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_HOLY_WARP );

	// PC에게서 성의 상징을 빼앗아 성단 안에 넣는다.
	Assert( pItem->getObjectID() == pPC->getExtraInventorySlotItem()->getObjectID() );
	pPC->deleteItemFromExtraInventorySlot();

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	deleteRelicEffect( pPC, pItem );

	pCorpse->addTreasure( pItem );

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	if (pShrineSet==NULL) return false;

	ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

    // 알맞은 성단에 넣으면 전쟁이 끝나고 수호성단으로 돌아가고
    if (isMatchHolyShrine( pItem, pCorpse ) && g_pWarSystem->isModifyCastleOwner( castleZoneID, pPC ))
    {
        g_pWarSystem->endWar(pPC, castleZoneID);

		// 전쟁 끝나는 War::executeEnd에서 알아서 되돌려준다.
//        returnCastleSymbol( shrineID, false );

		return true;
    }

    // 다른 성단에 넣거나 전쟁이 끝날 상황이 아니면 수호성단으로 그냥 돌아간다
   	returnCastleSymbol( shrineID, false );

	return false;

	__END_CATCH
}

// pZone은 guardZone이다.
bool CastleShrineInfoManager::removeShrineShield( Zone *pZone )
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	ZoneID_t guardZoneID = pZone->getZoneID();

	// castleZoneID의 shrineID를 검색할수가 없어서 하나하나 비교한다. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t currentGuardZoneID = pShrineSet->m_GuardShrine.getZoneID();

		if (guardZoneID==currentGuardZoneID)
		{
			Item* pItem = pZone->getItem( pShrineSet->m_GuardShrine.getObjectID() );

			if (pItem != NULL 
				&& pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
				&& pItem->isFlag(Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL)
				&& pItem->isFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD) ) 
			{
				pItem->removeFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);

				EffectManager& EM = pItem->getEffectManager();
				EM.deleteEffect(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pItem->getObjectID());
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SHRINE_SHIELD);
				pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcRemoveEffect);

			}
		}
	}

	return true;
	
	__END_CATCH
}

// pZone은 guardZone이다.
bool CastleShrineInfoManager::addShrineShield(Zone *pZone)
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	bool bAdded = false;

    __ENTER_CRITICAL_SECTION( (*pZone) )

	bAdded = addShrineShield_LOCKED( pZone );

    __LEAVE_CRITICAL_SECTION( (*pZone) )

	return bAdded;

	__END_CATCH
}

// pZone은 guardZone이다.
bool CastleShrineInfoManager::addShrineShield_LOCKED( Zone *pZone )
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	ZoneID_t guardZoneID = pZone->getZoneID();

	// castleZoneID의 shrineID를 검색할수가 없어서 하나하나 비교한다. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t currentGuardZoneID = pShrineSet->m_GuardShrine.getZoneID();

		if (guardZoneID==currentGuardZoneID)
		{
			Item* pItem = pZone->getItem( pShrineSet->m_GuardShrine.getObjectID() );

			if (pItem != NULL 
				&& pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
				&& !pItem->isFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD) ) 
			{
				pItem->setFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
				Assert(pCorpse!=NULL);

				EffectManager& EM = pItem->getEffectManager();
				EffectShrineShield* pEffect = new EffectShrineShield(pCorpse);
				pEffect->setShrineID( pCorpse->getItemType() );
				pEffect->setTick( 60 * 10 );
				EM.addEffect(pEffect);

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pItem->getObjectID() );
				gcAddEffect.setEffectID( Effect::EFFECT_CLASS_SHRINE_SHIELD );
				gcAddEffect.setDuration( 65000 );

				pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);
			}
		}
	}

	return true;

	__END_CATCH
}

string CastleShrineInfoManager::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ShrineInfoManager("
		<< "Size:" << size()
		<< ",(\n";

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	for( ; itr != m_ShrineSets.end() ; itr++ )
	{
		msg << "\t" << itr->second->toString() << "\n";
	}

	msg << "))";

	return msg.toString();

	__END_CATCH
}

CastleShrineInfoManager* g_pCastleShrineInfoManager = NULL;
