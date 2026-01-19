////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestMinusMinuteBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY__
#define __CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY__

// include files
#include "CBillingInfo.h"
#include "Exception.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestMinusMinuteBody
///////////////////////////////////////////////////
class CBillingPacketRequestMinusMinuteBody : public CBillingPacketRequestMinusMinuteBodyInfo {
public:
    // constructor
    CBillingPacketRequestMinusMinuteBody();

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream);

    string toString() const;
};

#endif
