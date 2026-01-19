//--------------------------------------------------------------------------------
//
// Filename    : GCSearchMotorcycleFail.cpp
// Written By  : elca@ewestsoft.com
// Description : Packet informing the player that motorcycle search failed.
//
//--------------------------------------------------------------------------------

// include files
#include "GCSearchMotorcycleFail.h"

#include "Assert1.h"

//--------------------------------------------------------------------
// Initialize the packet by reading data from the input stream.
//--------------------------------------------------------------------
void GCSearchMotorcycleFail::read(SocketInputStream& iStream)

{
    __BEGIN_TRY
    __END_CATCH
}


//--------------------------------------------------------------------------------
// Serialize the packet into the output stream.
//--------------------------------------------------------------------------------
void GCSearchMotorcycleFail::write(SocketOutputStream& oStream) const

{
    __BEGIN_TRY
    __END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCSearchMotorcycleFail::execute(Player* pPlayer)

{
    __BEGIN_TRY

    GCSearchMotorcycleFailHandler::execute(this, pPlayer);

    __END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCSearchMotorcycleFail::toString() const

{
    __BEGIN_TRY

    StringStream msg;
    msg << "GCSearchMotorcycleFail()";
    return msg.toString();

    __END_CATCH
}
