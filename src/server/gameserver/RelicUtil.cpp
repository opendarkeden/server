#include "RelicUtil.h"
#include "Zone.h"
#include "Creature.h"
#include "Corpse.h"
#include "Effect.h"
#include "BloodBible.h"
#include "CastleSymbol.h"
#include "Inventory.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "CombatInfoManager.h"
#include "CastleInfoManager.h"
#include "HolyLandManager.h"
#include "war/DragonEyeManager.h"
#include "StringPool.h"

#include "EffectHasVampireRelic.h"
#include "EffectHasSlayerRelic.h"
#include "EffectHasBloodBible.h"
#include "EffectHasCastleSymbol.h"
#include "EffectRelicPosition.h"
#include "EffectRelicLock.h"
#include "EffectDragonEye.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteInventoryItem.h"

#include <stdio.h>

void
sendBloodBibleEffect( Object* pObject, Effect::EffectClass EClass )
	
{
	__BEGIN_TRY

	Assert(pObject!=NULL);

	switch (pObject->getObjectClass())
	{
		case Object::OBJECT_CLASS_CREATURE :
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature!=NULL);

			GCAddEffect gcAddEffect;
			gcAddEffect.setEffectID( EClass );
			gcAddEffect.setObjectID( pCreature->getObjectID() );

			pCreature->getZone()->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
		}
		break;

		case Object::OBJECT_CLASS_ITEM :
		{
			Item* pItem = dynamic_cast<Item*>(pObject);
			Assert(pItem!=NULL);

			if ( pItem->getItemClass() == Item::ITEM_CLASS_CORPSE )
			{
				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
				Assert(pCorpse!=NULL);

				GCAddEffect gcAddEffect;
				gcAddEffect.setEffectID( EClass );
				gcAddEffect.setObjectID( pCorpse->getObjectID() );

				pCorpse->getZone()->broadcastPacket( pCorpse->getX(), pCorpse->getY(), &gcAddEffect );
			}
		}
		break;

		default :
			return;
	}

	__END_CATCH
}


