#include "Assert.h"
#include "Player.h"
#include "Slayer.h"
#include "Vampire.h"
#include "PacketUtil.h"
#include "PlayerCreature.h"
#include "ItemNameInfo.h"
#include "FlagSet.h"
#include "StringPool.h"

#include "WaitForApart.h"
#include "CoupleManager.h"

#include "item/CoupleRing.h"
#include "item/VampireCoupleRing.h"
#include "item/CoupleRingBase.h"
#include "ItemFactoryManager.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCRemoveFromGear.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

uint WaitForApart::waitPartner( PlayerCreature* pTargetPC )
	throw(Error)
{
	__BEGIN_TRY

	if ( pTargetPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	PlayerCreature* pWaitingPC = getWaitingPC();
	if ( pWaitingPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	if ( !g_pCoupleManager->isCouple( pTargetPC, pWaitingPC ) )
	{
		return COUPLE_MESSAGE_NOT_COUPLE;
	}

	GCSystemMessage gcSystemMessage;
//	StringStream msg;
//	msg << pWaitingPC->getName() << "님으로부터 이별 신청이 왔습니다.";

	char msg[100];
	sprintf( msg, g_pStringPool->c_str( STRID_REQUEST_APART ), pWaitingPC->getName().c_str() );
	gcSystemMessage.setMessage( msg );

	pTargetPC->getPlayer()->sendPacket( &gcSystemMessage );

	return 0;
	
	__END_CATCH
}

uint WaitForApart::acceptPartner( PlayerCreature* pRequestedPC )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pRequestedPC != NULL);

	PlayerCreature* pWaitingPC = getWaitingPC();
	if ( pWaitingPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	if (!g_pCoupleManager->isCouple( pRequestedPC, pWaitingPC )) return COUPLE_MESSAGE_NOT_COUPLE;

	if ( !hasCoupleItem( pRequestedPC ) )
	{
		filelog( "CoupleRing.txt", "don't have coupleRing : %s", pRequestedPC->getName().c_str() );
		return COUPLE_MESSAGE_NOT_COUPLE;
	}
	if ( !hasCoupleItem( pWaitingPC ) )
	{
		filelog( "CoupleRing.txt", "don't have coupleRing : %s", pWaitingPC->getName().c_str() );
		return COUPLE_MESSAGE_NOT_COUPLE;
	}

	Assert( hasCoupleItem( pRequestedPC ) );
	Assert( hasCoupleItem( pWaitingPC ) );

	// 커플링을 없애줘야 함~_~;
	Assert( removeCoupleItem( pRequestedPC ) );
	Assert( removeCoupleItem( pWaitingPC ) );

	// 커플매니저에서 헤어졌다고 등록함
	g_pCoupleManager->removeCouple( pRequestedPC, pWaitingPC );

	// 커플이 깨졌으니 Flag 를 다시 돌려준다.
	pRequestedPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );
	pWaitingPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );

	pRequestedPC->getFlagSet()->save( pRequestedPC->getName() );
	pWaitingPC->getFlagSet()->save( pWaitingPC->getName() );

	return 0;
/*	Inventory* pRequestedPCInven = pRequestedPC->getInventory();
	Inventory* pWaitingPCInven = pWaitingPC->getInventory();

	Item::ItemClass IClass = Item::ITEM_CLASS_COUPLE_ITEM;
	Item* pRequestedPCCoupleItem = pRequestedPCInven->findItem(IClass , 0);
	Item* pWaitingPCCoupleItem = pWaitingPCInven->findItem(IClass , 0);

	if (pRequestedPCCoupleItem != NULL && pWaitingPCCoupleItem != NULL)
	{
		pRequestedPCInven->deleteItem(pRequestedPCCoupleItem->getObjectID());
		pWaitingPCInven->deleteItem(pWaitingPCCoupleItem->getObjectID());

		GCDeleteInventoryItem gcDeleteRequestedPCInventoryCoupleItem;
		GCDeleteInventoryItem gcDeleteWaitingPCInventoryCoupleItem;

		gcDeleteRequestedPCInventoryCoupleItem.setObjectID( pRequestedPCCoupleItem->getObjectID() );
		gcDeleteWaitingPCInventoryCoupleItem.setObjectID( pWaitingPCCoupleItem->getObjectID() );

		pRequestedPC->getPlayer()->sendPacket( &gcDeleteRequestedPCInventoryCoupleItem );
		pWaitingPC->getPlayer()->sendPacket( &gcDeleteWaitingPCInventoryCoupleItem );

		// 커플이 깨졌으니 PlayerCreature 에 ItemNameInfo 도 없애줘야하는뎅 ;;
		// 그냥 NULL 로 셋팅하자 ~_~
		pRequestedPC->deleteItemNameInfoList( pRequestedPCCoupleItem->getObjectID() );
		pWaitingPC->deleteItemNameInfoList( pWaitingPCCoupleItem->getObjectID() );

		// 아이템을 없애준다.
		pRequestedPCCoupleItem->destroy();
		SAFE_DELETE( pRequestedPCCoupleItem );
		pWaitingPCCoupleItem->destroy();
		SAFE_DELETE( pWaitingPCCoupleItem );

		// 딴 남자 or 여자 찾아 떠나야 하므로. 
		
		return true;
	}

	return false;
	*/

	__END_CATCH
}
void WaitForApart::timeExpired()
	throw(Error)
{
	__BEGIN_TRY

	// 헤어짐이 거절당했다고 보내준다.
	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_APART_WAIT_TIME_EXPIRED );

	PlayerCreature* pWaitingPC = getWaitingPC();
	if ( pWaitingPC != NULL )
		pWaitingPC->getPlayer()->sendPacket( &gcNPCResponse );
	
	__END_CATCH
}

