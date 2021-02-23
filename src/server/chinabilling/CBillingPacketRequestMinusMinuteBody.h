////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestMinusMinuteBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY__
#define __CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestMinusMinuteBody
///////////////////////////////////////////////////
class CBillingPacketRequestMinusMinuteBody : public CBillingPacketRequestMinusMinuteBodyInfo
{
public:
	// constructor
	CBillingPacketRequestMinusMinuteBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

