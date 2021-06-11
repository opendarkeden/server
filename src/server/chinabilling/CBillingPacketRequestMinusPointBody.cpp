////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestMinusPointBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketRequestMinusPointBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketRequestMinusPointBody::CBillingPacketRequestMinusPointBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketRequestMinusPointBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestMinusPointBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketRequestMinusPointBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketRequestMinusPointBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestMinusPointBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketRequestMinusPointBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketRequestMinusPointBodyInfo );

	__END_CATCH
}

string CBillingPacketRequestMinusPointBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "RequestMinusPointBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ")";

	return msg.toString();
}