bool WaitForApart::removeCoupleItem( PlayerCreature* pPC )
	throw(Error)
{
	__BEGIN_TRY

	// 네손가락-_-부터 뒤진다.
	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>( pPC );
		Assert( pSlayer != NULL );

		for ( Slayer::WearPart i = Slayer::WEAR_FINGER1 ; i <= Slayer::WEAR_FINGER4 ; ++(int)i )
		{
			Item* pRing = pSlayer->getWearItem( i );
			if ( pRing != NULL )
			{
				if ( isMatchCoupleRing( pPC, pRing ) )
				{
//					pSlayer->deleteWearItem( i );
					pSlayer->takeOffItem( i, false, true );
					pRing->destroy();
					SAFE_DELETE( pRing );

					GCRemoveFromGear gcRemoveFromGear;
					gcRemoveFromGear.setSlotID( i );

					pPC->getPlayer()->sendPacket( &gcRemoveFromGear );

					return true;
				}
			}
		}
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>( pPC );
		Assert( pVampire != NULL );

		for ( Vampire::WearPart i = Vampire::WEAR_FINGER1 ; i <= Vampire::WEAR_FINGER4 ; ++(int)i )
		{
			Item* pRing = pVampire->getWearItem( i );
			if ( pRing != NULL )
			{
				if ( isMatchCoupleRing( pPC, pRing ) )
				{
//					pVampire->deleteWearItem( i );
					pVampire->takeOffItem( i, false, true );
					pRing->destroy();
					SAFE_DELETE( pRing );

					GCRemoveFromGear gcRemoveFromGear;
					gcRemoveFromGear.setSlotID( i );

					pPC->getPlayer()->sendPacket( &gcRemoveFromGear );

					return true;
				}
			}
		}
	}
	else Assert( false );
	
	// 마우스에 아이템이 있다.
	Item* pCoupleItem = pPC->getExtraInventorySlotItem();
	if ( pCoupleItem == NULL || !isMatchCoupleRing( pPC, pCoupleItem ) )
	{
		// 마우스에 아이템이 없거나 마우스에 있는 아이템이 커플링이 아니면 인벤토리를 뒤진다.
		pCoupleItem = pPC->getInventory()->findItem( getItemClass( pPC ), getItemType( pPC ) );
		if ( pCoupleItem != NULL ) pPC->getInventory()->deleteItem( pCoupleItem->getObjectID() );
	}
	else
	{
		pPC->deleteItemFromExtraInventorySlot();
	}

	if ( pCoupleItem == NULL ) return false;

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pCoupleItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	pCoupleItem->destroy();
	SAFE_DELETE( pCoupleItem );

	return true;
/*	Item* pPCCoupleItem = getCoupleItem( pPC );
	if ( pPCCoupleItem == NULL ) return false;

	pPC->getInventory()->deleteItem( pPCCoupleItem->getObjectID() );
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pPCCoupleItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

//	pPC->deleteItemNameInfoList( pPCCoupleItem->getObjectID() );

	pPCCoupleItem->destroy();
	SAFE_DELETE( pPCCoupleItem );

	return true;*/

	__END_CATCH
}

Item* WaitForApart::getCoupleItem( PlayerCreature* pPC ) throw(Error)
{
	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>( pPC );
		Assert( pSlayer != NULL );

		for ( Slayer::WearPart i = Slayer::WEAR_FINGER1 ; i <= Slayer::WEAR_FINGER4 ; ++(int)i )
		{
			Item* pRing = pSlayer->getWearItem( i );
			if ( pRing != NULL )
			{
				if ( isMatchCoupleRing( pPC, pRing ) )
				{
					return pRing;
				}
			}
		}
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>( pPC );
		Assert( pVampire != NULL );

		for ( Vampire::WearPart i = Vampire::WEAR_FINGER1 ; i <= Vampire::WEAR_FINGER4 ; ++(int)i )
		{
			Item* pRing = pVampire->getWearItem( i );
			if ( pRing != NULL )
			{
				if ( isMatchCoupleRing( pPC, pRing ) )
				{
					return pRing;
				}
			}
		}
	}
	else Assert( false );
	
	return pPC->getInventory()->findItem( getItemClass( pPC ), getItemType( pPC ) );
}
