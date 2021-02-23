////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestMinusPointBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_MINUS_POINT_BODY__
#define __CBILLING_PACKET_REQUEST_MINUS_POINT_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestMinusPointBody
///////////////////////////////////////////////////
class CBillingPacketRequestMinusPointBody : public CBillingPacketRequestMinusPointBodyInfo
{
public:
	// constructor
	CBillingPacketRequestMinusPointBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