// 	티모르남동 
// 			슬레이어 ( 37, 163 ) 
//			뱀파이어 ( 193, 46 ) 
//
//	아담의 성지 동<뱀파이어> ( 239, 134) 
//	아담의 성지 서<슬레이어> ( 27, 133 ) 
void
sendHolyLandWarpEffect( Creature* pCreature ) 
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);

	bool bSend = false;
	Distance_t limitDist = 15;
	Effect::EffectClass EClass;

	ZoneID_t zoneID = pCreature->getZoneID();

	ZoneCoord_t x, y;

	if (pCreature->isSlayer()) 
	{
		const int maxHolyLandWarpSlayer = 1;
		static ZONE_COORD HolyLandWarpSlayer[ maxHolyLandWarpSlayer ] = 
		{
			ZONE_COORD( 53, 37, 163 ), 	// 티모르 남동
//			ZONE_COORD( 73, 27, 133 )	// 아담의 성지 서쪽
		};

		for (int i=0; i<maxHolyLandWarpSlayer; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpSlayer[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_SLAYER;
	} 
	else if (pCreature->isVampire())
	{
		const int maxHolyLandWarpVampire = 1;
		static ZONE_COORD HolyLandWarpVampire[ maxHolyLandWarpVampire ] = 
		{
			ZONE_COORD( 53, 193, 46 ),	// 티모르 남동
//			ZONE_COORD( 71, 239, 134 )	// 아담의 성지 동쪽
		};

		for (int i=0; i<maxHolyLandWarpVampire; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpVampire[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_VAMPIRE;
	}
	else if (pCreature->isOusters())
	{
		// 음냐 언젠가 해줘야 함 ~_~
		// 아우스터즈는 아담의 성지 어디에 떨구지 ㅡ.,ㅡ
		const int maxHolyLandWarpOusters = 1;
		static ZONE_COORD HolyLandWarpOusters[ maxHolyLandWarpOusters ] = 
		{
			ZONE_COORD( 53, 160, 170 ),	// 티모르 남동
//			ZONE_COORD( 72, 129, 112 )	// 아담의 성지 중앙
		};

		for (int i=0; i<maxHolyLandWarpOusters; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpOusters[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_OUSTERS;
	}

	if (bSend) 
	{
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setEffectID( EClass );
		gcAddEffectToTile.setObjectID( pCreature->getObjectID() );
		gcAddEffectToTile.setXY( x, y );
		gcAddEffectToTile.setDuration( 21 );

		pCreature->getZone()->broadcastPacket( x, y, &gcAddEffectToTile );
	}

	__END_CATCH
}

bool addEffectRelicPosition( Item* pItem, ZoneID_t zoneID, TPOINT pt )
	
{
	__BEGIN_TRY

	if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
	{
		EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
		//pPosition->setNextTime(10);     // 1초 후 메세지 뿌린다.
		pPosition->setTick( 1*60*10 );  // 1분마다 한번씩 알린다.
		pPosition->setZoneID( zoneID );
		pPosition->setX( pt.x );
		pPosition->setY( pt.y );
		pPosition->setPart( pItem->getItemType() );
		pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
		pItem->getEffectManager().addEffect( pPosition );
		pPosition->affect();

		return true;
	}

	return false;

	__END_CATCH
}

bool
deleteEffectRelicPosition( Item* pItem )
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);

	// EffectRelicPosition 제거한다.
	// 성물 보관대에 붙어있던 Effect를 제거한다.
	if (pItem->isFlag(Effect::EFFECT_CLASS_RELIC_POSITION))
	{
		Effect* pPositionEffect = pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_RELIC_POSITION);
		Assert(pPositionEffect != NULL);

		pPositionEffect->unaffect();
		pItem->removeFlag(Effect::EFFECT_CLASS_RELIC_POSITION);
		pItem->getEffectManager().deleteEffect(Effect::EFFECT_CLASS_RELIC_POSITION);

		return true;
	}

	return false;

	__END_CATCH
}

// Corpse붙은 pItem과 관련된 Effect를 없애준다.
bool
deleteRelicEffect(Corpse* pCorpse, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pCorpse!=NULL);
	Assert(pItem!=NULL);

	Effect::EffectClass EClass;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_RELIC :
		{
			const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );
			Assert( pRelicInfo != NULL );

			if ( pRelicInfo->relicType == RELIC_TYPE_SLAYER )
				EClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			else if ( pRelicInfo->relicType == RELIC_TYPE_VAMPIRE )
				EClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			else
				throw Error("잘못된 Relic Item Type 입니다.");
		}
		break;

		case Item::ITEM_CLASS_BLOOD_BIBLE :
			EClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
			break;

		case Item::ITEM_CLASS_CASTLE_SYMBOL :
			EClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
			break;

		case Item::ITEM_CLASS_WAR_ITEM :
			EClass = Effect::EFFECT_CLASS_DRAGON_EYE;

		default :
			return false;
	}

	pCorpse->removeFlag( EClass );

	EffectManager& effectManager = pCorpse->getEffectManager();
	Effect* pEffect = effectManager.findEffect( EClass );
	if (pEffect!=NULL)
	{
		pEffect->unaffect();
		effectManager.deleteEffect( EClass );
	}

	return true;

	__END_CATCH
}

void
saveItemInCorpse(Item* pItem, Corpse* pCorpse)
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pCorpse!=NULL);

	if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE
		|| pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL
		|| pItem->isFlagItem() 
		|| pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{
		Zone* pZone = pCorpse->getZone();
		Assert(pZone!=NULL);

		char pField[80];

		pZone->registerObject( pItem );

		sprintf(pField, "ObjectID = %lu, OwnerID='%d', Storage=%d, StorageID=%lu", 
						pItem->getObjectID(), (int)pZone->getZoneID(), (int)STORAGE_CORPSE, pCorpse->getObjectID());

		pItem->tinysave( pField );
	}

	__END_CATCH
}

bool isRelicItem(const Item* pItem)
{
	if (pItem!=NULL)
	{
		Item::ItemClass IClass = pItem->getItemClass();

		return isRelicItem( IClass );
	}

	return false;
}

