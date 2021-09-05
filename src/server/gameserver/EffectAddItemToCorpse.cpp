//----------------------------------------------------------------------
//
// Filename    : EffectAddItemToCorpse.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddItemToCorpse.h"
#include "GCDeleteObject.h"
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
	
: Effect(pZone,0,0,pItem,delay) 
{
	__BEGIN_TRY

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
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
	
{
	unaffect(m_pZone , m_X , m_Y , m_pTarget);
}
			

//----------------------------------------------------------------------
// affect to target
// �� ����Ʈ�� Ÿ�Ͽ� ���ӵ��� �����Ƿ�, affect()�� ȣ����� �ʴ´�.
// �ֳ��ϸ�, target�� �����ڿ��� �����Ǹ�, �ƹ��� �ϵ� ���� �ʱ� �����̴�.
//----------------------------------------------------------------------
void EffectAddItemToCorpse::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
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
		throw Error("��ü�� �ƴϳ�");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItemToCorpse::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddItemToCorpse::toString () const 
	
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
