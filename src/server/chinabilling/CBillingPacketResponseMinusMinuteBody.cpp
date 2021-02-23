////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseMinusMinuteBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketResponseMinusMinuteBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketResponseMinusMinuteBody::CBillingPacketResponseMinusMinuteBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketResponseMinusMinuteBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseMinusMinuteBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketResponseMinusMinuteBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketResponseMinusMinuteBodyInfo );

	// change order network to host
	Pay_Type				= ntohl( Pay_Type );
	Free_Left_Time			= ntohl( Free_Left_Time );
	Rating_Left_Time		= ntohl( Rating_Left_Time );
	Minus_Free_Duration		= ntohl( Minus_Free_Duration );
	Minus_Duration			= ntohl( Minus_Duration );

	__END_CATCH
}

void CBillingPacketResponseMinusMinuteBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	// change order host to network
	Pay_Type				= htonl( Pay_Type );
	Free_Left_Time			= htonl( Free_Left_Time );
	Rating_Left_Time		= htonl( Rating_Left_Time );
	Minus_Free_Duration		= htonl( Minus_Free_Duration );
	Minus_Duration			= htonl( Minus_Duration );

	const CBillingPacketResponseMinusMinuteBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketResponseMinusMinuteBodyInfo );

	// restore order
	Pay_Type				= ntohl( Pay_Type );
	Free_Left_Time			= ntohl( Free_Left_Time );
	Rating_Left_Time		= ntohl( Rating_Left_Time );
	Minus_Free_Duration		= ntohl( Minus_Free_Duration );
	Minus_Duration			= ntohl( Minus_Duration );

	__END_CATCH
}

string CBillingPacketResponseMinusMinuteBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "ResponseMinusMinuteBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ",Pay_Type:" << Pay_Type
		<< ",Free_Left_Time:" << Free_Left_Time
		<< ",Rating_Left_Time:" << Rating_Left_Time
		<< ",Minus_Free_Duration:" << Minus_Free_Duration
		<< ",Minus_Duration:" << Minus_Duration
		<< ")";

	return msg.toString();
}