bool isRelicItem(Item::ItemClass IClass)
{
	if (IClass==Item::ITEM_CLASS_RELIC
		|| IClass==Item::ITEM_CLASS_BLOOD_BIBLE
		|| IClass==Item::ITEM_CLASS_CASTLE_SYMBOL
		|| IClass==Item::ITEM_CLASS_WAR_ITEM
		)
	{
		return true;
	}

	return false;
}

// Zone에 있는 pCorpse가 pItem을 가지고 있다.
bool
addHasRelicEffect(Zone* pZone, Corpse* pCorpse, Item* pItem)
	
{
	__BEGIN_TRY
		
	if (pZone==NULL) return false;
	
	Assert(pCorpse!=NULL);
	Assert(pItem!=NULL);

	EffectHasRelic* pRelicEffect = NULL;

	// 성단이 성서를 가지고 있다는 표시
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLOOD_BIBLE :
		{
			pRelicEffect = new EffectHasBloodBible( pCorpse );
		}
		break;

		case Item::ITEM_CLASS_CASTLE_SYMBOL :
		{
			pRelicEffect = new EffectHasCastleSymbol( pCorpse );
		}
		break;

		default :
			return false;
	}

	pRelicEffect->setZone( pZone );
	pRelicEffect->setXY( pCorpse->getX(), pCorpse->getY() );
	//pRelicEffect->setNextTime( 1*10 );   // 1초 후
	pRelicEffect->setTick( 1*60*10 );    // 1분마다 메세지 출력
	pRelicEffect->setPart( pItem->getItemType() );

	pRelicEffect->affect();

	EffectManager& effectManager = pCorpse->getEffectManager();
	pCorpse->setFlag( pRelicEffect->getEffectClass() );
	effectManager.addEffect( pRelicEffect );

	// 이펙트를 붙여주라고 한다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCorpse->getObjectID() );
	gcAddEffect.setEffectID( pRelicEffect->getSendEffectClass() );
	gcAddEffect.setDuration( 65000 );
	pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);

	return true;

	__END_CATCH
}


bool deleteRelicEffect(Creature* pCreature, Item* pItem) 
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pCreature!=NULL);

	Effect::EffectClass effectClass;

	if (pItem->getItemClass()==Item::ITEM_CLASS_RELIC)
	{
		const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );
		Assert( pRelicInfo != NULL );

		if ( pRelicInfo->relicType == RELIC_TYPE_SLAYER )
			effectClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
		else if ( pRelicInfo->relicType == RELIC_TYPE_VAMPIRE )
			effectClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
		else
			throw Error("잘못된 Relic Item Type 입니다.");
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
	}
	else if ( pItem->getItemClass() == Item::ITEM_CLASS_WAR_ITEM )
	{
		effectClass = Effect::EFFECT_CLASS_DRAGON_EYE;
	}
	else
	{
		return false;
	}

	// has relic 이펙트를 찾아서 이펙트를 지워준다.
	Effect* pEffect = pCreature->findEffect( effectClass );
	if ( pEffect != NULL )
	{
		pCreature->removeFlag( effectClass );
		pEffect->unaffect();
		pCreature->deleteEffect( effectClass );

		return true;
	}

	return false;

	__END_CATCH
}

