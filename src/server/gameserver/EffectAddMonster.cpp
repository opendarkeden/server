//----------------------------------------------------------------------
//
// Filename    : EffectAddMonster.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddMonster.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectAddMonster::EffectAddMonster (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pCreature , Turn_t delay)
	throw (Error)
: Effect(pZone,x,y,pCreature,delay) 
{
	__BEGIN_TRY

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pCreature->getObjectID();

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectAddMonster::~EffectAddMonster () 
	throw (Error)
{
	__BEGIN_TRY

	unaffect(m_pZone , m_X , m_Y , (Creature*)m_pTarget);

	__END_CATCH
}
			

//----------------------------------------------------------------------
// affect to target
// 이 이펙트는 타일에 종속되지 않으므로, affect()는 호출되지 않는다.
// 왜냐하면, target은 생성자에서 지정되며, 아무런 일도 하지 않기 때문이다.
//----------------------------------------------------------------------
void EffectAddMonster::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pTarget)
	throw (Error)
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddMonster::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	// 올바른 좌표이어야 한다.
	Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	Monster* pMonster = dynamic_cast<Monster*>(pTarget);

	if (pMonster!=NULL)
	{
		//pZone->getObjectRegistry().registerObject(pMonster);

		TPOINT pt = pZone->addCreature(pMonster, x, y, 2);

		cout << pZone->getZoneID() << "존의 (" << x << "," << y << ")에 몬스터가 추가되었습니다" << endl;

		if (pt.x == -1)
		{
			SAFE_DELETE(pMonster);
			throw Error("Zone에 몬스터 들어갈 자리가 없다");
		}
	}
	else
	{
		SAFE_DELETE(pMonster);
		throw Error("EffectAddMonster인데 item이 아닌가?");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddMonster::unaffect ()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddMonster::unaffect (Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddMonster::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectAddMonster("
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
