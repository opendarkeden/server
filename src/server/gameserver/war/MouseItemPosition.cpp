///////////////////////////////////////////////////////////////////
// MouseItemPosition 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Assert.h"

#include "PlayerCreature.h"
#include "Player.h"
#include "PCFinder.h"
#include "Item.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "Effect.h"

#include "Utility.h"
#include "ZoneUtil.h"
#include "RelicUtil.h"
#include "CreatureUtil.h"

#include "MouseItemPosition.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCAddEffect.h"

Item* MouseItemPosition::popItem( bool bLock )
	
{
	__BEGIN_TRY

	if ( bLock ) return popItem_UNLOCKED();
	return popItem_LOCKED();

	__END_CATCH
}

Item* MouseItemPosition::popItem_UNLOCKED( )
	
{
	__BEGIN_TRY

	Creature* pTargetCreature = findCreature();
	Zone* pZone = getZoneByCreature( pTargetCreature );

	//Assert( pZone != NULL );
	if (pZone==NULL) return NULL;
	
	Item* pItem = NULL;

	__ENTER_CRITICAL_SECTION( (*pZone) )

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
	Assert( pPC != NULL );

	pItem = popItem_CORE( pPC );

    __LEAVE_CRITICAL_SECTION((*pZone))

	return pItem;

	__END_CATCH
}

Item* MouseItemPosition::popItem_LOCKED()
	
{
	__BEGIN_TRY

	Creature* pTargetCreature = findCreature();

	Zone* pZone = getZoneByCreature( pTargetCreature );
	Assert( pZone != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
	Assert( pPC != NULL );

	return popItem_CORE( pPC );

	__END_CATCH
}

Zone* MouseItemPosition::getZone()
	
{
	__BEGIN_TRY

	// 구해놓은게 있으면 그걸로 리턴한다.
	if ( m_bSetZone ) return m_pZone;

	// 구해놓은게 없으면 새로 구한다.
	Creature* pTargetCreature = findCreature();

	return getZoneByCreature( pTargetCreature );

	__END_CATCH
}

Item* MouseItemPosition::popItem_CORE( PlayerCreature* pPC )
	
{
	__BEGIN_TRY

	Item* pItem;

	if ( pPC->getExtraInventorySlotItem() == NULL) 
	{
		filelog( "ItemError.log", "InventoryItemPosition:getItem() : 해당하는 위치에 아이템이 없습니다." );

		return NULL;
	}

	pItem = pPC->getExtraInventorySlotItem();
	pPC->deleteItemFromExtraInventorySlot();

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	if ( pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE
		|| pItem->getItemClass() == Item::ITEM_CLASS_CASTLE_SYMBOL )
	{
		sendBloodBibleEffect( pPC, Effect::EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_ME );
		deleteRelicEffect( pPC, pItem );
	}
	if ( pItem->isFlagItem() )
	{
		Effect* pFlagEffect = pPC->findEffect( Effect::EFFECT_CLASS_HAS_FLAG );
		if ( pFlagEffect != NULL ) pFlagEffect->setDeadline(0);
	}

	if ( pItem->isSweeper() )
	{
		Effect* pEffect = pPC->findEffect( Effect::EFFECT_CLASS_HAS_SWEEPER );
		if ( pEffect != NULL )
		{
			pEffect->setDeadline(0);
		}	
	}
	if ( pItem->getItemClass() == Item::ITEM_CLASS_WAR_ITEM )
	{
		deleteRelicEffect( pPC, pItem );
	}

	return pItem;

	__END_CATCH
}

Creature* MouseItemPosition::findCreature()
	
{
	__BEGIN_TRY

	Creature* pTargetCreature = NULL;

    __ENTER_CRITICAL_SECTION((*g_pPCFinder))


    pTargetCreature = g_pPCFinder->getCreature_LOCKED(m_OwnerName);
    if (pTargetCreature==NULL)
    {
		filelog( "ItemError.log", "InventoryItemPosition:getItem() : 해당하는 Creature가 없습니다." );

        g_pPCFinder->unlock();
        return NULL;
    }

    __LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	return pTargetCreature;

	__END_CATCH
}

Zone* MouseItemPosition::getZoneByCreature( Creature* pCreature ) 
	
{
	if (pCreature==NULL) return NULL;

    Assert(pCreature->isPC());

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );
	
	m_bSetZone = true;
	m_pZone = pZone;

	return pZone;
}

string  MouseItemPosition::toString() const 
	
{
	return "MouseItemPosition";
}

