////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseLoginBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketResponseLoginBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketResponseLoginBody::CBillingPacketResponseLoginBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketResponseLoginBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseLoginBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketResponseLoginBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketResponseLoginBodyInfo );

	// change order network to host
	Player_Type			= ntohl( Player_Type );
	Pay_Type			= ntohl( Pay_Type );
	Free_Left_Time		= ntohl( Free_Left_Time );
	Rating_Left_Time	= ntohl( Rating_Left_Time );

	__END_CATCH
}

void CBillingPacketResponseLoginBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	// change order host to network
	Player_Type			= htonl( Player_Type );
	Pay_Type			= htonl( Pay_Type );
	Free_Left_Time		= htonl( Free_Left_Time );
	Rating_Left_Time	= htonl( Rating_Left_Time );

	const CBillingPacketResponseLoginBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketResponseLoginBodyInfo );

	// restore order
	Player_Type			= ntohl( Player_Type );
	Pay_Type			= ntohl( Pay_Type );
	Free_Left_Time		= ntohl( Free_Left_Time );
	Rating_Left_Time	= ntohl( Rating_Left_Time );

	__END_CATCH
}

string CBillingPacketResponseLoginBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "ResponseLoginBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str;
	memcpy( str, End_Date_Time, 16 ); str[16] = '\0';
	msg	<< ",End_Date_Time:" << End_Date_Time
		<< ",Player_Type:" << Player_Type
		<< ",Pay_Type:" << Pay_Type
		<< ",Free_Left_Time:" << Free_Left_Time
		<< ",Rating_Left_Time:" << Rating_Left_Time
		<< ")";

	return msg.toString();
}

