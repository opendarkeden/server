#include "RegenZoneManager.h"
#include "DB.h"

#include "MonsterCorpse.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Tile.h"

#include "PlayerCreature.h"

#include "EffectRegenZone.h"
#include "EffectTryingPosition.h"

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"

#include "HolyLandManager.h"
#include "CastleInfoManager.h"
#include "StringPool.h"

#include "MonsterManager.h"
#include "SiegeManager.h"

#include "war/WarSystem.h"

#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRegenZoneStatus.h"

void RegenZoneInfo::putTryingPosition() throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = m_pRegenZoneTower->getZone();
	ZoneCoord_t X = m_pRegenZoneTower->getX() - 2;
	ZoneCoord_t Y = m_pRegenZoneTower->getY() + 2;

	__ENTER_CRITICAL_SECTION( (*pZone) );

	EffectTryingPosition* pEffect = new EffectTryingPosition( pZone, X, Y, m_pRegenZoneTower );
	pZone->registerObject( pEffect );
	pZone->addEffect( pEffect );
	pZone->getTile( X, Y ).addEffect( pEffect );

	GCAddEffectToTile gcAddEffectToTile;
	gcAddEffectToTile.setXY( X, Y );
	gcAddEffectToTile.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffectToTile.setObjectID( pEffect->getObjectID() );
	gcAddEffectToTile.setDuration( pEffect->getRemainDuration() );

	pZone->broadcastPacket( X, Y, &gcAddEffectToTile );

	__LEAVE_CRITICAL_SECTION( (*pZone) );

	__END_CATCH
}

void RegenZoneInfo::deleteTryingPosition() throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = m_pRegenZoneTower->getZone();
	ZoneCoord_t X = m_pRegenZoneTower->getX() - 2;
	ZoneCoord_t Y = m_pRegenZoneTower->getY() + 2;

	__ENTER_CRITICAL_SECTION( (*pZone) );
	
	EffectTryingPosition* pEffect = dynamic_cast<EffectTryingPosition*>(pZone->getTile(X, Y).getEffect( Effect::EFFECT_CLASS_TRYING_POSITION ) );
	if ( pEffect != NULL ) pEffect->setDeadline(0);

	__LEAVE_CRITICAL_SECTION( (*pZone) );

	__END_CATCH
}

RegenZoneManager::RegenZoneManager() { }
RegenZoneManager::~RegenZoneManager()
{
	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.begin();
	map<uint, RegenZoneInfo*>::iterator endItr = m_RegenZoneInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( itr->second );
	}
}

void RegenZoneManager::reload() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT ID, ZoneID, ZoneX, ZoneY, Owner FROM RegenZonePosition" );

		m_pStatusPacket = new GCRegenZoneStatus();
		
		while ( pResult->next() )
		{
			uint ID = pResult->getInt(1);
			ZoneID_t ZoneID = pResult->getInt(2);
			ZoneCoord_t ZoneX = pResult->getInt(3);
			ZoneCoord_t ZoneY = pResult->getInt(4);
			uint Owner = pResult->getInt(5);

			Assert( Owner < 4 );

			Zone* pZone = getZoneByZoneID( ZoneID );
			Assert( pZone != NULL );

			__ENTER_CRITICAL_SECTION( (*pZone) )

			Item* pTowerItem = pZone->getTile( ZoneX, ZoneY ).getItem();
			if ( pTowerItem == NULL || pTowerItem->getItemClass() != Item::ITEM_CLASS_CORPSE || pTowerItem->getItemType() != MONSTER_CORPSE )
			{
				filelog("RaceWar.log", "리젠존 타워를 못 찾았습니다. [%d:(%d,%d)]", ZoneID, ZoneX, ZoneY);
				pZone->unlock();
				continue;
			}

			MonsterCorpse* pTower = dynamic_cast<MonsterCorpse*>(pTowerItem);
			Assert( pTower != NULL );

			RegenZoneInfo* pInfo = m_RegenZoneInfos[ID];
			if ( pInfo == NULL )
			{
				filelog("RaceWar.log", "Reload : 해당되는 리젠존이 없습니다. [%d]", ID);
				m_RegenZoneInfos.erase(ID);
				pZone->unlock();
				continue;
			}

			pInfo->setOwner( (RegenZoneInfo::RegenZoneIndex)Owner );

			EffectRegenZone* pEffect = dynamic_cast<EffectRegenZone*>(pTower->getEffectManager().findEffect( Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE ));
			if ( pEffect == NULL )
			{
				filelog("RaceWar.log", "Reload : 리젠존 이펙트가 날라갔습니다. [%d]", ID);
				pZone->unlock();
				continue;
			}

			pEffect->setOwner( m_RegenZoneInfos[ID]->getOwner() );
			m_pStatusPacket->setStatus( ID, Owner );

			__LEAVE_CRITICAL_SECTION( (*pZone) )
		}
	}
	END_DB( pStmt );

	broadcastStatus();

	__END_CATCH
}

