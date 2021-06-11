////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseLogoutBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketResponseLogoutBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketResponseLogoutBody::CBillingPacketResponseLogoutBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketResponseLogoutBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseLogoutBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketResponseLogoutBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketResponseLogoutBodyInfo );

	// change order network to host
	Minus_Free_Point	= ntohl( Minus_Free_Point );
	Minus_Point			= ntohl( Minus_Point );

	__END_CATCH
}

void CBillingPacketResponseLogoutBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	// change order host to network
	Minus_Free_Point	= htonl( Minus_Free_Point );
	Minus_Point			= htonl( Minus_Point );

	const CBillingPacketResponseLogoutBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketResponseLogoutBodyInfo );

	// restore order
	Minus_Free_Point	= ntohl( Minus_Free_Point );
	Minus_Point			= ntohl( Minus_Point );

	__END_CATCH
}

string CBillingPacketResponseLogoutBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "ResponseLogoutBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ",Minus_Free_Point:" << Minus_Free_Point
		<< ",Minus_Point:" << Minus_Point
		<< ")";

	return msg.toString();
}

