//-------------------------------------------------------------------------------- //
// Filename    : GCUsePowerPointResult.cpp
// Written By  : reiot@ewestsoft.com
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GCUsePowerPointResult.h"


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCUsePowerPointResult::GCUsePowerPointResult()

    : m_ErrorCode(0), m_ItemCode(0) {}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCUsePowerPointResult::~GCUsePowerPointResult()

{}

//--------------------------------------------------------------------------------
// Initialize packet by reading data from the incoming stream.
//--------------------------------------------------------------------------------
void GCUsePowerPointResult::read(SocketInputStream& iStream)

{
    __BEGIN_TRY

    // Error code
    iStream.read(m_ErrorCode);

    // Item Code
    iStream.read(m_ItemCode);

    // Power Point
    iStream.read(m_PowerPoint);

    __END_CATCH
}


//--------------------------------------------------------------------------------
// Serialize packet data to the outgoing stream.
//--------------------------------------------------------------------------------
void GCUsePowerPointResult::write(SocketOutputStream& oStream) const

{
    __BEGIN_TRY

    // Error code
    oStream.write(m_ErrorCode);

    // Item Code
    oStream.write(m_ItemCode);

    // Power Point
    oStream.write(m_PowerPoint);

    __END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCUsePowerPointResult::execute(Player* pPlayer)

{
    __BEGIN_TRY

    GCUsePowerPointResultHandler::execute(this, pPlayer);

    __END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCUsePowerPointResult::toString() const

{
    __BEGIN_TRY

    StringStream msg;

    msg << "GCUsePowerPointResult("
        << "ErrorCode:" << (int)m_ErrorCode << ",ItemCode:" << (int)m_ItemCode << ",PowerPoint:" << m_PowerPoint << ")";

    return msg.toString();

    __END_CATCH
}