bool
addRelicEffect(Creature* pCreature, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(pItem!=NULL);

	// 성물을 가졌다는 이펙트를 붙인다.
	Effect::EffectClass effectClass;
	Effect::EffectClass effectClassSend;

	Item::ItemClass itemclass 	= pItem->getItemClass();
	ItemType_t		itemtype	= pItem->getItemType();

	if (itemclass == Item::ITEM_CLASS_RELIC)
	{
		const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(itemtype));

		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			effectClassSend = effectClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			EffectHasRelic* pEffect = new EffectHasSlayerRelic(pCreature);
			//pEffect->setNextTime( 1*10 );	// 10초 후
			pEffect->setTick( 1*60*10 );	// 1분마다 메세지 출력
			pCreature->addEffect( pEffect );
			pEffect->affect();
		}
		else
		{
			effectClassSend = effectClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			EffectHasRelic* pEffect = new EffectHasVampireRelic(pCreature);
			//pEffect->setNextTime( 1*10 );	// 10초 후
			pEffect->setTick( 1*60*10 );	// 1분마다 메세지 출력
			pCreature->addEffect( pEffect );
			pEffect->affect();
		}
	}
	else if (itemclass == Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
		effectClassSend = (Effect::EffectClass)((int)Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE + itemtype);
		EffectHasRelic* pEffect = new EffectHasBloodBible(pCreature);
		//pEffect->setNextTime( 1*10 );	// 10초 후
		pEffect->setTick( 1*60*10 );	// 1분마다 메세지 출력
		pEffect->setPart( itemtype );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else if (itemclass == Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
		effectClassSend = (Effect::EffectClass)((int)Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL + itemtype);
		EffectHasRelic* pEffect = new EffectHasCastleSymbol(pCreature);
		//pEffect->setNextTime( 1*10 );	// 10초 후
		pEffect->setTick( 1*60*10 );	// 1분마다 메세지 출력
		pEffect->setPart( itemtype );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else if ( itemclass == Item::ITEM_CLASS_WAR_ITEM )
	{
		effectClass = Effect::EFFECT_CLASS_DRAGON_EYE;
		effectClassSend = effectClass;
		EffectHasRelic* pEffect = new EffectDragonEye(pCreature);
		EffectDragonEye* pDragonEyeEffect = dynamic_cast<EffectDragonEye*>(pEffect);
		pDragonEyeEffect->setItemID( pItem->getItemID() );
		pEffect->setTick( 999999 );
		pEffect->setPart( 0 );
		pCreature->setFlag( effectClass );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else
	{
		return false;
	}

	pCreature->setFlag( effectClass );

	// Effect붙였다고 알려준다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCreature->getObjectID() );
	gcAddEffect.setEffectID( effectClassSend );
	gcAddEffect.setDuration( 65000 );
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	return true;

	__END_CATCH
}


bool dropRelicToZone(PlayerCreature* pPC, Item* pItem)
	
{
	Zone* pZone = pPC->getZone();
	Assert(pZone!=NULL);

	// 일단 아이템을 바닥에 떨어뜨린다.
	// 시체와 겹칠 수도 있으므로.. 캐릭터가 없는 곳에 떨어뜨린다.
	TPOINT pt = pZone->addItem( pItem, pPC->getX(), pPC->getY(), false );

	if ( pt.x != -1 )           // 떨어뜨리는데 성공했다면
	{
		char pField[80];
		sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
		pItem->tinysave(pField);

		// 인벤토리에서 뺀다.
		//pInventory->deleteItem( pItem->getObjectID() );
		deleteRelicEffect( pPC, pItem );

		// Relic이 떨어진 곳의 정보를 틈틈히 알려주도록 한다.
/*		if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
		{
			EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
			//pPosition->setNextTime(10);     // 1초 후 메세지 뿌린다.
			pPosition->setTick( 1*60*10 );  // 1분마다 한번씩 알린다.
			pPosition->setZoneID( pZone->getZoneID() );
			pPosition->setX( pt.x );
			pPosition->setY( pt.y );
			pPosition->setPart( pItem->getItemType() );
			pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
			pItem->getEffectManager().addEffect( pPosition );
			pPosition->affect();
		}*/


		// 전체 사용자에게 Relic 이 떨어졌다는 메시지를 보낸다.
		/*
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		StringStream msg;
		msg << pRelicInfo->getName() << " 성물이 " << pZoneInfo->getFullName() << " ( " << pt.x << " , " << pt.y << " ) 에 떨어졌습니다.";

		GCSystemMessage message;
		message.setMessage( msg.toString() );
		g_pZoneGroupManager->broadcast( &message );
		*/
		if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_LOCK ))
		{
			EffectRelicLock* pLock = new EffectRelicLock(pItem);
			pLock->setDeadline( 10*10 ); // 10초
			pItem->setFlag( Effect::EFFECT_CLASS_RELIC_LOCK );
			pItem->getEffectManager().addEffect( pLock );
		}
	}
	else
	{
		throw Error("Logout하는데 성물 떨어뜨릴 자리가 없다");
		//return false;
	}

	return true;
}


bool dropRelicToZone(Creature* pCreature, bool bSendPacket)
	
