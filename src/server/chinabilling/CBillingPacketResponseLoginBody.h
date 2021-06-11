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
	CBillingPacketResponseLoginBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

