//----------------------------------------------------------------------
//
// Filename    : EffectTransportItemToCorpse.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectTransportItemToCorpse.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "Corpse.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectTransportItemToCorpse::EffectTransportItemToCorpse (Zone* pZone, Item* pItem, 
														Zone* pTargetZone, ObjectID_t corpseObjectID, Turn_t delay) 
	
: Effect(pZone,0,0,pItem,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);
	Assert(pTargetZone != NULL);

	// pTargetZone, x, y
	// m_pZone, m_StartX, m_StartY
	m_pTargetZone = pTargetZone;	
	m_CorpseObjectID = corpseObjectID;	

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectTransportItemToCorpse::~EffectTransportItemToCorpse () 
	
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
void EffectTransportItemToCorpse::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectTransportItemToCorpse::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);
	Assert(m_pTargetZone!=NULL);

	Item* pItem = dynamic_cast<Item*>(pTarget);
	Assert(pItem!=NULL);

	// 다른 존에 추가한다.
	// Multi-thread이므로.. 조심조심..
	// 같은 ZoneGroup이면 걍 넣는다.
	if (pZone->getZoneGroup()==m_pTargetZone->getZoneGroup())
	//if (pZone==m_pTargetZone)
	{
		//cout << "Zone->addItem" << endl;
		//pZone->addItem(pTempItem, x, y);

		Item* pCorpseItem = m_pTargetZone->getItem( m_CorpseObjectID );

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
	}
	else
	{
		//cout << "Zone->addItemDelayed" << endl;
		m_pTargetZone->addItemToCorpseDelayed(pItem, m_CorpseObjectID);
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItemToCorpse::unaffect ()
	
{
	__BEGIN_TRY

	//cout << "EffectTransportItemToCorpse unaffect" << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItemToCorpse::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectTransportItemToCorpse::toString () const 
	
{
	StringStream msg;

	msg << "EffectTransportItemToCorpse("
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
