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
	CBillingPacketResponseMinusMinuteBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

