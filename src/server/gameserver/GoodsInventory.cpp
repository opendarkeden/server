//////////////////////////////////////////////////////////////////////////
// Filename			: GoodsInventory.cpp
// Written By		: bezz
// Description		: 홈페이지에서 구매한 아이템이 담겨 있는 Inventory
//////////////////////////////////////////////////////////////////////////

#include "GoodsInventory.h"
#include "DB.h"


GoodsInventory::~GoodsInventory()
	
{
	clear();
}

void GoodsInventory::clear()
	
{
	__BEGIN_TRY

	ListItemItr itr = m_Goods.begin();
	for ( ; itr != m_Goods.end(); itr++ )
	{
		SAFE_DELETE( (*itr).m_pItem );
	}

	m_Goods.clear();

	__END_CATCH
}

void GoodsInventory::addItem( string ID, Item* pItem )
	
{
	__BEGIN_TRY

	BuyItem buyItem;

	buyItem.m_ID = ID;
	buyItem.m_pItem = pItem;

	m_Goods.push_back( buyItem );

	__END_CATCH
}

Item* GoodsInventory::getItem( ObjectID_t oid )
	
{
	__BEGIN_TRY

	if ( m_Goods.empty() )
		return NULL;

	Item* pItem = NULL;

	ListItemItr itr = m_Goods.begin();

	for ( ; itr != m_Goods.end(); itr++ )
	{
		if ( (*itr).m_pItem->getObjectID() == oid )
		{
			pItem = (*itr).m_pItem;
			break;
		}
	}

	return pItem;

	__END_CATCH
}
Item* GoodsInventory::popItem( ObjectID_t oid )
	
{
	__BEGIN_TRY

	if ( m_Goods.empty() )
		return NULL;

	Item* pItem = NULL;

	ListItemItr itr = m_Goods.begin();

	for ( ; itr != m_Goods.end(); itr++ )
	{
		if ( (*itr).m_pItem->getObjectID() == oid )
		{
			pItem = (*itr).m_pItem;

			filelog( "Goods.log", "아이템을 찾아갔습니다. : [%s:%s]", (*itr).m_ID.c_str(), (*itr).m_pItem->toString().c_str() );

			Statement* pStmt = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
				Result* pResult = pStmt->executeQuery(
						"UPDATE GoodsListObject SET Num = Num - 1, Status = IF( NUM < 1, 'GET', 'NOT' ) WHERE ID=%s",
							(*itr).m_ID.c_str() );

				// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()

				if ( pStmt->getAffectedRowCount() == 0 )
				{
					filelog( "Goods.log", "근데 DB에 업데이트가 안됐습니다. : %s", (*itr).m_ID.c_str() );
				}

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			m_Goods.erase( itr );
			break;
		}
	}

	return pItem;

	__END_CATCH
}

