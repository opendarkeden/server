//----------------------------------------------------------------------
//
// Filename    : EffectDecayMotorcycle.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectDecayMotorcycle.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectDecayMotorcycle::EffectDecayMotorcycle (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bDeleteFromDB)
	
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
EffectDecayMotorcycle::~EffectDecayMotorcycle () 
	
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
void EffectDecayMotorcycle::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget, Slayer* pSlayer)
	
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
					pTempItem->destroy();
				}

				SAFE_DELETE(pTempItem);
			}
		}
	}

	// heartbeat시 EffectDecayMotorcycle이 처리된다. 그 이후 다음 heartbeat시에 
	// 사용자에게 오토바이를 호출해 주어야 한다.
	// 사용자는 오토바이의 오브젝트와 

	//EffectCallMotorcycle* pEffectCallMotorcycle = new EffectCallMotorcycle(pMotorcycleObject, pSlayer);
	//pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectDecayMotorcycle::toString () const 
	
{
	StringStream msg;

	msg << "EffectDecayMotorcycle("
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
