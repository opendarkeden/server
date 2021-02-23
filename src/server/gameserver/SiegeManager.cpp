#include "SiegeManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "EffectShareHP.h"
#include "PlayerCreature.h"
#include "Item.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCCannotAdd.h"
#include "RelicUtil.h"
#include "Player.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "CreatureUtil.h"
#include "CastleInfoManager.h"
#include "WarSystem.h"
#include "EventTransport.h"
#include <cstdio>

void SiegeManager::init()
{
	init(1500);
	init(1501);
	init(1502);
	init(1503);
	init(1504);
	init(1505);
	init(1506);
}

void SiegeManager::init(ZoneID_t zoneID)
{
	Zone* pSiegeZone = getZoneByZoneID( zoneID );
	if ( pSiegeZone == NULL ) return;

	MonsterCorpse* pShrine = new MonsterCorpse( 560, "圣物保管台", 2 );
	Assert( pShrine != NULL );

	pShrine->setShrine(true);
	pShrine->setZone( pSiegeZone );
	pSiegeZone->registerObject( pShrine );

	TPOINT tp = pSiegeZone->addItem( pShrine, 191, 64, true );
	Assert( tp.x != -1 );
	pShrine->setFlag( Effect::EFFECT_CLASS_CASTLE_SHRINE_HOLY );
}

void SiegeManager::start(ZoneID_t zoneID)
{
	Zone* pSiegeZone = getZoneByZoneID( zoneID );
	if ( pSiegeZone == NULL ) return;

	Monster* pGate[4];

	pGate[0] = new Monster( 726 );
	pGate[1] = new Monster( 727 );
	pGate[2] = new Monster( 728 );
	pGate[3] = new Monster( 729 );

	for ( int i=0; i<4; ++i )
	{
		pGate[i]->setBrain(NULL);
		pSiegeZone->addCreature( pGate[i], 57+i, 204+i, 1 );
	}

	for ( int i=0; i<4; ++i )
	{
		EffectShareHP* pEffect = new EffectShareHP(pGate[i]);
		for ( int j=0; j<4; ++j )
		{
			if ( j != i ) pEffect->getSharingCreatures().push_back(pGate[j]->getObjectID());
		}
		pGate[i]->addEffect(pEffect);
		pGate[i]->setFlag(pEffect->getEffectClass());
	}

	pGate[0] = new Monster( 726 );
	pGate[1] = new Monster( 727 );
	pGate[2] = new Monster( 728 );
	pGate[3] = new Monster( 729 );

	for ( int i=0; i<4; ++i )
	{
		pGate[i]->setBrain(NULL);
		pSiegeZone->addCreature( pGate[i], 159+i, 101+i, 1 );
	}

	for ( int i=0; i<4; ++i )
	{
		EffectShareHP* pEffect = new EffectShareHP(pGate[i]);
		for ( int j=0; j<4; ++j )
		{
			if ( j != i ) pEffect->getSharingCreatures().push_back(pGate[j]->getObjectID());
		}
		pGate[i]->addEffect(pEffect);
		pGate[i]->setFlag(pEffect->getEffectClass());
	}

	Monster* pTower = new Monster( 734 );
	pTower->setBrain(NULL);
	pSiegeZone->addCreature( pTower, 143, 30, 1 );

	static TPOINT guardPosition[] = 
	{
		{47,193},
		{48,195},
		{48,192},
		{49,194},
		{63,208},
		{64,207},
		{64,210},
		{65,209},
		{150,89},
		{151,88},
		{151,91},
		{152,90},
		{165,106},
		{166,105},
		{166,108},
		{167,107},
		{-1,-1}
	};

	ZoneID_t castleZoneID = 0;
	g_pCastleInfoManager->getCastleZoneID( zoneID, castleZoneID );
	MonsterType_t mType = 736;
	CastleInfo* pInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
	if ( pInfo != NULL )
	{
		switch ( pInfo->getRace() )
		{
			case RACE_VAMPIRE:
				mType = 736;
				break;
			case RACE_SLAYER:
				mType = 735;
				break;
			case RACE_OUSTERS:
				mType = 737;
				break;
			default:
				break;
		}
	}

	for ( int i=0; guardPosition[i].x != -1; ++i )
	{
		Monster* pMonster = new Monster( mType );
		pMonster->setTreasure(false);
		pMonster->setScanEnemy(true);
		pMonster->setName("卫兵");

		try
		{
			pSiegeZone->addCreature( pMonster, guardPosition[i].x, guardPosition[i].y, 0 );
			pSiegeZone->monsterScan( pMonster, guardPosition[i].x, guardPosition[i].y, 0 );
		}
		catch( Exception& e )
		{
			filelog("SummonSiegeGuard.log", "%s", e.toString().c_str());
		}
	}
}

void SiegeManager::reset(ZoneID_t zoneID)
{
	Zone* pSiegeZone = getZoneByZoneID( zoneID );
	if ( pSiegeZone == NULL ) return;

	pSiegeZone->killAllMonsters_UNLOCK();
	pSiegeZone->getPCManager()->transportAllCreatures(0xffff);
}

