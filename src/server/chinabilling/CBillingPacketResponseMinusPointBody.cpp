////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseMinusPointBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketResponseMinusPointBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketResponseMinusPointBody::CBillingPacketResponseMinusPointBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketResponseMinusPointBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseMinusPointBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketResponseMinusPointBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketResponseMinusPointBodyInfo );

	// change order network to host
	Player_Type			= ntohl( Player_Type );
	Pay_Type			= ntohl( Pay_Type );
	Free_Left_Time		= ntohl( Free_Left_Time );
	Rating_Left_Time	= ntohl( Rating_Left_Time );
	Minus_Free_Point	= ntohl( Minus_Free_Point );
	Minus_Point			= ntohl( Minus_Point );

	__END_CATCH
}

void CBillingPacketResponseMinusPointBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	// change order host to network
	Player_Type			= htonl( Player_Type );
	Pay_Type			= htonl( Pay_Type );
	Free_Left_Time		= htonl( Free_Left_Time );
	Rating_Left_Time	= htonl( Rating_Left_Time );
	Minus_Free_Point	= htonl( Minus_Free_Point );
	Minus_Point			= htonl( Minus_Point );

	const CBillingPacketResponseMinusPointBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketResponseMinusPointBodyInfo );

	// restore order
	Player_Type			= ntohl( Player_Type );
	Pay_Type			= ntohl( Pay_Type );
	Free_Left_Time		= ntohl( Free_Left_Time );
	Rating_Left_Time	= ntohl( Rating_Left_Time );
	Minus_Free_Point	= ntohl( Minus_Free_Point );
	Minus_Point			= ntohl( Minus_Point );

	__END_CATCH
}

string CBillingPacketResponseMinusPointBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "ResponseMinusPointBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ",Player_Type:" << Player_Type
		<< ",Pay_Type:" << Pay_Type
		<< ",Free_Left_Time:" << Free_Left_Time
		<< ",Rating_Left_Time:" << Rating_Left_Time
		<< ",Minus_Free_Point:" << Minus_Free_Point
		<< ",Minus_Point:" << Minus_Point
		<< ")";

	return msg.toString();
}

