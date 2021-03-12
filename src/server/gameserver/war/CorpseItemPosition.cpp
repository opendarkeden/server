///////////////////////////////////////////////////////////////////
// CorpseItemPosition 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Assert.h"

#include "Zone.h"
#include "ZoneGroup.h"
#include "Tile.h"
#include "Item.h"
#include "Corpse.h"
#include "MonsterCorpse.h"

#include "ZoneUtil.h"
#include "ItemUtil.h"
#include "RelicUtil.h"
#include "Utility.h"
#include "ItemFactoryManager.h"

#include "CorpseItemPosition.h"
#include "RelicUtil.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "ctf/FlagManager.h"
#include <list>

Item* CorpseItemPosition::popItem( bool bLock )
	
{
	__BEGIN_TRY

	m_pZone = NULL;

	if ( bLock ) return getItem_UNLOCKED(true);
	return getItem_LOCKED(true);

	__END_CATCH
}

Item* CorpseItemPosition::getItem_LOCKED( bool isDel )
	
{
	__BEGIN_TRY

	Zone* pZone = getZoneByZoneID( m_ZoneID );
	m_pZone = pZone;

	if( pZone == NULL )
	{
		filelog( "ItemError.log", "CorpseItemPosition:getItem() : ZoneID가 잘못되었습니다.");
		return NULL;
	}

	return getItem_CORE( pZone, isDel );

	__END_CATCH
}

Item* CorpseItemPosition::getItem_UNLOCKED( bool isDel )
	
{
	__BEGIN_TRY

	Zone* pZone = getZoneByZoneID( m_ZoneID );
	m_pZone = pZone;

	if( pZone == NULL )
	{
		filelog( "ItemError.log", "CorpseItemPosition:getItem() : ZoneID가 잘못되었습니다.");
		return NULL;
	}

	Item* pItem;

	__ENTER_CRITICAL_SECTION( (*pZone) )

	pItem = getItem_CORE( pZone, isDel );

	__LEAVE_CRITICAL_SECTION( (*pZone) )

	return pItem;

	__END_CATCH
}

Item* CorpseItemPosition::getItem_CORE(Zone* pZone, bool isDel) 
	
{
	__BEGIN_TRY

	Corpse* pCorpse = dynamic_cast<Corpse*>(pZone->getItem( m_CorpseObjectID ));
	Item* pRet = NULL;

	if( pCorpse == NULL || pCorpse->getItemClass() != Item::ITEM_CLASS_CORPSE ) 
	{
		filelog( "ItemError.log", "CorpseItemPosition::getItem() : 해당하는 시체가 없습니다.");
		
		return NULL;
	}

	if ( isDel )
	{
		pRet = pCorpse->popTreasure( m_ObjectID );

		if( pRet == NULL )
		{
			filelog( "ItemError.log", "CorpseItemPosition::getItem() : 해당 아이템이 시체 안에 없습니다.");

			return NULL;
		}

		deleteFlagEffect( pCorpse, pRet );
		deleteRelicEffect( pCorpse, pRet );
		sendRelicWarpEffect( pCorpse );

		if ( pCorpse->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pCorpse);
			if ( pMonsterCorpse != NULL )
			{
				if ( g_pFlagManager->isFlagPole( pMonsterCorpse ) 
				&& g_pFlagManager->getFlagPoleRace( pMonsterCorpse ) == g_pFlagManager->getWinnerRace() )
				{
					Item* pGemStone = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_QUEST_ITEM, 4, list<OptionType_t>() );
					pZone->registerObject( pGemStone );
					TPOINT tp = pZone->addItem( pGemStone, pMonsterCorpse->getX(), pMonsterCorpse->getY() );

					pGemStone->create( "", STORAGE_ZONE, pZone->getZoneID(), tp.x, tp.y );
//					pGemStone->setFlag( Effect::EFFECT_CLASS_DROP_FORCE );
					pGemStone->setFlag( (Effect::EffectClass)(Effect::EFFECT_CLASS_SLAYER_ONLY + (int)g_pFlagManager->getWinnerRace()) );

					EffectID_t effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_1 + (rand()&0x3);

					GCAddEffectToTile gcAddEffectToTile;
					gcAddEffectToTile.setObjectID( pMonsterCorpse->getObjectID() );
					gcAddEffectToTile.setEffectID( effectClass );
					gcAddEffectToTile.setXY( pMonsterCorpse->getX(), pMonsterCorpse->getY() );
					gcAddEffectToTile.setDuration( 10 );  // 별 의미 없다 그냥 1초

					pZone->broadcastPacket( pMonsterCorpse->getX(), pMonsterCorpse->getY(), &gcAddEffectToTile );
				}
			}
		}
	}
	else
		pRet = pCorpse->getTreasure( m_ObjectID );

	if( pRet == NULL )
	{
		filelog( "ItemError.log", "CorpseItemPosition::getItem() : 해당 아이템이 시체 안에 없습니다.");

		return NULL;
	}

	return pRet;

	__END_CATCH
}

string  
CorpseItemPosition::toString() const 
	
{
	return "CorpseItemPosition";
}