{
	__BEGIN_TRY

	bool bDrop = false;

	///////////////////////////////////////////////////////////////////
	// 죽을 때 DragonEye 를 가지고 있다면 원래 위치로 빽~
	///////////////////////////////////////////////////////////////////
	if ( pCreature->isFlag(Effect::EFFECT_CLASS_DRAGON_EYE) )
	{
		g_pDragonEyeManager->warpToDefaultPosition( pCreature );

		Effect* pEffect = pCreature->findEffect( Effect::EFFECT_CLASS_DRAGON_EYE );
		if ( pEffect != NULL )
		{
			pCreature->removeFlag( Effect::EFFECT_CLASS_DRAGON_EYE );
			pEffect->unaffect();
			pCreature->deleteEffect( Effect::EFFECT_CLASS_DRAGON_EYE );
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////
	// 죽을 때 Relic Item을 가지고 있다면 바닥에 떨어뜨린다.
	///////////////////////////////////////////////////////////////////
	if ( pCreature->hasRelicItem())
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		// mouse에 relic이 있는지 체크
		Item* pSlotItem = pPC->getExtraInventorySlotItem();

		if (pSlotItem!=NULL 
			&& isRelicItem( pSlotItem ))
		{
			if (dropRelicToZone( pPC, pSlotItem ))
			{
				pPC->deleteItemFromExtraInventorySlot();

				// player의 mouse에서 제거한다.
				// client에서 이 패킷을 받으면
				// mouse에서도 함 체크해주게 했다.

				if (bSendPacket)
				{
					GCDeleteInventoryItem gcDeleteInventoryItem;
					gcDeleteInventoryItem.setObjectID( pSlotItem->getObjectID() );

					pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );
				}

				bDrop = true;
			}
		}

		Zone* pZone = pPC->getZone();
		Assert( pZone != NULL );

		Inventory* pInventory = pPC->getInventory();
		Assert( pInventory != NULL );
		
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		// 인벤토리에서 Relic Item을 찾아본다.
		for ( CoordInven_t y = 0; y < pInventory->getHeight(); y++ )
		{
			for ( CoordInven_t x = 0; x < pInventory->getWidth(); x++ )
			{
				Item* pItem = pInventory->getItem( x, y );
				if ( pItem != NULL 
					&& isRelicItem( pItem ))
				{
					// 일단 아이템을 바닥에 떨어뜨린다.
					if (dropRelicToZone(pPC, pItem))
					{
						// 인벤토리에서 뺀다.
						pInventory->deleteItem( pItem->getObjectID() );

						// player의 inventory에서 제거한다.
						if (bSendPacket)
						{
							GCDeleteInventoryItem gcDeleteInventoryItem;
							gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

							pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );
						}

						bDrop = true;
					}
				}
			}
		}
	}

	return bDrop;

	__END_CATCH
}


// 시체에서 RelicItem이 나오는것 처리
bool
dissectionRelicItem( Corpse* pCorpse, Item* pItem, const TPOINT& pt )
	
