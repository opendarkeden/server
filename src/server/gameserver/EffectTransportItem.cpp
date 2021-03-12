//----------------------------------------------------------------------
//
// Filename    : EffectTransportItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectTransportItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectTransportItem::EffectTransportItem (Zone* pZone , ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay) 
	
: Effect(pZone,x,y,pItem,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);
	Assert(pTargetZone != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();

	// pTargetZone, x, y
	// m_pZone, m_StartX, m_StartY
	m_pTargetZone = pTargetZone;	
	m_StartX = sx;					
	m_StartY = sy;

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectTransportItem::~EffectTransportItem () 
	
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
void EffectTransportItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectTransportItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	//cout << "EffectTransportItem unaffect(pZone,x,y,pTarget)" << endl;

	// pTargetZone, x, y
	// m_pZone, m_StartX, m_StartY

	// 올바른 좌표이어야 한다.
	if (isValidZoneCoord(pZone, m_StartX, m_StartY))
	{
		//Assert(isValidZoneCoord(pZone, m_StartX, m_StartY));

		// TempItem 변수를 잡는다.
		Item* pTempItem = NULL;

		// 여기서는 지정 아이템이 없을 수 있으며, 또 다른 아이템이 놓여 있을 수도 있다.
		// 이 경우는 오리지널 아이템과 지금 현재 바닥에 있는 아이템을 비교하여 삭제해야 한다.
		// 없을 경우는 무시하면 된다.
		Tile & tile = pZone->getTile(m_StartX, m_StartY);

		if (tile.hasItem()) 
		{
			pTempItem = tile.getItem();

			if (pTempItem != NULL) {
				// ObjectID가 같다는 말은 같은 아이템이란 말이다.
				//if (pTempItem->getObjectID() == m_ObjectID) {
				if (pTempItem->getObjectID() == m_ObjectID) {

					pZone->deleteItem(pTempItem , m_StartX, m_StartY);

					// 아이템이 사라졌다는 패킷을 날린다.
					GCDeleteObject gcDeleteObject;
					gcDeleteObject.setObjectID(m_ObjectID);

					pZone->broadcastPacket(m_StartX, m_StartY , &gcDeleteObject);

					// 다른 존에 추가한다.
					// Multi-thread이므로.. 조심조심..
					// 같은 ZoneGroup이면 걍 넣는다.
					if (pZone->getZoneGroup()==m_pTargetZone->getZoneGroup())
					//if (pZone==m_pTargetZone)
					{
						//cout << "Zone->addItem" << endl;
						m_pTargetZone->addItem(pTempItem, x, y);
					}
					else
					{
						//cout << "Zone->addItemDelayed" << endl;
						m_pTargetZone->addItemDelayed(pTempItem, x, y);
					}

					//cout << "addItemDelayed OK" << endl;
				}
			}
		}
	}
	else
	{
		filelog("motorBug.txt", "ZoneID=%d, x=%d, y=%d", (int)pZone->getZoneID(), (int)m_StartX, (int)m_StartY);
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItem::unaffect ()
	
{
	__BEGIN_TRY

	//cout << "EffectTransportItem unaffect" << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectTransportItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectTransportItem("
			<< "ZoneID:" << (int)m_pZone->getZoneID()
			<< "TargetZoneID:" << (int)m_pTargetZone->getZoneID()
			<< ",X:"     << (int)getX()
			<< ",Y:"     << (int)getY();

	if (m_pTarget) msg << ",Target:" << m_pTarget->toString();
	else           msg << ",Target:NULL";

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec;

	msg << ")";

	return msg.toString();
}
