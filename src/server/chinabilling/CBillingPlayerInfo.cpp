///////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayerInfo.h
//
///////////////////////////////////////////////////////////////

// include files
#include "CBillingPlayerInfo.h"
#include "StringStream.h"

CBillingPlayerInfo::CBillingPlayerInfo()
	throw ( Error )
	: m_bCBillingVerified( false ),
	  m_bPayPlayer( false ),
	  m_bShowPayInfo( false ),
	  m_CBPlayerType( CBILLING_PLAYER_TYPE_MAX ),
	  m_CBPayType( CBILLING_PAY_TYPE_MAX ),
	  m_SendID( 0 ),
	  m_RecvID( 0 ),
	  m_MissedMinusPointPacket( 0 ),
	  m_CBLastShowLeftTime( 300 )
{
	__BEGIN_TRY
	__END_CATCH
}

CBillingPlayerInfo::~CBillingPlayerInfo()
	throw ( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

string CBillingPlayerInfo::toString() const
	throw ( Error )
{
	__BEGIN_TRY

	StringStream msg;

	msg << "CBillingPlayerInfo()";

	return msg.toString();

	__END_CATCH
}

