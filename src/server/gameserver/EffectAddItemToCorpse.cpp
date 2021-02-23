//----------------------------------------------------------------------
//
// Filename    : EffectAddItemToCorpse.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddItemToCorpse.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "Corpse.h"
#include "ZoneUtil.h"
#include "ParkingCenter.h"
#include "item/Motorcycle.h"
#include <stdio.h>

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectAddItemToCorpse::EffectAddItemToCorpse (Zone* pZone, Item* pItem, ObjectID_t corpseObjectID, Turn_t delay)
	throw (Error)
: Effect(pZone,0,0,pItem,delay) 
{
	__BEGIN_TRY

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_CorpseObjectID = corpseObjectID;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectAddItemToCorpse::~EffectAddItemToCorpse () 
	throw (Error)
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
void EffectAddItemToCorpse::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	// 올바른 좌표이어야 한다.
	Assert(pTarget!=NULL);

	Item* pItem = dynamic_cast<Item*>(pTarget);
	Assert(pItem!=NULL);

	pZone->getObjectRegistry().registerObject(pItem);

	Item* pCorpseItem = pZone->getItem( m_CorpseObjectID );

	if (pCorpseItem!=NULL && pCorpseItem->getItemClass()==Item::ITEM_CLASS_CORPSE)
	{
		Corpse* pCorpse = dynamic_cast<Corpse*>(pCorpseItem);
		Assert(pCorpse!=NULL);

		pCorpse->addTreasure( pItem );
	}
	else
	{
		throw Error("시체가 아니네");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect ()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect (Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddItemToCorpse::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectAddItemToCorpse("
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
