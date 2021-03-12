///////////////////////////////////////////////////////////////////
// ZoneItemPosition 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Assert.h"

#include "Item.h"
#include "Corpse.h"
#include "Zone.h"
#include "Tile.h"
#include "ZoneGroup.h"
#include "ZoneUtil.h"
#include "Utility.h"
#include "StringStream.h"
#include "Effect.h"

#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "ZoneItemPosition.h"

Item* ZoneItemPosition::getItem_LOCKED( bool isDel )
	
{
	__BEGIN_TRY

	Zone* pZone = getZone();
	if ( pZone == NULL ) 
	{
		filelog( "ItemError.log", "ZoneItemPosition:getItem() : ZoneID가 잘못되었습니다.");
		return NULL;
	}

	Item* pItem = getItemFromZone( pZone );
	if ( pItem == NULL ) return NULL;
	if ( isDel ) deleteItemFromZone( pZone, pItem );

	if ( pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE
		|| pItem->getItemClass() == Item::ITEM_CLASS_CASTLE_SYMBOL )
	{
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setEffectID( Effect::EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_TILE );
		gcAddEffectToTile.setXY( m_ZoneX, m_ZoneY );

		pZone->broadcastPacket( m_ZoneX, m_ZoneY, &gcAddEffectToTile );
	}

	return pItem;

	__END_CATCH
}

Item* ZoneItemPosition::getItem( bool isDel )
	
{
	__BEGIN_TRY

	Zone* pZone = getZone();
	if ( pZone == NULL ) 
	{
		filelog( "ItemError.log", "ZoneItemPosition:getItem() : ZoneID가 잘못되었습니다.");
		return NULL;
	}

	Item* pItem = NULL;

	__ENTER_CRITICAL_SECTION((*pZone))

	pItem = getItemFromZone( pZone );

	if ( pItem == NULL )
	{
		pZone->unlock();
		return NULL;
	}

	if ( isDel )
	{
		deleteItemFromZone( pZone, pItem );
	}

	if ( pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE 
		|| pItem->getItemClass() == Item::ITEM_CLASS_CASTLE_SYMBOL )
	{
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setEffectID( Effect::EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_TILE );
		gcAddEffectToTile.setXY( m_ZoneX, m_ZoneY );

		pZone->broadcastPacket( m_ZoneX, m_ZoneY, &gcAddEffectToTile );
	}

    __LEAVE_CRITICAL_SECTION((*pZone))

	return pItem;

	__END_CATCH
}

Item* ZoneItemPosition::popItem( bool bLock )
	
{
	__BEGIN_TRY

	if ( bLock ) return getItem( true );
	return getItem_LOCKED( true );

	__END_CATCH
}

Item* ZoneItemPosition::getItemFromZone( Zone* pZone )
	
{
	__BEGIN_TRY

	VSRect rect( 0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1 );

	if( !rect.ptInRect( m_ZoneX, m_ZoneY ) )
	{
		filelog( "ItemError.log", "ZoneItemPosition:getItem() : 아이템 좌표가 잘못되었습니다." );

		return NULL;
	}

	Tile& tile = pZone->getTile( m_ZoneX, m_ZoneY );

	if( !tile.hasItem() )
	{
		filelog( "ItemError.log", "ZoneItemPosition:getItem() : 아이템이 없습니다." );

		return NULL;
	}

	return tile.getItem();

	__END_CATCH
}

void ZoneItemPosition::deleteItemFromZone( Zone* pZone, Item* pItem )
	
{
	__BEGIN_TRY

	pZone->deleteItem( pItem, m_ZoneX, m_ZoneY );

	GCDeleteObject gcDeleteObject( pItem->getObjectID() );
	pZone->broadcastPacket( m_ZoneX, m_ZoneY, &gcDeleteObject );

	__END_CATCH
}

string ZoneItemPosition::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ZoneItemPosition("
		<< "ZoneID:" << (int)m_ZoneID
		<< ",ZoneX:" << (int)m_ZoneX
		<< ",ZoneY:" << (int)m_ZoneY
		<< ")";

	return msg.toString();

	__END_CATCH
}
