///////////////////////////////////////////////////////////////////////////
// File : DragonEyeManager.cpp
///////////////////////////////////////////////////////////////////////////

// include files
#include "DragonEyeManager.h"
#include "ItemFactoryManager.h"
#include "ZoneUtil.h"
#include "Zone.h"
#include "GlobalItemPositionLoader.h"
#include "EffectDragonEye.h"

#include <stdio.h>

const int nDragonEyes = 9;

///////////////////////////////////////////////////////////////////////////
// class DragonEyeManager
///////////////////////////////////////////////////////////////////////////
DragonEyeManager::DragonEyeManager()
{
	__BEGIN_TRY

	m_DragonEyes.reserve( nDragonEyes );
	m_DefaultPositions.reserve( nDragonEyes );

	initDefaultPositions();

	__END_CATCH
}

DragonEyeManager::~DragonEyeManager()
{
	__BEGIN_TRY
	__END_CATCH
}

void DragonEyeManager::init()
	throw(Error)
{
	__BEGIN_TRY

	createAllDragonEyes();

	__END_CATCH
}

void DragonEyeManager::initDefaultPositions()
	throw(Error)
{
	__BEGIN_TRY

	// 전쟁 시작시 DragonEye 의 시작 위치 설정.
	m_DefaultPositions[0].set(   73,  24, 121 );		// 슬레이어 / 아담서 / 24 / 121
	m_DefaultPositions[1].set( 1201,  62,  68 );		// 슬레이어 / 옥타부스 / 62 / 68
	m_DefaultPositions[2].set( 1203,  85,  50 );		// 슬레이어 / 셉티무스 / 85 / 50
	m_DefaultPositions[3].set(   71, 111, 124 );		// 뱀파이어 / 아담동 / 111 / 124
	m_DefaultPositions[4].set( 1204,  62,  69 );		// 뱀파이어 / 쿠아르투스 / 62 / 69
	m_DefaultPositions[5].set( 1202,  81,  52 );		// 뱀파이어 / 테르티우스 / 81 / 52 
	m_DefaultPositions[6].set(   72,  66, 168 );		// 아우스터즈 / 아담 / 66 / 168
	m_DefaultPositions[7].set( 1205,  62,  69 );		// 아우스터즈 / 펜타누스 / 62 / 69
	m_DefaultPositions[8].set( 1206,  82,  52 );		// 아우스터즈 / 헥시리우스 / 82 / 52

	__END_CATCH
}

void DragonEyeManager::createAllDragonEyes()
	throw(Error)
{
	__BEGIN_TRY

	// 일단 드래곤 아이 이이템을 생성한다.
	for ( int i=0; i<nDragonEyes; ++i )
	{
		list<OptionType_t> optionNull;
		Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_WAR_ITEM, 0, optionNull );
		Assert( pItem != NULL );

		WarItem* pWarItem = dynamic_cast<WarItem*>(pItem);
		Assert( pWarItem != NULL );

		Zone* pZone = getZoneByZoneID( m_DefaultPositions[i].id );
		Assert( pZone != NULL );

		char strZoneID[10];
		sprintf( strZoneID, "%u", pZone->getZoneID() );

		pZone->registerObject( pWarItem );
		pWarItem->create( strZoneID, STORAGE_ZONE, pZone->getZoneID(), m_DefaultPositions[i].x, m_DefaultPositions[i].y );

		pWarItem->setIndex( i );

		m_DragonEyes[i] = pWarItem;
	}

	__END_CATCH
}

void DragonEyeManager::addAllDragonEyesToZone()
	throw(Error)
{
	__BEGIN_TRY

	// 아이템을 각자의 초기 위치에 놓는다.
	for ( int i=0; i<nDragonEyes; ++i )
	{
		Zone* pZone = getZoneByZoneID( m_DefaultPositions[i].id );
		Assert( pZone != NULL );

		Item* pItem = m_DragonEyes[i];
		Assert( pItem != NULL );

		// 존에 아이템 추가하기
		pZone->addItemDelayed( pItem, m_DefaultPositions[i].x, m_DefaultPositions[i].y );
	}

	__END_CATCH
}

void DragonEyeManager::removeAllDragonEyes()
	throw(Error)
{
	__BEGIN_TRY

	// 존재하는 모든 드래곤 아이이를 볼 수 없도록 없앤다.
	for ( int i=0; i<nDragonEyes; ++i )
	{
		Item::ItemClass ItemClass	= Item::ITEM_CLASS_WAR_ITEM;
		ItemID_t		ItemID		= m_DragonEyes[i]->getItemID();

		GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( ItemClass, ItemID );

		if ( pItemPosition == NULL )
			return;

		// War 쓰레드에서 호출 되므로 락 걸어야 된다.
		pItemPosition->popItem( true );
	}

	__END_CATCH
}

void DragonEyeManager::warpToDefaultPosition( Creature* pCreature )
	throw(Error)
{
	__BEGIN_TRY

	// pCreature 는 드래곤 아이를 가지고 있는 크리쳐이다.
	// 드래곤 아이를 가지고 있던 사용자가 죽거나 나가거나 할때 불린다.
	// 드래곤 아이를 원래 위치로 이동시키는 코드다.
	// GlobalItemPositionLoader 를 사용해서 아이템을 원래 위치에서 제거한다.
	// 원래 존의 포인터를 가져와서 아이템을 넣는다.
	// 이 함수는 사용자가 어떤 행동을 할때 불리는 코드이므로 ZoneGroup 에서 호출되는 코드이다.
	// 그래서 존의 포인터로 작업을 할 때 ZoneGroup 을 비교해보고 작업을 한다.
	EffectDragonEye* pEffect = dynamic_cast<EffectDragonEye*>(pCreature->getEffectManager()->findEffect( Effect::EFFECT_CLASS_DRAGON_EYE ));
	Assert( pEffect != NULL );

	Item::ItemClass ItemClass	= Item::ITEM_CLASS_WAR_ITEM;
	ItemID_t		ItemID		= pEffect->getItemID();

	GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( ItemClass, ItemID );

	if ( pItemPosition == NULL )
		return;

	Item* pItem = pItemPosition->popItem( false );

	if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_WAR_ITEM )
	{
		WarItem* pWarItem = dynamic_cast<WarItem*>(pItem);
		Assert( pWarItem != NULL );

		int index = pWarItem->getIndex();

		Zone* pZone = pCreature->getZone();
		Assert( pZone != NULL );

		Zone* pTargetZone = getZoneByZoneID( m_DefaultPositions[index].id );
		Assert( pTargetZone != NULL );

		if ( pZone->getZoneGroup() == pTargetZone->getZoneGroup() )
			pTargetZone->addItem( pItem, m_DefaultPositions[index].x, m_DefaultPositions[index].y );
		else
			pTargetZone->addItemDelayed( pItem, m_DefaultPositions[index].x, m_DefaultPositions[index].y );
	}

	__END_CATCH
}

DragonEyeManager* g_pDragonEyeManager = NULL;
