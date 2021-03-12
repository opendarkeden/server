///////////////////////////////////////////////////////////////////
// InventoryItemPosition 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Assert.h"

#include "Item.h"
#include "PlayerCreature.h"
#include "Player.h"
#include "PCFinder.h"
#include "Inventory.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "Effect.h"

#include "Utility.h"
#include "CreatureUtil.h"
#include "RelicUtil.h"

#include "InventoryItemPosition.h"

#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCAddEffect.h"

Item* InventoryItemPosition::popItem( bool bLock )
	
{
	__BEGIN_TRY

	if ( bLock ) return popItem_UNLOCKED();
	return popItem_LOCKED();

	__END_CATCH
}

Item* InventoryItemPosition::popItem_LOCKED()
	
{
	__BEGIN_TRY

	Creature* pTargetCreature = findCreature();
	Zone* pZone = getZoneByCreature( pTargetCreature );
	if ( pZone == NULL ) return NULL;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
	Assert( pPC != NULL );

	return popItem_CORE( pPC );

	__END_CATCH
}

Item* InventoryItemPosition::popItem_UNLOCKED()
	
{
	__BEGIN_TRY

	Creature* pTargetCreature = findCreature();

	if (pTargetCreature==NULL
		|| !pTargetCreature->isPC())
		return NULL;

	Zone* pZone = getZoneByCreature( pTargetCreature );
	if ( pZone == NULL ) return NULL;

	Item* pItem = NULL;

	__ENTER_CRITICAL_SECTION( (*pZone) )

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
	Assert( pPC != NULL );

	pItem = popItem_CORE( pPC );

	/*
	if ( pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE )
	{
		GCAddEffect gcAddEffect;
		gcAddEffect.setEffectID( Effect::EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_ME );
		gcAddEffect.setObjectID( pPC->getObjectID() );

		pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );
	}
	*/

    __LEAVE_CRITICAL_SECTION((*pZone))

	return pItem;

	__END_CATCH
}

Zone* InventoryItemPosition::getZone() 
	
{
	__BEGIN_TRY

	if ( m_bSetZone ) return m_pZone;
	
	Creature* pCreature = findCreature();
	if ( pCreature == NULL ) return NULL;

	return getZoneByCreature( pCreature );
	
	__END_CATCH
}

Creature* InventoryItemPosition::findCreature()
	
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

Zone* InventoryItemPosition::getZoneByCreature( Creature* pCreature )
	
{
	__BEGIN_TRY

	if ( m_bSetZone ) return m_pZone;

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	m_bSetZone = true;
	m_pZone = pZone;

	return pZone;

	__END_CATCH
}

Item* InventoryItemPosition::popItem_CORE( PlayerCreature* pPC )
	
{
	__BEGIN_TRY

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	if( !pInventory->hasItem( m_InvenX, m_InvenY ) )
	{
		filelog( "ItemError.log", "InventoryItemPosition:getItem() : 해당하는 위치에 아이템이 없습니다.");

		return NULL;
	}

	Item* pItem = pInventory->getItem( m_InvenX, m_InvenY );
	Assert(pItem!=NULL);

	pInventory->deleteItem( pItem->getObjectID() );

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	if ( pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE
		|| pItem->getItemClass() == Item::ITEM_CLASS_CASTLE_SYMBOL )
	{
		deleteRelicEffect( pPC, pItem );
		sendBloodBibleEffect( pPC, Effect::EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_ME );
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

string InventoryItemPosition::toString() const 
	
{
	__BEGIN_TRY

	return "InventoryItemPosition";

	__END_CATCH
}
