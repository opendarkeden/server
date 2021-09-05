////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestMinusMinuteBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketRequestMinusMinuteBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketRequestMinusMinuteBody::CBillingPacketRequestMinusMinuteBody()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketRequestMinusMinuteBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestMinusMinuteBody::read( SocketInputStream& iStream )
{
	__BEGIN_TRY
	
	CBillingPacketRequestMinusMinuteBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketRequestMinusMinuteBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestMinusMinuteBody::write( SocketOutputStream& oStream )
{
	__BEGIN_TRY

	const CBillingPacketRequestMinusMinuteBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketRequestMinusMinuteBodyInfo );

	__END_CATCH
}

string CBillingPacketRequestMinusMinuteBody::toString() const
{
	char str[128];
	StringStream msg;
	msg << "ErrorBody(";

	memcpy( str, Login_Name, 64 ); str[64] = '\0';
	msg << "Login_Name:" << str
		<< ")";

	return msg.toString();
}

