//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToZoneHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToZone.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemUtil.h"
	#include "ItemInfoManager.h"
	#include "LogClient.h"
	#include "ZoneGroupManager.h"
	#include "StringStream.h"
	#include "CreatureUtil.h"
	#include "StringPool.h"

	#include "Relic.h"
	#include "RelicUtil.h"
	#include "ZoneInfoManager.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectRelicLock.h"
	#include "EffectRelicPosition.h"

	#include "Belt.h"
	#include "Sweeper.h"
	#include "OustersArmsband.h"

	#include "Gpackets/GCAddNewItemToZone.h"
	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCRemoveEffect.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCDeleteObject.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToZoneHandler::execute (CGAddMouseToZone* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature   = pGamePlayer->getCreature();
	bool        Success     = false;

	//EffectHasRelic* pEffect = NULL;

	Zone*          	pZone   = pCreature->getZone();
	PlayerCreature* pPC     = dynamic_cast<PlayerCreature*>(pCreature);

	InventorySlot* pExtraInventorySlot = pPC->getExtraInventorySlot();
	Item*          pItem               = pExtraInventorySlot->getItem();

	if (pItem == NULL)
	{
		//throw ProtocolException("CGAddMouseToZoneHandler::execute() : 존에 떨어뜨리려 하는 아이템이 존재하지 않습니다.");
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	if (pCreature->isSlayer()) 
	{
		Slayer*        pSlayer             = dynamic_cast<Slayer*>(pCreature);

		if (pSlayer->hasRideMotorcycle()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}
	} 

	if (pCreature->isOusters()) 
	{
		Ousters*        pOusters             = dynamic_cast<Ousters*>(pCreature);

		if (pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}
	} 

	ObjectID_t ItemObjectID = pItem->getObjectID();

/*	if ( pItem->isQuestItem() )
	{
		pPC->deleteItemFromExtraInventorySlot();

		// ItemTrace 를 남긴다
		if ( pItem != NULL && pItem->isTraceItem() )
		{
			remainTraceLog( pItem, pCreature->getName(), "DropQuestItem", ITEM_LOG_DELETE, DETAIL_DROP);
		}

		pItem->destroy();
		SAFE_DELETE( pItem );

		Success = true;
	}*/
	if (ItemObjectID == pPacket->getObjectID()
		&& canDropToZone( pPC, pItem )
	) 
	{
		// Item을 Zone에 Access 한다.
		// 일단 자신의 위치에 Item을 떨어 트린다.
		// 나중엔 아이템이 떨어진 Tile을 찾아야 한다.
		// CREATE_TYPE_GAME인 아이템은 10초 후 사라지게 한다.
		Turn_t decayTurn = 0;
		if (pItem->getCreateType()==Item::CREATE_TYPE_GAME)
			decayTurn = 100;

		TPOINT pt = pZone->addItem(pItem, pCreature->getX(), pCreature->getY(), true, decayTurn);

		if (pt.x != -1) 
		{
			pItem->whenPCLost(pPC);
			//pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", (int)STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
			pItem->tinysave(pField);

			// belt일 경우 벨트 안의 아이템들도 모두 주인이 없어져야 한다. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_BELT )
			{
				sprintf(pField, "OwnerID=''");

				Belt* pBelt = dynamic_cast<Belt*>( pItem );
				Assert( pBelt != NULL );

				Inventory* pBeltInventory = pBelt->getInventory();
				PocketNum_t	num = pBelt->getPocketCount();
				
				for ( SlotID_t count = 0 ; count < num ; ++count )
				{
					Item* pBeltItem = pBeltInventory->getItem( count, 0 );
					if ( pBeltItem != NULL )
					{
						pBeltItem->tinysave( pField );
					}
				}
			}

			// 암스밴드일 경우 안의 아이템들도 모두 주인이 없어져야 한다. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND )
			{
				sprintf(pField, "OwnerID=''");

				OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>( pItem );
				Assert( pOustersArmsband != NULL );

				Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
				PocketNum_t	num = pOustersArmsband->getPocketCount();
				
				for ( SlotID_t count = 0 ; count < num ; ++count )
				{
					Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem( count, 0 );
					if ( pOustersArmsbandItem != NULL )
					{
						pOustersArmsbandItem->tinysave( pField );
					}
				}
			}

			pPC->deleteItemFromExtraInventorySlot();

			if ( pItem->isFlagItem() )
			{
				Effect* pEffect = pPC->findEffect(Effect::EFFECT_CLASS_HAS_FLAG);

				if ( pEffect != NULL ) pEffect->setDeadline(0);

				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_LOCK ))
				{
					EffectRelicLock* pLock = new EffectRelicLock(pItem);
					pLock->setDeadline( 10*10 ); // 10초
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_LOCK );
					pItem->getEffectManager().addEffect( pLock );
				}
			}

			if ( pItem->getItemClass() == Item::ITEM_CLASS_SWEEPER )
			{
				Effect* pEffect = pPC->findEffect( Effect::EFFECT_CLASS_HAS_SWEEPER );
				if ( pEffect != NULL ) pEffect->setDeadline(0);

				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_LOCK ))
				{
					EffectRelicLock* pLock = new EffectRelicLock(pItem);
					pLock->setDeadline( 10*10 ); // 10초
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_LOCK );
					pItem->getEffectManager().addEffect( pLock );
				}

				// 떨어뜨린 걸 존에 뿌려준다.
				char race[15];
				if ( pCreature->isSlayer() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
				}
				else if ( pCreature->isVampire() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
				}
				else if ( pCreature->isOusters() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
				}
				else 
				{
					Assert(false);
				}

				const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

				char msg[100];
				sprintf( msg , g_pStringPool->c_str( STRID_DROP_SWEEPER ) , 
									pSweeperInfo->getName().c_str(),
									pCreature->getName().c_str(),
									race
						);
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				pZone->broadcastPacket( &gcSystemMessage );
			}


			// Relic 을 바닥에 놓는 경우라면 Effect를 없애준다.
			if ( isRelicItem( pItem ))
			{
				deleteRelicEffect( pPC, pItem );
				
				// 한동안 주울 수 없도록 이펙트를 붙인다.
				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_LOCK ))
				{
					EffectRelicLock* pLock = new EffectRelicLock(pItem);
					pLock->setDeadline( 10*10 ); // 10초
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_LOCK );
					pItem->getEffectManager().addEffect( pLock );
				}
				else
				{
					// 기존에꺼 찾아서 시간 늘려준다.
				}

				// Relic이 떨어진 곳의 정보를 틈틈히 알려주도록 한다.
