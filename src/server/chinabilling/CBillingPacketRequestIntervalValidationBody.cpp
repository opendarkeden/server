////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestIntervalValidationBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketRequestIntervalValidationBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "CBillingPlayerManager.h"

CBillingPacketRequestIntervalValidationBody::CBillingPacketRequestIntervalValidationBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketRequestIntervalValidationBodyInfo );

	static string interval = g_pCBillingPlayerManager->getMinusInterval();
	strcpy( Parameter_Name, "MINUS_INTERVAL" );
	strcpy( Parameter_Value, interval.c_str() );

	__END_CATCH
}

void CBillingPacketRequestIntervalValidationBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketRequestIntervalValidationBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketRequestIntervalValidationBodyInfo );

	__END_CATCH
}

void CBillingPacketRequestIntervalValidationBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketRequestIntervalValidationBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketRequestIntervalValidationBodyInfo );

	__END_CATCH
}

string CBillingPacketRequestIntervalValidationBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "RequestIntervalValidationBody(";

	memcpy( str, Parameter_Name, 64 ); str[64] = '\0';
	msg << "Parameter_Name:" << str;

	memcpy( str, Parameter_Value, 64 ); str[64] = '\0';
	msg << ",Parameter_Value:" << str
		<< ")";

	return msg.toString();
}