void RegenZoneManager::load() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT ID, ZoneID, ZoneX, ZoneY, Owner FROM RegenZonePosition" );

		m_pStatusPacket = new GCRegenZoneStatus();
		
		while ( pResult->next() )
		{
			uint ID = pResult->getInt(1);
			ZoneID_t ZoneID = pResult->getInt(2);
			ZoneCoord_t ZoneX = pResult->getInt(3);
			ZoneCoord_t ZoneY = pResult->getInt(4);
			uint Owner = pResult->getInt(5);

			Assert( Owner < 4 );

			Zone* pZone = getZoneByZoneID( ZoneID );
			Assert( pZone != NULL );

			MonsterCorpse* pTower = new MonsterCorpse( 673, g_pStringPool->getString( STRID_REGENZONE_TOWER ), 2 );
			Assert( pTower != NULL );

			pTower->setShrine(true);

			pZone->registerObject( pTower );
			pZone->addItem( pTower, ZoneX, ZoneY );

			m_RegenZoneInfos[ID] = new RegenZoneInfo( ID, pTower, Owner );
			m_RegenZoneInfos[ID]->setOriginalOwner( (RegenZoneInfo::RegenZoneIndex)Owner );

			EffectRegenZone* pEffect = new EffectRegenZone( pTower );
			pEffect->setOwner( m_RegenZoneInfos[ID]->getOwner() );
			pTower->setFlag( pEffect->getEffectClass() );

			pTower->getEffectManager().addEffect( pEffect );
			
			m_pStatusPacket->setStatus( ID, Owner );
		}
	}
	END_DB( pStmt );

	__END_CATCH
}

void RegenZoneManager::putTryingPosition() throw(Error)
{
	__BEGIN_TRY

	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.begin();
	map<uint, RegenZoneInfo*>::iterator endItr = m_RegenZoneInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		itr->second->putTryingPosition();
	}

	__END_CATCH
}

void RegenZoneManager::deleteTryingPosition() throw(Error)
{
	__BEGIN_TRY

	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.begin();
	map<uint, RegenZoneInfo*>::iterator endItr = m_RegenZoneInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		itr->second->deleteTryingPosition();
	}

	__END_CATCH
}

void RegenZoneManager::changeRegenZoneOwner( MonsterCorpse* pTower, Race_t race )
{
	Assert( race < 4 );
	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.begin();
	map<uint, RegenZoneInfo*>::iterator endItr = m_RegenZoneInfos.end();

	if ( !g_pWarSystem->hasActiveRaceWar() ) return;

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second->getTower() == pTower )
		{
			if ( itr->second->getOriginalOwner() != RegenZoneInfo::REGEN_ZONE_DEFAULT )
			{
				if ( race != (Race_t)itr->second->getOriginalOwner() ) race = (Race_t)RegenZoneInfo::REGEN_ZONE_DEFAULT;
			}

			itr->second->setOwner( (RegenZoneInfo::RegenZoneIndex)race );
			EffectRegenZone* pEffect = dynamic_cast<EffectRegenZone*>(pTower->getEffectManager().findEffect( Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE ));
			if ( pEffect != NULL )
			{
				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.addEffectList( pEffect->getSendEffectClass() );
				gcRemoveEffect.setObjectID( pTower->getObjectID() );

				pEffect->setOwner( (RegenZoneInfo::RegenZoneIndex)race );

				m_pStatusPacket->setStatus( itr->second->getID(), race );
				broadcastStatus();

				GCAddEffect gcAddEffect;
				gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
				gcAddEffect.setObjectID( pTower->getObjectID() );
				gcAddEffect.setDuration( pEffect->getRemainDuration() );

				pTower->getZone()->broadcastPacket( pTower->getX(), pTower->getY(), &gcRemoveEffect );
				pTower->getZone()->broadcastPacket( pTower->getX(), pTower->getY(), &gcAddEffect );

				gcAddEffect.setEffectID( Effect::EFFECT_CLASS_CAPTURE_REGEN_ZONE );
				gcAddEffect.setObjectID( pTower->getObjectID() );
				gcAddEffect.setDuration( 1 );

				pTower->getZone()->broadcastPacket( pTower->getX(), pTower->getY(), &gcAddEffect );
			}

			return;
		}
	}
}

