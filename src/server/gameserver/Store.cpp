#include "Store.h"
#include "Item.h"

BYTE StoreItem::removeItem()
{
	if ( !m_bExist ) return 1;

	m_bExist = false;
	m_pItem = NULL;
	m_Price = 0;

	return 0;
}

BYTE StoreItem::setItem(Item* pItem, Gold_t price)
{
	if ( m_bExist ) return 2;

	m_bExist = true;
	m_pItem = pItem;
	m_Price = price;

	return 0;
}

void StoreItem::makeStoreItemInfo( StoreItemInfo& info )
{
	info.setItemExist( (m_bExist)?1:0 );
	if ( !m_bExist ) return;

	m_pItem->makePCItemInfo( info );
//	cout << "make ObjectID : " << (int)m_pItem->getObjectID() << endl;
	info.setPrice( m_Price );
}

Store::Store() : m_bOpen(false), m_StoreItems(MAX_ITEM_NUM)
{
	m_StoreInfo.setOpen(0);
	vector<StoreItem>::iterator itr = m_StoreItems.begin();
	BYTE index = 0;
	for ( ; itr != m_StoreItems.end(); ++itr )
	{
		itr->makeStoreItemInfo( m_StoreInfo.getStoreItemInfo(index++) );
	}
}

BYTE Store::setStoreItem( BYTE index, Item* pItem, Gold_t price )
{
	StoreItem& storeItem = getStoreItem(index);

	BYTE result = storeItem.setItem( pItem, price );
	if ( result != 0 ) return result;

//	cout << "add ObjectID : " << (int)pItem->getObjectID() << endl;
	storeItem.makeStoreItemInfo( m_StoreInfo.getStoreItemInfo(index) );

	if ( pItem->isOnStore() )
	{
		filelog("StoreBug.log", "already on store : %s", pItem->toString().c_str());
	}

	pItem->displayItem(this);
	return result;
}

BYTE Store::removeStoreItem( BYTE index )
{
	StoreItem& storeItem = getStoreItem(index);
	Item* pItem = storeItem.getItem();

	BYTE result = storeItem.removeItem();
	if ( result != 0 ) return result;

	storeItem.makeStoreItemInfo( m_StoreInfo.getStoreItemInfo(index) );

	if ( pItem == NULL )
	{
		filelog("StoreBug.log", "null item displayed");
	}

	if ( !pItem->isOnStore() )
	{
		filelog("StoreBug.log", "not on store : %s", pItem->toString().c_str());
	}

	if ( pItem != NULL ) pItem->undisplayItem();
	
	return result;
}

bool Store::hasItem(Item* pItem) const
{
	if ( pItem == NULL ) return false;
	return hasItem(pItem->getObjectID());
}

bool Store::hasItem(ObjectID_t oid) const
{
	vector<StoreItem>::const_iterator itr = m_StoreItems.begin();

	for ( ; itr != m_StoreItems.end(); ++itr )
	{
		//add by viva for server crash : itr != NULL
		if( itr != NULL)
		{
			if ( itr->isExists() )
			{
				if ( itr->getItem()->getObjectID() == oid ) return true;
			}
		}
	}

	return false;
}

BYTE Store::getItemIndex(Item* pItem) const
{
	if ( pItem == NULL ) return 0xff;
	return getItemIndex(pItem->getObjectID());
}

BYTE Store::getItemIndex(ObjectID_t oid) const
{
	for ( BYTE ret = 0; ret < MAX_ITEM_NUM ; ++ret )
	{
		if ( m_StoreItems[ret].isExists() )
		{
			if ( m_StoreItems[ret].getItem()->getObjectID() == oid ) return ret;
		}
	}

	return 0xff;
}

void Store::updateStoreInfo()
{
//	cout << __PRETTY_FUNCTION__ << endl;
	for ( BYTE index = 0; index < MAX_ITEM_NUM ; ++index )
	{
		m_StoreItems[index].makeStoreItemInfo( m_StoreInfo.getStoreItemInfo(index) );
	}
}
