////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseMinusMinuteBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_RESPONSE_MINUS_MINUTE_BODY__
#define __CBILLING_PACKET_RESPONSE_MINUS_MINUTE_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketResponseMinusMinuteBody
///////////////////////////////////////////////////
class CBillingPacketResponseMinusMinuteBody : public CBillingPacketResponseMinusMinuteBodyInfo
{
public:
	// constructor
	CBillingPacketResponseMinusMinuteBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

