////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseMinusPointBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_RESPONSE_MINUS_POINT_BODY__
#define __CBILLING_PACKET_RESPONSE_MINUS_POINT_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketResponseMinusPointBody
///////////////////////////////////////////////////
class CBillingPacketResponseMinusPointBody : public CBillingPacketResponseMinusPointBodyInfo
{
public:
	// constructor
	CBillingPacketResponseMinusPointBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

