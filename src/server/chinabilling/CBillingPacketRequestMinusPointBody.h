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
	CBillingPacketRequestMinusPointBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

