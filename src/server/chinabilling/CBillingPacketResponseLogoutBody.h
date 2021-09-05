////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseLogoutBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_RESPONSE_LOGOUT_BODY__
#define __CBILLING_PACKET_RESPONSE_LOGOUT_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketResponseLogoutBody
///////////////////////////////////////////////////
class CBillingPacketResponseLogoutBody : public CBillingPacketResponseLogoutBodyInfo
{
public:
	// constructor
	CBillingPacketResponseLogoutBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

