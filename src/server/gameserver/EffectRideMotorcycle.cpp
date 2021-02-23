//----------------------------------------------------------------------
//
// Filename    : EffectRideMotorcycle.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectRideMotorcycle.h"
#include "Gpackets/GCDeleteObject.h"
#include "Cpackets/CGRideMotorCycle.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"
#include "Slayer.h"
#include "GamePlayer.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectRideMotorcycle::EffectRideMotorcycle (Slayer* pOwner, Item* pMotorcycle, ZoneCoord_t motorX, ZoneCoord_t motorY)
	throw (Error)
: Effect(pOwner->getZone(),motorX,motorY,pOwner,0), m_MotorX(motorX), m_MotorY(motorY), m_OwnerObjectID(pOwner->getObjectID()), m_pMotorcycle(pMotorcycle)
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectRideMotorcycle::~EffectRideMotorcycle () 
	throw (Error)
{
	__BEGIN_TRY

	__END_CATCH
}
			

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectRideMotorcycle::unaffect ()
	throw (Error)
{
	__BEGIN_TRY

	Slayer* pOwner = dynamic_cast<Slayer*>(m_pTarget);
	if ( pOwner == NULL ) return;
	//cout << "EffectRideMotorcycle unaffect" << endl;
	CGRideMotorCycle cgRide;
	cgRide.setObjectID( m_pMotorcycle->getObjectID() );
	cgRide.setX(m_MotorX);
	cgRide.setY(m_MotorY);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pOwner->getPlayer());
	cgRide.execute(pGamePlayer);

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectRideMotorcycle::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectRideMotorcycle("
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
