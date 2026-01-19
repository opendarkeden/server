/////////////////////////////////////////////////////////////////////////////
// Filename : MPacket.h
// Desc		: Base interface for Mofus packets.
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_H__
#define __MPACKET_H__


// include files
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Types.h"

// packet size type
typedef int MPacketSize_t;
const unsigned int szMPacketSize = sizeof(MPacketSize_t);

// packet type
typedef int MPacketID_t;
const unsigned int szMPacketID = sizeof(MPacketID_t);

const unsigned int szMPacketHeader = szMPacketSize + szMPacketID;


class MPacket {
public:
    virtual ~MPacket() = default;

    // Return the packet identifier.
    virtual MPacketID_t getID() const = 0;

    // Return the packet size.
    virtual MPacketSize_t getSize() const = 0;

    // Factory: create a new packet of this type.
    virtual MPacket* create() = 0;

    // Populate the packet from the input stream payload.
    virtual void read(SocketInputStream& iStream) = 0;

    // Serialize the packet to the output stream.
    virtual void write(SocketOutputStream& oStream) = 0;

    // debug message
    virtual string toString() const = 0;
};

#endif