{
	__BEGIN_TRY

	if (!isRelicItem( pItem ))
		return false;

	switch (pItem->getItemClass())
	{
		//----------------------------------------------------------------------		
		//
		// 							Relic
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_RELIC :
		{
			// 만약 아이템이 하나도 남지 않았다면(마지막 아이템이었다면, EffectRelic을 삭제해 준다)
			try {
				int relicIndex = pItem->getItemType();
				const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );

				deleteRelicEffect( pCorpse, pItem );

				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_NULL);

                char msg[50];
                sprintf( msg, g_pStringPool->c_str( STRID_RELIC_FROM_RELIC_TABLE ),
                                pRelicInfo->getName().c_str() );

//				StringStream msg;
//				msg << "성물 보관대에서 "
//					<< "성물(" << pRelicInfo->getName() << ")이 나왔습니다.";

				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				g_pZoneGroupManager->broadcast( &gcSystemMessage );


				// relic이 성물보관대에서 빠져나왔기 때문에
				// 보너스/패널티를 다시 조정해준다.
				g_pCombatInfoManager->computeModify();
			} catch (Throwable& t) {
				cout << t.toString().c_str() << endl;
				throw;
			}
		}
		return true;

		//----------------------------------------------------------------------		
		//
		// 							BloodBible
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_BLOOD_BIBLE :
		{
			//deleteRelicEffect( pCorpse, pItem );

			const BloodBibleInfo* pBloodBibleInfo = dynamic_cast<BloodBibleInfo*>(g_pBloodBibleInfoManager->getItemInfo( pItem->getItemType() ) );

//			StringStream msg;
//			msg << "피의 성서 조각(" << pBloodBibleInfo->getName() << ")이 나왔습니다.";

			char msg[200];
			sprintf( msg, g_pStringPool->c_str( STRID_BLOOD_BIBLE_FROM_SHRINE ),
							pBloodBibleInfo->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			//g_pZoneGroupManager->broadcast( &gcSystemMessage );
			g_pHolyLandManager->broadcast( &gcSystemMessage );

			// 성서 조각 아이템 위치 변경
			if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
			{
				EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
				//pPosition->setNextTime(10);     // 1초 후 메세지 뿌린다.
				pPosition->setTick( 1*60*10 );  // 1분마다 한번씩 알린다.
				pPosition->setZoneID( pCorpse->getZone()->getZoneID() );
				pPosition->setX( pt.x );
				pPosition->setY( pt.y );
				pPosition->setPart( pItem->getItemType() );
				pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
				pItem->getEffectManager().addEffect( pPosition );
				pPosition->affect();
			}

		}
		return true;

		//----------------------------------------------------------------------		
		//
		// 							CastleSymbol
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_CASTLE_SYMBOL :
		{
			//deleteRelicEffect( pCorpse, pItem );

			const CastleSymbolInfo* pCastleSymbolInfo = dynamic_cast<const CastleSymbolInfo*>(g_pCastleSymbolInfoManager->getItemInfo( pItem->getItemType() ) );

			if ( pCastleSymbolInfo != NULL )
			{
//				StringStream msg;
//				msg << "성 상징물(" << pCastleSymbolInfo->getName() << ")이 나왔습니다.";

				char msg[200];
				sprintf( msg, g_pStringPool->c_str( STRID_CASTLE_SYMBOL_FROM_SHRINE ),
								pCastleSymbolInfo->getName().c_str() );
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				//g_pZoneGroupManager->broadcast( &gcSystemMessage );
				g_pCastleInfoManager->broadcastShrinePacket( pItem->getItemType(), &gcSystemMessage );


				// 성서 조각 아이템 위치 변경
				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
				{
					EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
					//pPosition->setNextTime(10);     // 1초 후 메세지 뿌린다.
					pPosition->setTick( 1*60*10 );  // 1분마다 한번씩 알린다.
					pPosition->setZoneID( pCorpse->getZone()->getZoneID() );
					pPosition->setX( pt.x );
					pPosition->setY( pt.y );
					pPosition->setPart( pItem->getItemType() );
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
					pItem->getEffectManager().addEffect( pPosition );
					pPosition->affect();
				}
			}
		}
		return true;


		default :
			return false;
	}

	return false;

	__END_CATCH
}

// Relic이 pCorpse에서 어딘가로 warp되었다고 할때
// pCorpse에 Effect를 붙여준다.
void
sendRelicWarpEffect(Corpse* pCorpse)
	
{
	__BEGIN_TRY

	Assert(pCorpse!=NULL);

	if (pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD))
	{
		sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_GUARD_WARP );
	}
	else if (pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY))
	{
		sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_HOLY_WARP );
	}
	else 
	{
		ZoneID_t relicZoneID = pCorpse->getZone()->getZoneID();
		ZoneID_t castleZoneID;

		bool isCastle = g_pCastleInfoManager->getCastleZoneID( relicZoneID, castleZoneID );

		if (!isCastle)
			return;

		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
		Assert( pCastleInfo != NULL );

		if (pCastleInfo->getRace()==RACE_SLAYER)
		{
			sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_CASTLE_SHRINE_SLAYER_WARP );
		}
		else
		{
			sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_CASTLE_SHRINE_VAMPIRE_WARP );
		}
	}

	__END_CATCH
}