/*				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
				{
					EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
					pPosition->setNextTime(10);		// 1초 후 메세지 뿌린다.
					pPosition->setTick( 1*60*10 ); 	// 1분마다 한번씩 알린다.
					pPosition->setZoneID( pZone->getZoneID() );
					pPosition->setX( pt.x );
					pPosition->setY( pt.y );
					pPosition->setPart( pItem->getItemType() );
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
					pItem->getEffectManager().addEffect( pPosition );
				}
				else
				{
					// 기존에꺼 찾아서 값을 바꿔준다.
				}
*/

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
			}

			log(LOG_DROP_ITEM, pCreature->getName(), "", pItem->toString());

			// ItemTrace 를 남긴다
			if ( pItem != NULL && pItem->isTraceItem() )
			{
				char zoneName[15];
				sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
				remainTraceLog( pItem, pCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
			}

			Success = true;
			// edit by Coffee 2007-6-9
			//if ( pItem->isQuestItem() || ( pItem->getItemClass()==Item::ITEM_CLASS_MOON_CARD && pItem->getItemType()==2 ) )
			if ( pItem->isQuestItem() || ( pItem->getItemClass()==Item::ITEM_CLASS_MOON_CARD && pItem->getItemType()==2 ) ||
				( pItem->getItemClass()==Item::ITEM_CLASS_MOON_CARD && pItem->getItemType()==5 ) ||
				( pItem->getItemClass()==Item::ITEM_CLASS_MOON_CARD && pItem->getItemType()==6 ) ||
				( pItem->getItemClass()==Item::ITEM_CLASS_MOON_CARD && pItem->getItemType()==7 ))
			{
				// 퀘스트 아이템일 경우 바로 지운다.
				// 바보 클라이언트 때문에 마우스에 있는거 바로 못 지운다.
				// 그래서 이렇게 처리한다.
				pZone->deleteItem(pItem , pt.x, pt.y);

				GCDeleteObject gcDeleteObject;
				gcDeleteObject.setObjectID( pItem->getObjectID() );

				pZone->broadcastPacket( pt.x, pt.y, &gcDeleteObject );
			}
		} 
		else 
		{
			Success = false;
		}
	}

	// Adding을 실패하였을때.
	if (!Success)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