ZoneID_t SiegeManager::getSiegeZoneID(ZoneID_t castleZoneID)
{
	ZoneID_t ret = castleZoneID - 1200;

	if ( ret > 6 || ret < 1 ) return 0;
	return ret + 1500;
}

void SiegeManager::putItem( PlayerCreature* pPC, MonsterCorpse* pCorpse, Item* pItem )
{
	ZoneID_t zoneID = pPC->getZoneID();
	ZoneID_t castleZoneID = 0;
	if ( !g_pCastleInfoManager->getCastleZoneID( zoneID, castleZoneID) )
	{
		GCCannotAdd gcCA;
		gcCA.setObjectID( pItem->getObjectID() );
		pPC->getPlayer()->sendPacket( &gcCA );
		return;
	}

	int side = 0;
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 ) )
	{
		side = 1;
	}
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 ) )
	{
		side = 2;
	}
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 ) )
	{
		side = 3;
	}
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 ) )
	{
		side = 4;
	}
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 ) )
	{
		side = 5;
	}

	if ( side == 0 )
	{
		GCCannotAdd gcCA;
		gcCA.setObjectID( pItem->getObjectID() );
		pPC->getPlayer()->sendPacket( &gcCA );
		return;
	}

/*	if ( !g_pCastleInfoManager->modifyCastleOwner( castleZoneID, pPC ) )
	{
		GCCannotAdd gcCA;
		gcCA.setObjectID( pItem->getObjectID() );
		pPC->getPlayer()->sendPacket( &gcCA );
		return;
	}*/

	if ( !g_pWarSystem->isModifyCastleOwner( castleZoneID, pPC ) )
	{
		GCCannotAdd gcCA;
		gcCA.setObjectID( pItem->getObjectID() );
		pPC->getPlayer()->sendPacket( &gcCA );
		return;
	}

	g_pWarSystem->endWar( pPC, castleZoneID );

	Assert( pItem->getObjectID() == pPC->getExtraInventorySlotItem()->getObjectID() );
	pPC->deleteItemFromExtraInventorySlot();

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	deleteRelicEffect( pPC, pItem );

	pItem->destroy();
	SAFE_DELETE( pItem );

	GCSystemMessage gcSM;
	char buffer[256];
	sprintf( buffer, "%d号攻击方获得胜利.10秒后移动到复活地点.", side );
	gcSM.setMessage( buffer );
	pPC->getZone()->broadcastPacket( &gcSM );

	pPC->getZone()->killAllMonsters_UNLOCK();
	pPC->getZone()->getPCManager()->transportAllCreatures(0xffff);
}

void SiegeManager::recallGuild( ZoneID_t currentZoneID, ZoneID_t siegeZoneID, GuildID_t guildID, int side, int num )
{
	if ( side < 1 || side > 7 ) return;

	static TPOINT targetPos[7] =
	{
		{172, 38},
		{172, 38},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232},
		{20, 232}
	};

	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	list<Creature*> clist = g_pPCFinder->getGuildCreatures(guildID, num);

	for ( list<Creature*>::iterator itr = clist.begin(); itr != clist.end(); ++itr )
	{
		Creature* pTargetCreature = *itr;
		if ( pTargetCreature == NULL ) continue;

		// 家券磊狼 粮苞 谅钎.
		ZoneID_t ZoneNum = siegeZoneID;
		Coord_t ZoneX = targetPos[side-1].x;
		Coord_t ZoneY = targetPos[side-1].y;

		if ( pTargetCreature->getZone() == NULL ) continue;

		if ( currentZoneID != pTargetCreature->getZoneID() )
		{
			pTargetCreature->getZone()->lock();
		}

		for ( int i=0; i<7; ++i )
		{
			deleteCreatureEffect( pTargetCreature, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + i) );
		}

		if ( side < 8 && side > 0 )
		{
			cout << "side : " << side << endl;
			addSimpleCreatureEffect( pTargetCreature, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + side - 1) );
		}

		if ( currentZoneID != pTargetCreature->getZoneID() )
		{
			pTargetCreature->getZone()->unlock();
		}

//		transportCreature(pTargetCreature, ZoneNum, ZoneX, ZoneY, false);
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pTargetCreature->getPlayer());
		if ( pGamePlayer == NULL ) continue;

		EventTransport* pEvent = dynamic_cast<EventTransport*>(pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT));
		bool newEvent = false;
		if (pEvent==NULL)
		{
			pEvent = new EventTransport(pGamePlayer);
			newEvent = true;
		}

//		pEvent = new EventTransport(pGamePlayer);
		pEvent->setTargetZone( ZoneNum, ZoneX, ZoneY );
		pEvent->setDeadline(10);

		if ( newEvent )
			pGamePlayer->addEvent( pEvent );
		num--;

		if ( num == 0 ) break;
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )
}

bool SiegeManager::isSiegeZone( ZoneID_t zID )
{
	switch ( zID )
	{
		case 1500:
		case 1501:
		case 1502:
		case 1503:
		case 1504:
		case 1505:
		case 1506:
			return true;
		default:
			break;
	}

	return false;
}
