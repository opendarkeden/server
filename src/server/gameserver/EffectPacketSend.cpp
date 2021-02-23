//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPacketSend.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectPacketSend.h"
#include "Zone.h"
#include "Player.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPacketSend::EffectPacketSend(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;

	__END_CATCH
}

void EffectPacketSend::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Assert( m_pZone != NULL );
	Assert( m_pPacket != NULL );
	m_pZone->broadcastPacket( m_X, m_Y, m_pPacket );

	SAFE_DELETE( m_pPacket );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPacketSend::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPacketSend("
		<< "ObjectID:" << getObjectID()
		<< ", Packet : " << m_pPacket->toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}