bool RegenZoneManager::canTryRegenZone( PlayerCreature* pPC, MonsterCorpse* pTower )
{
	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.begin();
	map<uint, RegenZoneInfo*>::iterator endItr = m_RegenZoneInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second->getTower() == pTower )
		{
			return pPC->getRace() != (Race_t)itr->second->getOwner();
		}
	}

	return false;
}

bool RegenZoneManager::canRegen( PlayerCreature* pPC, uint ID )
{
	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.find(ID);
	RegenZoneInfo* pInfo;

	if ( itr == m_RegenZoneInfos.end() )
	{
		switch ( ID )
		{
			case 8:				// 옥타부스
			case 10:			// 셉티무스
				return pPC->isSlayer();
			case 9:			// 테르티우스
			case 11:			// 쿠아르투스
				return pPC->isVampire();
			case 12:
			case 13:
				return pPC->isOusters();

			case 14:
				{
					if ( !SiegeManager::Instance().isSiegeZone( pPC->getZoneID() ) ) return false;
					Zone* pZone = pPC->getZone();
					MonsterManager* pMM = pZone->getMonsterManager();
					hash_map< ObjectID_t, Creature* >& cmap = pMM->getCreatures();
					hash_map< ObjectID_t, Creature* >::iterator itr = cmap.begin();

					// 성문이 있으면 안된다.
					for ( ; itr != cmap.end(); ++itr )
					{
						Monster* pMonster = dynamic_cast<Monster*>((itr->second));
						if ( pMonster != NULL && pMonster->getMonsterType() == 726 ) return false;
					}
				}
				return (
						pPC->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_1) ||
						pPC->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_2) ||
						pPC->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_3) ||
						pPC->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_4) ||
						pPC->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_5) );
			default:
				return false;
				break;
		};
		return false;
	}
	else pInfo = itr->second;

	return pPC->getRace() == (Race_t)pInfo->getOwner();
}

void RegenZoneManager::regeneratePC( PlayerCreature* pPC, uint ID )
{
	map<uint, RegenZoneInfo*>::iterator itr = m_RegenZoneInfos.find(ID);
	ZONE_COORD targetPos;
	RegenZoneInfo* pInfo;

	if ( itr == m_RegenZoneInfos.end() )
	{
		switch ( ID )
		{
			case 8:				// 옥타부스
				{
					targetPos.id = 1201;
					targetPos.x = 120;
					targetPos.y = 120;
					break;
				}
			case 9:			// 테르티우스
				{
					targetPos.id = 1202;
					targetPos.x = 30;
					targetPos.y = 120;
					break;
				}
			case 10:			// 셉티무스
				{
					targetPos.id = 1203;
					targetPos.x = 120;
					targetPos.y = 30;
					break;
				}
			case 11:			// 쿠아르투스
				{
					targetPos.id = 1204;
					targetPos.x = 30;
					targetPos.y = 30;
					break;
				}
			case 12:
				{
					targetPos.id = 1205;
					targetPos.x = 30;
					targetPos.y = 30;
					break;
				}
			case 13:
				{
					targetPos.id = 1206;
					targetPos.x = 30;
					targetPos.y = 120;
					break;
				}
			case 14:
				{
					targetPos.id = pPC->getZoneID();
					targetPos.x = 156;
					targetPos.y = 108;
					break;
				}
			default:
				return;
				break;
		};
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( targetPos.id );
		if ( pCastleInfo != NULL )
		{
			pCastleInfo->getResurrectPosition( CastleInfo::CASTLE_RESURRECT_PRIORITY_FIRST, targetPos );
		}
	}
	else
	{
		pInfo = itr->second;
		MonsterCorpse* pTower = pInfo->getTower();
		targetPos.id = pTower->getZone()->getZoneID();
		targetPos.x = pTower->getX();
		targetPos.y = pTower->getY();
	}

	pPC->deleteEffect( Effect::EFFECT_CLASS_COMA );

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		pSlayer->setHP( pSlayer->getHP( ATTR_MAX ) );
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		pVampire->setHP( pVampire->getHP( ATTR_MAX ) - pVampire->getSilverDamage() );
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		pOusters->setHP( pOusters->getHP( ATTR_MAX ) - pOusters->getSilverDamage() );
	}

	transportCreature( pPC, targetPos.id, targetPos.x, targetPos.y, false );
}

void RegenZoneManager::broadcastStatus()
{
	g_pHolyLandManager->broadcast( m_pStatusPacket );
}
