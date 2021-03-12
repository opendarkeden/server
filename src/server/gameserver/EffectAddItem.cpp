//----------------------------------------------------------------------
//
// Filename    : EffectAddItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"
#include "ParkingCenter.h"
#include "item/Motorcycle.h"
#include <stdio.h>

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectAddItem::EffectAddItem (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bAllowCreature) 
	
: Effect(pZone,x,y,pItem,delay) 
{
	__BEGIN_TRY

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();
	m_bAllowCreature = bAllowCreature;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectAddItem::~EffectAddItem () 
	
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
void EffectAddItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	//cout << "EffectAddItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)" << endl;

	// 올바른 좌표이어야 한다.
	Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	Item* pItem = dynamic_cast<Item*>(pTarget);

	if (pItem!=NULL)
	{
		pZone->getObjectRegistry().registerObject(pItem);

		//TPOINT pt = 
		pZone->addItem(pItem, x, y, m_bAllowCreature);
	}
	else
	{
		SAFE_DELETE(pTarget);
		throw Error("EffectAddItem인데 item이 아닌가?");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItem::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectAddItem("
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
