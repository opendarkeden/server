////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketErrorBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketErrorBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketErrorBody::CBillingPacketErrorBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketErrorBodyInfo );

	__END_CATCH
}

void CBillingPacketErrorBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketErrorBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketErrorBodyInfo );

	__END_CATCH
}

void CBillingPacketErrorBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketErrorBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketErrorBodyInfo );

	__END_CATCH
}

string CBillingPacketErrorBody::toString() const
	throw ()
{
	char str[192];
	StringStream msg;
	msg << "ErrorBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str;

	memcpy( str, Return_Message, 128 ); str[128] = '\0';
	msg << ",Return_Message:" << str
		<< ")";

	return msg.toString();
}

