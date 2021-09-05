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
	CBillingPacketRequestLogoutBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

