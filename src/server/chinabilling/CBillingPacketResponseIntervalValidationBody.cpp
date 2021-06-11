////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseIntervalValidationBody.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketResponseIntervalValidationBody.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

CBillingPacketResponseIntervalValidationBody::CBillingPacketResponseIntervalValidationBody()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketResponseIntervalValidationBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseIntervalValidationBody::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketResponseIntervalValidationBodyInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketResponseIntervalValidationBodyInfo );

	__END_CATCH
}

void CBillingPacketResponseIntervalValidationBody::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	const CBillingPacketResponseIntervalValidationBodyInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketResponseIntervalValidationBodyInfo );

	__END_CATCH
}

string CBillingPacketResponseIntervalValidationBody::toString() const
	throw ()
{
	char str[128];
	StringStream msg;
	msg << "ResponseIntervalValidationBody(";

	memcpy( str, Parameter_Name, 64 ); str[64] = '\0';
	msg << "Parameter_Name:" << str;

	memcpy( str, Parameter_Value, 64 ); str[64] = '\0';
	msg << ",Parameter_Value:" << str
		<< ")";

	return msg.toString();
}

