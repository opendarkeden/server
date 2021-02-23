////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestLoginBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketRequestLoginBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketRequestLoginBody::CBillingPacketRequestLoginBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketRequestLoginBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestLoginBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketRequestLoginBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketRequestLoginBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestLoginBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketRequestLoginBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketRequestLoginBodyInfo );

	__END_CATCH
}

string CBillingPacketRequestLoginBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "RequestLoginBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str;

	memcpy( str, Player_IP, 32 ); str[32] = '\0';
	msg << ",Player_IP:" << str;

	memcpy( str, Player_MAC, 32 ); str[32] = '\0';
	msg << ",Player_MAC:" << str
		<< ")";

	return msg.toString();
}

