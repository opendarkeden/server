///////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketHeader.h
//
///////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_HEADER_H__
#define __CBILLING_PACKET_HEADER_H__

// include files
#include "CBillingInfo.h"
#include "Exception.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketHeader
///////////////////////////////////////////////////
class CBillingPacketHeader : public CBillingPacketHeaderInfo
{
public:
	// constructor
	CBillingPacketHeader() throw ();

public:
	void read( SocketInputStream& iStream ) throw ( ProtocolException, Error );
	void write( SocketOutputStream& iStream ) throw ( ProtocolException, Error );

	string toString() const throw ();
};

#endif

