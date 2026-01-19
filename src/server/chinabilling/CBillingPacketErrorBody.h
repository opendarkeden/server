////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketErrorBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_ERROR_BODY__
#define __CBILLING_PACKET_ERROR_BODY__

// include files
#include "CBillingInfo.h"
#include "Exception.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketErrorBody
///////////////////////////////////////////////////
class CBillingPacketErrorBody : public CBillingPacketErrorBodyInfo {
public:
    // constructor
    CBillingPacketErrorBody();

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream);

    string toString() const;
};

#endif
