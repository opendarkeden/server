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
	CBillingPacketResponseIntervalValidationBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

