////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestLoginBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_LOGIN_BODY__
#define __CBILLING_PACKET_REQUEST_LOGIN_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestLoginBody
///////////////////////////////////////////////////
class CBillingPacketRequestLoginBody : public CBillingPacketRequestLoginBodyInfo
{
public:
	// constructor
	CBillingPacketRequestLoginBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

