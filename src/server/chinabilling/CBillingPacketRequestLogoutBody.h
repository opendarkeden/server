////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestLogoutBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_LOGOUT_BODY__
#define __CBILLING_PACKET_REQUEST_LOGOUT_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestLogoutBody
///////////////////////////////////////////////////
class CBillingPacketRequestLogoutBody : public CBillingPacketRequestLogoutBodyInfo
{
public:
	// constructor
	CBillingPacketRequestLogoutBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

