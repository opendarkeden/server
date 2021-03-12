//----------------------------------------------------------------------
//
// Filename    : EffectDecayItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectDecayItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "Money.h"
#include "ItemUtil.h"
#include "ZoneUtil.h"
#include "UniqueItemManager.h"
#include "VariableManager.h"

#include <stdio.h>

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectDecayItem::EffectDecayItem (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bDeleteFromDB) 
	
: Effect(pZone,x,y,pItem,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();
	m_bDeleteFromDB = bDeleteFromDB;

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectDecayItem::~EffectDecayItem () 
	
{
	__BEGIN_TRY

	unaffect(m_pZone , m_X , m_Y , m_pTarget);

	__END_CATCH
}
			

//----------------------------------------------------------------------
// affect to target
// 이 이펙트는 타일에 종속되지 않으므로, affect()는 호출되지 않는다.
// 왜냐하면, target은 생성자에서 지정되며, 아무런 일도 하지 않기 때문이다.
//----------------------------------------------------------------------
void EffectDecayItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectDecayItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	// 올바른 좌표이어야 한다.
	Assert(isValidZoneCoord(pZone, x, y));

	// TempItem 변수를 잡는다.
	Item* pTempItem = NULL;

	// 여기서는 지정 아이템이 없을 수 있으며, 또 다른 아이템이 놓여 있을 수도 있다.
	// 이 경우는 오리지널 아이템과 지금 현재 바닥에 있는 아이템을 비교하여 삭제해야 한다.
	// 없을 경우는 무시하면 된다.
	Tile & tile = pZone->getTile(x, y);

	if (tile.hasItem()) {

		pTempItem = tile.getItem();

		if (pTempItem != NULL) {
			// ObjectID가 같다는 말은 같은 아이템이란 말이다.
			//if (pTempItem->getObjectID() == m_ObjectID) {
			if (pTempItem->getObjectID() == m_ObjectID) {

				pZone->deleteItem(pTempItem , x, y);

				// 아이템이 사라졌다는 패킷을 날린다.
				GCDeleteObject gcDeleteObject;
				gcDeleteObject.setObjectID(m_ObjectID);

				pZone->broadcastPacket(x, y , &gcDeleteObject);

				if (m_bDeleteFromDB)
				{
					//ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pTempItem->getItemClass(), pTempItem->getItemType() );
					//Assert(pItemInfo!=NULL);

					// 유니크 아이템인 경우 개수를 줄인다.
					if (pTempItem->isUnique())
					{
						// create한 아이템이 아닌 경우만 지워준다.
						if (pTempItem->getCreateType()!=Item::CREATE_TYPE_CREATE)
							UniqueItemManager::deleteItem( pTempItem->getItemClass(), pTempItem->getItemType() );

						filelog("uniqueItem.txt", "[EffectDecayItem] %s", pTempItem->toString().c_str());
					}

					// ItemTraceLog 를 남긴다
					/*
					 * 존에 떨어진 아이템중 expire time인것들 모두 로그를 빼버린다.
					if ( pTempItem != NULL && pTempItem->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), x, y);
						remainTraceLog( pTempItem, zoneName, "GOD", ITEM_LOG_DELETE, DETAIL_TIMEOUT);
					}
					*/

					// 돈 로그 남기자
					if ( pTempItem->getItemClass() == Item::ITEM_CLASS_MONEY )
					{
						Money* pMoney = dynamic_cast<Money*>(pTempItem);
						if ( pMoney->getAmount() >= g_pVariableManager->getMoneyTraceLogLimit() )
						{
							char zoneName[15];
							sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), x, y);
							remainMoneyTraceLog( zoneName, "GOD", ITEM_LOG_DELETE, DETAIL_TIMEOUT, pMoney->getAmount() );
						}
					}

					pTempItem->destroy();
				}

				SAFE_DELETE(pTempItem);
			}
		}
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayItem::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectDecayItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectDecayItem("
			<< "ZoneID:" << (int)m_pZone->getZoneID()
			<< ",X:"     << (int)getX()
			<< ",Y:"     << (int)getY();

	if (m_pTarget) msg << ",Target:" << m_pTarget->toString();
	else           msg << ",Target:NULL";

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec;

	msg << ")";

	return msg.toString();
}
