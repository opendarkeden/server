////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketResponseLoginBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_RESPONSE_LOGIN_BODY__
#define __CBILLING_PACKET_RESPONSE_LOGIN_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketResponseLoginBody
///////////////////////////////////////////////////
class CBillingPacketResponseLoginBody : public CBillingPacketResponseLoginBodyInfo
{
public:
	// constructor
	CBillingPacketResponseLoginBody();

public:
	void read( SocketInputStream& iStream );
	void write( SocketOutputStream& oStream );

	string toString() const;
};

#endif

