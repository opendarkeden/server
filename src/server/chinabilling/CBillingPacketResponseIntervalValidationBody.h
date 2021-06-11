////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseIntervalValidationBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_RESPONSE_INTERVAL_VALIDATION_BODY__
#define __CBILLING_PACKET_RESPONSE_INTERVAL_VALIDATION_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketResponseIntervalValidationBody
///////////////////////////////////////////////////
class CBillingPacketResponseIntervalValidationBody : public CBillingPacketResponseIntervalValidationBodyInfo
{
public:
	// constructor
	CBillingPacketResponseIntervalValidationBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

