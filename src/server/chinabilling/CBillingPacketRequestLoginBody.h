////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestLoginBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_LOGIN_BODY__
#define __CBILLING_PACKET_REQUEST_LOGIN_BODY__

// include files
#include "CBillingInfo.h"
#include "Exception.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestLoginBody
///////////////////////////////////////////////////
class CBillingPacketRequestLoginBody : public CBillingPacketRequestLoginBodyInfo {
public:
    // constructor
    CBillingPacketRequestLoginBody();

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream);

    string toString() const;
};

#endif
