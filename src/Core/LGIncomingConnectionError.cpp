//////////////////////////////////////////////////////////////////////
//
// Filename    : LGIncomingConnectionError.cpp
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "LGIncomingConnectionError.h"


//////////////////////////////////////////////////////////////////////
// Initialize the packet by reading data from the datagram payload.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::read(Datagram& iDatagram)

{
    __BEGIN_TRY

    //--------------------------------------------------
    //--------------------------------------------------
    BYTE szMessage;

    iDatagram.read(szMessage);

    if (szMessage == 0)
        throw InvalidProtocolException("szMessage == 0");

    if (szMessage >= 128)
        throw InvalidProtocolException("too large message length");

    iDatagram.read(m_Message, szMessage);


    //--------------------------------------------------
    //--------------------------------------------------
    BYTE szPlayerID;

    iDatagram.read(szPlayerID);

    if (szPlayerID == 0)
        throw InvalidProtocolException("szPlayerID == 0");

    if (szPlayerID >= 128)
        throw InvalidProtocolException("too large playerID length");

    iDatagram.read(m_PlayerID, szPlayerID);


    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Serialize the packet into the datagram payload.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::write(Datagram& oDatagram) const

{
    __BEGIN_TRY
    __BEGIN_DEBUG

    //--------------------------------------------------
    //--------------------------------------------------
    BYTE szMessage = m_Message.size();

    if (szMessage == 0)
        throw InvalidProtocolException("szMessage == 0");

    if (szMessage >= 128)
        throw InvalidProtocolException("too large message length");

    oDatagram.write(szMessage);

    oDatagram.write(m_Message);


    //--------------------------------------------------
    //--------------------------------------------------
    BYTE szPlayerID = m_PlayerID.size();

    if (szPlayerID == 0)
        throw InvalidProtocolException("szPlayerID == 0");

    if (szPlayerID >= 128)
        throw InvalidProtocolException("too large playerID length");

    oDatagram.write(szPlayerID);

    oDatagram.write(m_PlayerID);

    __END_DEBUG
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::execute(Player* pPlayer)

{
    __BEGIN_TRY

    // cout << "LGIncomingConnectionError::execute() called." << endl;

    LGIncomingConnectionErrorHandler::execute(this);

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string LGIncomingConnectionError::toString() const

{
    __BEGIN_TRY

    StringStream msg;
    msg << "LGIncomingConnectionError("
        << "Message:" << m_Message << "PlayerID:" << m_PlayerID << ")";
    return msg.toString();

    __END_CATCH
}
