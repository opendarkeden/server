////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestLogoutBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketRequestLogoutBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketRequestLogoutBody::CBillingPacketRequestLogoutBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketRequestLogoutBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestLogoutBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketRequestLogoutBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketRequestLogoutBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestLogoutBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketRequestLogoutBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketRequestLogoutBodyInfo );

	__END_CATCH
}

string CBillingPacketRequestLogoutBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "RequestLogoutBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ")";

	return msg.toString();
}

