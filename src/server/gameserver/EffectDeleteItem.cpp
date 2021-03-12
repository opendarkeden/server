//----------------------------------------------------------------------
//
// Filename    : EffectDeleteItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include fies
#include "Assert.h"
#include "EffectDeleteItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectDeleteItem::EffectDeleteItem (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject , Turn_t delay)
	
: Effect(pZone,x,y,pObject,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pObject->getObjectID();

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectDeleteItem::~EffectDeleteItem () 
	
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
void EffectDeleteItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	// 올바른 좌표이어야 한다.
	//Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	//pZone->deleteFromItemList(pTarget->getObjectID());
	//(pZone->getTile( x, y)).deleteItem();
	//pZone->deleteItem( pTarget, x, y );

	Item* pItem = NULL;

	Tile& tile = pZone->getTile(x,y);

	if ( tile.hasItem() )
	{
		pItem = tile.getItem();

		if ( pItem != NULL )
		{
			if ( pItem->getObjectID() == m_ObjectID )
			{
				pZone->deleteItem( pItem, x, y );

				GCDeleteObject gcDO;
				gcDO.setObjectID(pTarget->getObjectID());
				pZone->broadcastPacket(x, y, &gcDO);

				SAFE_DELETE(pTarget);
			}
		}
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectDeleteItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectDeleteItem("
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
