////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketErrorBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_ERROR_BODY__
#define __CBILLING_PACKET_ERROR_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketErrorBody
///////////////////////////////////////////////////
class CBillingPacketErrorBody : public CBillingPacketErrorBodyInfo
{
public:
	// constructor
	CBillingPacketErrorBody() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& oStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

